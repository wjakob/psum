#include <immintrin.h>

/// Vectorized implementation using Intel AVX instructions
float psum_2(float *x, size_t size) {
    __m256 r { 0 }, z { 0 };

    for (size_t i = 0; i < size / 8; ++i) {
        __m256 xf = _mm256_loadu_ps(x);
        r = _mm256_add_ps(_mm256_max_ps(xf, z), r);
        x += 8;
    }

    float t[8];
    _mm256_storeu_ps(t, r);
    for (int i = 1; i < 8; ++i)
        t[0] += t[i];
    return t[0];
}

/// Vectorized AVX implementation with more instruction-level parallelism
float psum_3(float *x, size_t size) {
    __m256 r0 { 0 }, r1{ 0 }, r2 { 0 }, r3 { 0 }, z{ 0 };

    for (size_t i = 0; i < size / 32; ++i) {
        __m256 x0 = _mm256_loadu_ps(x);
        __m256 x1 = _mm256_loadu_ps(x+8);
        __m256 x2 = _mm256_loadu_ps(x+16);
        __m256 x3 = _mm256_loadu_ps(x+24);
        r0 = _mm256_add_ps(_mm256_max_ps(x0, z), r0);
        r1 = _mm256_add_ps(_mm256_max_ps(x1, z), r1);
        r2 = _mm256_add_ps(_mm256_max_ps(x2, z), r2);
        r3 = _mm256_add_ps(_mm256_max_ps(x3, z), r3);
        x += 32;
    }

    r0 = _mm256_add_ps(_mm256_add_ps(r0, r1),
                       _mm256_add_ps(r2, r3));

    float t[8];
    _mm256_storeu_ps(t, r0);
    for (int i = 1; i < 8; ++i)
        t[0] += t[i];
    return t[0];
}

