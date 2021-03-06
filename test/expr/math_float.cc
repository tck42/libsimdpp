/*  Copyright (C) 2014  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#include <simdpp/simd.h>
#include "../utils/test_suite.h"
#include "../utils/test_helpers.h"
#include "../common/vectors.h"
#include "../common/masks.h"


template<class V, unsigned B>
void test_expr_math_float_v(SeqTestSuite& ts)
{
    SIMDPP_ARCH_NAMESPACE::Vectors<16,16> v;

    using namespace simdpp;

    for (unsigned i = 0; i < 4; ++i) {
        V a = load(v.pu8+(i*4+0)*B);
        V b = load(v.pu8+(i*4+1)*B);
        V c = load(v.pu8+(i*4+2)*B);
        V d = load(v.pu8+(i*4+3)*B);

        // operators
        TEST_CMP_VEC(ts, add(a, b), a + b);
        TEST_CMP_VEC(ts, add(a, mul(b, c)), a + b * c);
        TEST_CMP_VEC(ts, add(a, sub(b, c)), a + (b - c));
        TEST_CMP_VEC(ts, add(a, abs(b)), a + abs(b));
        TEST_CMP_VEC(ts, mul(a, b), a * b);
        TEST_CMP_VEC(ts, mul(a, mul(b, c)), a * b * c);
        TEST_CMP_VEC(ts, mul(a, sub(b, c)), a * (b - c));
        TEST_CMP_VEC(ts, mul(a, abs(b)), a * abs(b));
        TEST_CMP_VEC(ts, mul(a, sub(b, bit_not(c))), a * (b - ~c));

        // expressions
        TEST_CMP_VEC(ts, add(a, add(b, c)), add(a, add(b, c).eval()));
        TEST_CMP_VEC(ts, add(add(b, c), a), add(add(b, c).eval(), a));
        TEST_CMP_VEC(ts, sub(a, sub(b, c)), sub(a, sub(b, c).eval()));
        TEST_CMP_VEC(ts, sub(sub(b, c), a), sub(sub(b, c).eval(), a));
        TEST_CMP_VEC(ts, mul(a, mul(b, c)), mul(a, mul(b, c).eval()));
        TEST_CMP_VEC(ts, mul(mul(b, c), a), mul(mul(b, c).eval(), a));
        TEST_CMP_VEC(ts, fmadd(a, d, fmadd(b, c, a)), fmadd(a, d, fmadd(b, c, a).eval()));
        TEST_CMP_VEC(ts, fmadd(a, fmadd(b, c, a), d), fmadd(a, fmadd(b, c, a).eval(), d));
        TEST_CMP_VEC(ts, fmadd(fmadd(b, c, a), a, d), fmadd(fmadd(b, c, a).eval(), a, d));
        TEST_CMP_VEC(ts, fmsub(a, d, fmsub(b, c, a)), fmsub(a, d, fmsub(b, c, a).eval()));
        TEST_CMP_VEC(ts, fmsub(a, fmsub(b, c, a), d), fmsub(a, fmsub(b, c, a).eval(), d));
        TEST_CMP_VEC(ts, fmsub(fmsub(b, c, a), a, d), fmsub(fmsub(b, c, a).eval(), a, d));
        TEST_CMP_VEC(ts, abs(mul(a, b)), abs(mul(a, b).eval()));
        TEST_CMP_VEC(ts, neg(mul(a, b)), neg(mul(a, b).eval()));

        // scalar arguments
        TEST_CMP_VEC(ts, add(a, make_float<V>(1234.1234f)), a + 1234.1234f);
        TEST_CMP_VEC(ts, add(make_float<V>(1234.1234f), a), 1234.1234f + a);
        TEST_CMP_VEC(ts, add(a, make_int<V>(1234)), a + 1234);
        TEST_CMP_VEC(ts, add(make_int<V>(1234), a), 1234 + a);
        // TEST_CMP_VEC(ts, add(a, make_int<V>(1234ll)), a + 1234ll);
        // TEST_CMP_VEC(ts, add(make_int<V>(1234ll), a), 1234ll + a);
        TEST_CMP_VEC(ts, add(a, make_int<V>(0x80000000)), a + 0x80000000);
        TEST_CMP_VEC(ts, add(make_int<V>(0x80000000), a), 0x80000000 + a);
        TEST_CMP_VEC(ts, add(a, make_uint<V>(0x80000000)), a + 0x80000000);
        TEST_CMP_VEC(ts, add(make_uint<V>(0x80000000), a), 0x80000000 + a);
        TEST_CMP_VEC(ts, add(a, make_int<V>(0xf12341234)), a + 0xf12341234);
        TEST_CMP_VEC(ts, add(make_int<V>(0xf12341234), a), 0xf12341234 + a);
        // TEST_CMP_VEC(ts, add(a, make_int<V>(0xf12341234ull)), a + 0xf12341234ull);
        // TEST_CMP_VEC(ts, add(make_int<V>(0xf12341234ull), a), 0xf12341234ull + a);
    }
}


void test_expr_math_float(SeqTestSuite& ts)
{
    using namespace simdpp;

    test_expr_math_float_v<float32<4>, 16>(ts);
    test_expr_math_float_v<float64<2>, 16>(ts);
}
