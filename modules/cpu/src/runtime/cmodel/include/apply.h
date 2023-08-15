#pragma once
#include <gsl/gsl-lite.hpp>

namespace detail {
#define APPLY_IMPL_FOR(i) for (index[i] = 0; index[i] < shape[i]; index[i]++)

template <class Callable>
void apply_1(gsl::span<const size_t> shape, Callable &&callable) noexcept {
    size_t index[1];
    APPLY_IMPL_FOR(0)
    callable(gsl::span(index));
}

template <class Callable>
void apply_2(gsl::span<const size_t> shape, Callable &&callable) noexcept {
    size_t index[2];
    APPLY_IMPL_FOR(0)
    APPLY_IMPL_FOR(1)
    callable(gsl::span(index));
}

template <class Callable>
void apply_3(gsl::span<const size_t> shape, Callable &&callable) noexcept {
    size_t index[3];
    APPLY_IMPL_FOR(0)
    APPLY_IMPL_FOR(1)
    APPLY_IMPL_FOR(2)
    callable(gsl::span(index));
}

template <class Callable>
void apply_4(gsl::span<const size_t> shape, Callable &&callable) noexcept {
    size_t index[4];
    APPLY_IMPL_FOR(0)
    APPLY_IMPL_FOR(1)
    APPLY_IMPL_FOR(2)
    APPLY_IMPL_FOR(3)
    callable(gsl::span(index));
}

template <class Callable>
void apply_5(gsl::span<const size_t> shape, Callable &&callable) noexcept {
    size_t index[5];
    APPLY_IMPL_FOR(0)
    APPLY_IMPL_FOR(1)
    APPLY_IMPL_FOR(2)
    APPLY_IMPL_FOR(3)
    APPLY_IMPL_FOR(4)
    callable(gsl::span(index));
}

template <class Callable>
void apply_generic(gsl::span<const size_t> shape,
                   Callable &&callable) noexcept {
    auto index_buffer = (size_t *)
#ifdef _WIN32
        _alloca
#else
        __builtin_alloca
#endif
        (sizeof(size_t) * shape.size());

    gsl::span<size_t> index(index_buffer, shape.size());
    std::fill(index.begin(), index.end(), 0);
    auto last_dim_idx = (int32_t)shape.size() - 1;
    while (true) {
        int dim = last_dim_idx;
        while (index[dim] == shape[dim]) {
            if (dim == 0) {
            }

            index[dim] = 0;
            index[--dim]++;
        }

        callable(index);
        index[last_dim_idx]++;
    }
}
} // namespace detail

template <class Callable>
void apply(gsl::span<const size_t> shape, Callable &&callable) noexcept {
    switch (shape.size()) {
    case 0:
        return callable(shape);
    case 1:
        return detail::apply_1(shape, std::forward<Callable>(callable));
    case 2:
        return detail::apply_2(shape, std::forward<Callable>(callable));
    case 3:
        return detail::apply_3(shape, std::forward<Callable>(callable));
    case 4:
        return detail::apply_4(shape, std::forward<Callable>(callable));
    case 5:
        return detail::apply_5(shape, std::forward<Callable>(callable));
    default:
        break;
    }

    return detail::apply_generic(shape, std::forward<Callable>(callable));
}