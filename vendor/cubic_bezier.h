// Copyright 2014 The Chromium Authors. All rights reserved.
// ReSharper disable CppClangTidyBugproneNarrowingConversions

#pragma once

#include <cmath>

constexpr int CUBIC_BEZIER_SPLINE_SAMPLES = 11;

class cubic_bezier {
private: 
    const int max_newton_iterations_ = 4;

public:
    const double bezier_epsilon = 1e-7;

    cubic_bezier(const double p1x, const double p1y, const double p2x, const double p2y) {
        init_coefficients(p1x, p1y, p2x, p2y);
        init_gradients(p1x, p1y, p2x, p2y);
        init_range(p1y, p2y);
        init_spline();
    }

    cubic_bezier(const cubic_bezier &other) = default;

    double sample_curve_x(const double t) const {
        // `ax t^3 + bx t^2 + cx t' expanded using Horner's rule.
        return ((ax_ * t + bx_) * t + cx_) * t;
    }

    double sample_curve_y(const double t) const {
        return ((ay_ * t + by_) * t + cy_) * t;
    }

    double sample_curve_derivative_x(const double t) const {
        return (3.0 * ax_ * t + 2.0 * bx_) * t + cx_;
    }

    double sample_curve_derivative_y(const double t) const {
        return (3.0 * ay_ * t + 2.0 * by_) * t + cy_;
    }

    // Evaluates y at the given x. The epsilon parameter provides a hint as to the
    // required accuracy and is not guaranteed. Uses gradients if x is
    // out of [0, 1] range.
    double solve_with_epsilon(const double x, const double epsilon) const {
        if (x < 0.0) {
            return 0.0 + start_gradient_ * x;
        }

        if (x > 1.0) {
            return 1.0 + end_gradient_ * (x - 1.0);
        }

        return sample_curve_y(solve_curve_x(x, epsilon));
    }

    // Gets the bezier's minimum y value in the interval [0, 1].
    double range_min() const { return range_min_; }
    // Gets the bezier's maximum y value in the interval [0, 1].
    double range_max() const { return range_max_; }

    void init_coefficients(const double p1x, const double p1y, const double p2x, const double p2y) {
        // Calculate the polynomial coefficients, implicit first and last control
        // points are (0,0) and (1,1).
        cx_ = 3.0 * p1x;
        bx_ = 3.0 * (p2x - p1x) - cx_;
        ax_ = 1.0 - cx_ - bx_;

        cy_ = 3.0 * p1y;
        by_ = 3.0 * (p2y - p1y) - cy_;
        ay_ = 1.0 - cy_ - by_;

#ifndef NDEBUG
        // Bezier curves with x-coordinates outside the range [0,1] for internal
        // control points may have multiple values for t for a given value of x.
        // In this case, calls to SolveCurveX may produce ambiguous results.
        monotonically_increasing_ = p1x >= 0 && p1x <= 1 && p2x >= 0 && p2x <=
            1;
#endif
    }

    void init_gradients(const double p1x, const double p1y, const double p2x, const double p2y) {
        // End-point gradients are used to calculate timing function results
        // outside the range [0, 1].
        //
        // There are four possibilities for the gradient at each end:
        // (1) the closest control point is not horizontally coincident with regard to
        //     (0, 0) or (1, 1). In this case the line between the end point and
        //     the control point is tangent to the bezier at the end point.
        // (2) the closest control point is coincident with the end point. In
        //     this case the line between the end point and the far control
        //     point is tangent to the bezier at the end point.
        // (3) both internal control points are coincident with an endpoint. There
        //     are two special case that fall into this category:
        //     cubic_bezier(0, 0, 0, 0) and cubic_bezier(1, 1, 1, 1). Both are
        //     equivalent to linear.
        // (4) the closest control point is horizontally coincident with the end
        //     point, but vertically distinct. In this case the gradient at the
        //     end point is Infinite. However, this causes issues when
        //     interpolating. As a result, we break down to a simple case of
        //     0 gradient under these conditions.

        if (p1x > 0) {
            start_gradient_ = p1y / p1x;
        }
        else if (!p1y && p2x > 0) {
            start_gradient_ = p2y / p2x;
        }
        else if (!p1y && !p2y) {
            start_gradient_ = 1;
        }
        else {
            start_gradient_ = 0;
        }

        if (p2x >= 1) {
            if (p2y != 1 || p1x >= 1) {
                end_gradient_ = p2y == 1 && p1y == 1 ? 1 : 0;
            }
            else {
                end_gradient_ = (p1y - 1) / (p1x - 1);
            }
        }
        else {
            end_gradient_ = (p2y - 1) / (p2x - 1);
        }
    }

    void init_range(const double p1y, const double p2y) {
        range_min_ = 0;
        range_max_ = 1;
        if (0 <= p1y && p1y < 1 && 0 <= p2y && p2y <= 1) {
            return;
        }

        const double epsilon = bezier_epsilon;

        // Represent the function's derivative in the form at^2 + bt + c
        // as in sampleCurveDerivativeY.
        // (Technically this is (dy/dt)*(1/3), which is suitable for finding zeros
        // but does not actually give the slope of the curve.)
        const double a = 3.0 * ay_;
        const double b = 2.0 * by_;
        const double c = cy_;

        // Check if the derivative is constant.
        if (std::abs(a) < epsilon && std::abs(b) < epsilon) {
            return;
        }

        // Zeros of the function's derivative.
        double t1 = 0;
        double t2 = 0;

        if (std::abs(a) < epsilon) {
            // The function's derivative is linear.
            t1 = -c / b;
        }
        else {
            // The function's derivative is a quadratic. We find the zeros of this
            // quadratic using the quadratic formula.
            const double discriminant = b * b - 4 * a * c;
            if (discriminant < 0) {
                return;
            }
            const double discriminant_sqrt = std::sqrt(discriminant);
            t1 = (-b + discriminant_sqrt) / (2 * a);
            t2 = (-b - discriminant_sqrt) / (2 * a);
        }

        double sol1 = 0;
        double sol2 = 0;

        // If the solution is in the range [0,1] then we include it, otherwise we
        // ignore it.

        // An interesting fact about these beziers is that they are only
        // actually evaluated in [0,1]. After that we take the tangent at that point
        // and linearly project it out.
        if (0 < t1 && t1 < 1) {
            sol1 = sample_curve_y(t1);
        }

        if (0 < t2 && t2 < 1) {
            sol2 = sample_curve_y(t2);
        }

        range_min_ = std::min({range_min_, sol1, sol2});
        range_max_ = std::max({range_max_, sol1, sol2});
    }

    void init_spline() {
        const double delta_t = 1.0 / (CUBIC_BEZIER_SPLINE_SAMPLES - 1);
        for (int i = 0; i < CUBIC_BEZIER_SPLINE_SAMPLES; i++) {
            spline_samples_[i] = sample_curve_x(i * delta_t);
        }
    }

    double get_default_epsilon() const {
        return bezier_epsilon;
    }

    // Given an x value, find a parametric value it came from.
    // x must be in [0, 1] range. Doesn't use gradients.
    double solve_curve_x(const double x, const double epsilon) const {
        double t0{};
        double t1 = 0;
        double t2 = x;
        double x2{};
        int i;

        // Linear interpolation of spline curve for initial guess.
        const double delta_t = 1.0 / (CUBIC_BEZIER_SPLINE_SAMPLES - 1);
        for (i = 1; i < CUBIC_BEZIER_SPLINE_SAMPLES; i++) {
            if (x <= spline_samples_[i]) {
                t1 = delta_t * i;
                t0 = t1 - delta_t;
                t2 = t0 + (t1 - t0) * (x - spline_samples_[i - 1]) / (spline_samples_[i] - spline_samples_[i - 1]);
                break;
            }
        }

        // Perform a few iterations of Newton's method -- normally very fast.
        // See https://en.wikipedia.org/wiki/Newton%27s_method.
        const double newton_epsilon = std::min(bezier_epsilon, epsilon);
        for (i = 0; i < max_newton_iterations_; i++) {
            x2 = sample_curve_x(t2) - x;

            if (std::fabs(x2) < newton_epsilon) {
                return t2;
            }

            const double d2 = sample_curve_derivative_x(t2);
            if (std::fabs(d2) < bezier_epsilon) {
                break;
            }

            t2 = t2 - x2 / d2;
        }

        if (std::fabs(x2) < epsilon) {
            return t2;
        }

        // Fall back to the bisection method for reliability.
        while (t0 < t1) {
            x2 = sample_curve_x(t2);
            if (std::fabs(x2 - x) < epsilon) {
                return t2;
            }

            (x > x2 ? t0 : t1) = t2;
            t2 = (t1 + t0) * 0.5;
        }

        // Failure.
        return t2;
    }

    // Evaluates y at the given x with default epsilon.
    double solve(const double x) const {
        return solve_with_epsilon(x, bezier_epsilon);
    }

    double get_x1() const {
        return cx_ / 3.0;
    }

    double get_y1() const {
        return cy_ / 3.0;
    }

    double get_x2() const {
        return (bx_ + cx_) / 3.0 + get_x1();
    }

    double get_y2() const {
        return (by_ + cy_) / 3.0 + get_y1();
    }

private:
    double ax_;
    double bx_;
    double cx_;

    double ay_;
    double by_;
    double cy_;

    double start_gradient_;
    double end_gradient_;

    double range_min_;
    double range_max_;

    double spline_samples_[CUBIC_BEZIER_SPLINE_SAMPLES];

#ifndef NDEBUG
    // Guard against attempted to solve for t given x in the event that the curve
    // may have multiple values for t for some values of x in [0, 1].
    bool monotonically_increasing_;
#endif
};
