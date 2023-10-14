#include <immintrin.h>

/// Vectorized implementation using Intel AVX512 instructions
float psum_2(float *x, size_t size) {
    __m512 r { 0 }, z { 0 };

    for (size_t i = 0; i < size / 16; ++i) {
        __m512 xf = _mm512_loadu_ps(x);
        r = _mm512_add_ps(_mm512_max_ps(xf, z), r);
        x += 16;
    }

    float t[16];
    _mm512_storeu_ps(t, r);
    for (int i = 1; i < 16; ++i)
        t[0] += t[i];
    return t[0];
}

/// Vectorized AVX512 implementation with more instruction-level parallelism
float psum_3(float *x, size_t size) {
    __m512 r0 { 0 }, r1{ 0 }, r2 { 0 }, r3 { 0 }, z{ 0 };

    for (size_t i = 0; i < size / 64; ++i) {
        __m512 x0 = _mm512_loadu_ps(x);
        __m512 x1 = _mm512_loadu_ps(x+16);
        __m512 x2 = _mm512_loadu_ps(x+32);
        __m512 x3 = _mm512_loadu_ps(x+48);
        r0 = _mm512_add_ps(_mm512_max_ps(x0, z), r0);
        r1 = _mm512_add_ps(_mm512_max_ps(x1, z), r1);
        r2 = _mm512_add_ps(_mm512_max_ps(x2, z), r2);
        r3 = _mm512_add_ps(_mm512_max_ps(x3, z), r3);
        x += 64;
    }

    r0 = _mm512_add_ps(_mm512_add_ps(r0, r1),
                       _mm512_add_ps(r2, r3));

    float t[16];
    _mm512_storeu_ps(t, r0);
    for (int i = 1; i < 16; ++i)
        t[0] += t[i];
    return t[0];
}
