#ifndef _TRAITS_HPP_
#define _TRAITS_HPP_

#include <type_traits>

namespace traits {
template <typename T, typename... Types>
constexpr bool is_any_of_v = (std::is_same_v<T, Types> || ...);
}

#endif  // _TRAITS_HPP_