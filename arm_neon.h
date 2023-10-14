#include <arm_neon.h>

/// Vectorized implementation using ARM NEON instructions
float psum_2(float *x, size_t size) {
    float32x4_t r { 0 }, z { 0 };

    for (size_t i = 0; i < size / 4; ++i) {
        float32x4_t xf = vld1q_f32(x);
        r = vaddq_f32(vmaxq_f32(xf, z), r);
        x += 4;
    }

    float t[4];
    vst1q_f32(t, r);
    for (int i = 1; i < 4; ++i)
        t[0] += t[i];
    return t[0];
}

/// Vectorized ARM NEON implementation with more instruction-level parallelism
float psum_3(float *x, size_t size) {
    float32x4_t r0 { 0 }, r1{ 0 }, r2 { 0 }, r3 { 0 }, z{ 0 };

    for (size_t i = 0; i < size / 16; ++i) {
        float32x4_t x0 = vld1q_f32(x);
        float32x4_t x1 = vld1q_f32(x+4);
        float32x4_t x2 = vld1q_f32(x+8);
        float32x4_t x3 = vld1q_f32(x+12);
        r0 = vaddq_f32(vmaxq_f32(x0, z), r0);
        r1 = vaddq_f32(vmaxq_f32(x1, z), r1);
        r2 = vaddq_f32(vmaxq_f32(x2, z), r2);
        r3 = vaddq_f32(vmaxq_f32(x3, z), r3);
        x += 16;
    }

    r0 = vaddq_f32(vaddq_f32(r0, r1),
                   vaddq_f32(r2, r3));

    float t[4];
    vst1q_f32(t, r0);
    for (int i = 1; i < 4; ++i)
        t[0] += t[i];
    return t[0];
}
