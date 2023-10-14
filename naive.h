/// Super-naive scalar implementation with branching
float psum_0(float *x, size_t size) {
    float r { 0.f };

    for (size_t i = 0; i < size; ++i) {
        if (x[i] >= 0) {
            r += x[i];
            if (std::isinf(r))
                abort();
        }
    }

    return r;
}

/// Naive scalar implementation, compiler optimizes branching away
float psum_1(float *x, size_t size) {
    float r { 0.f };

    for (size_t i = 0; i < size; ++i)
        r += fmaxf(x[i], 0.f);

    return r;
}
