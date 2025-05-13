#pragma once

#include <cstddef>
#include <type_traits>

template <size_t N, size_t M>
struct Check
    : std::integral_constant<
          bool,
          std::conditional_t<(N % M == 0), std::integral_constant<bool, true>,
                             std::integral_constant<bool, false>>{}> {};

template <size_t N, size_t M>
struct CheckLoop
    : std::integral_constant<
          bool, std::conditional_t<Check<N, M>::value,
                                   std::integral_constant<bool, false>,
                                   CheckLoop<N, M - 1>>{}> {};

template <size_t N>
struct CheckLoop<N, 1> : std::integral_constant<bool, true> {};

template <size_t N>
struct isPrime : CheckLoop<N, N - 1> {};

template <>
struct isPrime<1> : std::integral_constant<bool, false> {};

template <>
struct isPrime<0> : std::integral_constant<bool, false> {};

template <size_t N, size_t M>
struct PrimeHelper
    : std::integral_constant<
          size_t,
          std::conditional_t<isPrime<M>::value, PrimeHelper<N - 1, M + 1>,
                             PrimeHelper<N, M + 1>>{}> {};

template <size_t M>
struct PrimeHelper<0, M> : std::integral_constant<size_t, M - 1> {};

template <size_t N>
struct Prime : PrimeHelper<N, 2> {};
