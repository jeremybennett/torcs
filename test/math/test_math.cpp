/***************************************************************************

    file                 : test_math.cpp
    created              : 2026-03-27
    copyright            : (C) 2026 Open Racing Simulator contributors

 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

/**
 * @file test_math.cpp
 * Unit tests for the tmath vector library (v2t, v3t).
 * Compile with: make  (or see Makefile for manual flags)
 */

#include <cstdio>
#include <cmath>
#include <cstring>

#include <tmath/linalg_t.h>

// ---------------------------------------------------------------------------
// Minimal test framework
// ---------------------------------------------------------------------------

static int s_passed = 0;
static int s_failed = 0;

static void check(bool condition, const char* expr, const char* file, int line)
{
    if (condition) {
        ++s_passed;
    } else {
        ++s_failed;
        fprintf(stderr, "FAIL  %s:%d  %s\n", file, line, expr);
    }
}

#define CHECK(expr)          check((expr), #expr, __FILE__, __LINE__)
#define CHECK_NEAR(a, b, eps) check(fabs((double)(a) - (double)(b)) < (eps), \
                                    #a " ~= " #b, __FILE__, __LINE__)

// ---------------------------------------------------------------------------
// v2t tests
// ---------------------------------------------------------------------------

static void test_v2t_construction()
{
    vec2f v(3.0f, 4.0f);
    CHECK(v.x == 3.0f);
    CHECK(v.y == 4.0f);

    vec2f u(1.5f);
    CHECK(u.x == 1.5f);
    CHECK(u.y == 1.5f);

    vec2f copy(v);
    CHECK(copy.x == 3.0f);
    CHECK(copy.y == 4.0f);
}

static void test_v2t_arithmetic()
{
    vec2f a(1.0f, 2.0f);
    vec2f b(3.0f, 4.0f);

    vec2f sum = a + b;
    CHECK_NEAR(sum.x, 4.0f, 1e-6f);
    CHECK_NEAR(sum.y, 6.0f, 1e-6f);

    vec2f diff = b - a;
    CHECK_NEAR(diff.x, 2.0f, 1e-6f);
    CHECK_NEAR(diff.y, 2.0f, 1e-6f);

    vec2f neg = -a;
    CHECK_NEAR(neg.x, -1.0f, 1e-6f);
    CHECK_NEAR(neg.y, -2.0f, 1e-6f);

    vec2f scaled = a * 2.0f;
    CHECK_NEAR(scaled.x, 2.0f, 1e-6f);
    CHECK_NEAR(scaled.y, 4.0f, 1e-6f);

    vec2f divided = b / 2.0f;
    CHECK_NEAR(divided.x, 1.5f, 1e-6f);
    CHECK_NEAR(divided.y, 2.0f, 1e-6f);
}

static void test_v2t_dot_product()
{
    vec2f a(1.0f, 0.0f);
    vec2f b(0.0f, 1.0f);
    CHECK_NEAR(a * b, 0.0f, 1e-6f);  // perpendicular

    vec2f c(3.0f, 4.0f);
    vec2f d(1.0f, 2.0f);
    CHECK_NEAR(c * d, 11.0f, 1e-6f); // 3*1 + 4*2 = 11
}

static void test_v2t_length_and_normalize()
{
    vec2f v(3.0f, 4.0f);
    CHECK_NEAR(v.len(), 5.0f, 1e-5f);

    vec2f u(3.0f, 4.0f);
    u.normalize();
    CHECK_NEAR(u.len(), 1.0f, 1e-6f);
    CHECK_NEAR(u.x, 0.6f, 1e-6f);
    CHECK_NEAR(u.y, 0.8f, 1e-6f);
}

static void test_v2t_distance()
{
    vec2f a(0.0f, 0.0f);
    vec2f b(3.0f, 4.0f);
    CHECK_NEAR(a.dist(b), 5.0f, 1e-5f);
    CHECK_NEAR(b.dist(a), 5.0f, 1e-5f);

    // distance to self is zero
    CHECK_NEAR(a.dist(a), 0.0f, 1e-6f);
}

static void test_v2t_equality()
{
    vec2f a(1.0f, 2.0f);
    vec2f b(1.0f, 2.0f);
    vec2f c(1.0f, 3.0f);
    CHECK(a == b);
    CHECK(!(a == c));
    CHECK(a != c);
    CHECK(!(a != b));
}

static void test_v2t_approx_equals()
{
    vec2f a(1.0f, 2.0f);
    vec2f b(1.0001f, 2.0001f);
    CHECK(a.approxEquals(b, 0.001f));
    CHECK(!a.approxEquals(b, 0.00001f));
}

static void test_v2t_fake_cross_product()
{
    vec2f a(1.0f, 0.0f);
    vec2f b(0.0f, 1.0f);
    CHECK_NEAR(a.fakeCrossProduct(&b), 1.0f, 1e-6f);  // a X b = +1 (CCW)
    CHECK_NEAR(b.fakeCrossProduct(&a), -1.0f, 1e-6f); // b X a = -1 (CW)
}

static void test_v2t_compound_assignment()
{
    vec2f a(1.0f, 2.0f);
    vec2f b(3.0f, 4.0f);

    a += b;
    CHECK_NEAR(a.x, 4.0f, 1e-6f);
    CHECK_NEAR(a.y, 6.0f, 1e-6f);

    a -= b;
    CHECK_NEAR(a.x, 1.0f, 1e-6f);
    CHECK_NEAR(a.y, 2.0f, 1e-6f);

    a *= 2.0f;
    CHECK_NEAR(a.x, 2.0f, 1e-6f);
    CHECK_NEAR(a.y, 4.0f, 1e-6f);

    a /= 2.0f;
    CHECK_NEAR(a.x, 1.0f, 1e-6f);
    CHECK_NEAR(a.y, 2.0f, 1e-6f);
}

// ---------------------------------------------------------------------------
// v3t tests
// ---------------------------------------------------------------------------

static void test_v3t_construction()
{
    vec3f v(1.0f, 2.0f, 3.0f);
    CHECK(v.x == 1.0f);
    CHECK(v.y == 2.0f);
    CHECK(v.z == 3.0f);

    vec3f u(5.0f);
    CHECK(u.x == 5.0f);
    CHECK(u.y == 5.0f);
    CHECK(u.z == 5.0f);
}

static void test_v3t_arithmetic()
{
    vec3f a(1.0f, 2.0f, 3.0f);
    vec3f b(4.0f, 5.0f, 6.0f);

    vec3f sum = a + b;
    CHECK_NEAR(sum.x, 5.0f, 1e-6f);
    CHECK_NEAR(sum.y, 7.0f, 1e-6f);
    CHECK_NEAR(sum.z, 9.0f, 1e-6f);

    vec3f diff = b - a;
    CHECK_NEAR(diff.x, 3.0f, 1e-6f);
    CHECK_NEAR(diff.y, 3.0f, 1e-6f);
    CHECK_NEAR(diff.z, 3.0f, 1e-6f);

    vec3f scaled = a * 3.0f;
    CHECK_NEAR(scaled.x, 3.0f, 1e-6f);
    CHECK_NEAR(scaled.y, 6.0f, 1e-6f);
    CHECK_NEAR(scaled.z, 9.0f, 1e-6f);
}

static void test_v3t_dot_product()
{
    vec3f a(1.0f, 0.0f, 0.0f);
    vec3f b(0.0f, 1.0f, 0.0f);
    CHECK_NEAR(a * b, 0.0f, 1e-6f);  // perpendicular

    vec3f c(1.0f, 2.0f, 3.0f);
    vec3f d(4.0f, 5.0f, 6.0f);
    CHECK_NEAR(c * d, 32.0f, 1e-5f); // 1*4 + 2*5 + 3*6 = 32
}

static void test_v3t_cross_product()
{
    vec3f x(1.0f, 0.0f, 0.0f);
    vec3f y(0.0f, 1.0f, 0.0f);
    vec3f z(0.0f, 0.0f, 1.0f);

    vec3f r;
    x.crossProduct(y, r);
    CHECK_NEAR(r.x, 0.0f, 1e-6f);
    CHECK_NEAR(r.y, 0.0f, 1e-6f);
    CHECK_NEAR(r.z, 1.0f, 1e-6f);  // x X y = z

    y.crossProduct(x, r);
    CHECK_NEAR(r.z, -1.0f, 1e-6f); // y X x = -z
}

static void test_v3t_length_and_normalize()
{
    vec3f v(0.0f, 3.0f, 4.0f);
    CHECK_NEAR(v.len(), 5.0f, 1e-5f);

    vec3f u(0.0f, 3.0f, 4.0f);
    u.normalize();
    CHECK_NEAR(u.len(), 1.0f, 1e-6f);
    CHECK_NEAR(u.y, 0.6f, 1e-6f);
    CHECK_NEAR(u.z, 0.8f, 1e-6f);
}

static void test_v3t_equality()
{
    vec3f a(1.0f, 2.0f, 3.0f);
    vec3f b(1.0f, 2.0f, 3.0f);
    vec3f c(1.0f, 2.0f, 4.0f);
    CHECK(a == b);
    CHECK(!(a == c));
    CHECK(a != c);
}

// ---------------------------------------------------------------------------
// main
// ---------------------------------------------------------------------------

int main()
{
    // v2t tests
    test_v2t_construction();
    test_v2t_arithmetic();
    test_v2t_dot_product();
    test_v2t_length_and_normalize();
    test_v2t_distance();
    test_v2t_equality();
    test_v2t_approx_equals();
    test_v2t_fake_cross_product();
    test_v2t_compound_assignment();

    // v3t tests
    test_v3t_construction();
    test_v3t_arithmetic();
    test_v3t_dot_product();
    test_v3t_cross_product();
    test_v3t_length_and_normalize();
    test_v3t_equality();

    printf("Results: %d passed, %d failed\n", s_passed, s_failed);
    return s_failed == 0 ? 0 : 1;
}
