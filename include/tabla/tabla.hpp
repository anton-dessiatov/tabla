#pragma once

#include <ostream>
#include <tuple>
#include <type_traits>

namespace tabla {

template <std::size_t Cols, typename Accessor>
struct RowDescLeaf {
  Accessor accessor;
};

template <typename T> struct tag{ using type = T; };

template <typename Seq, typename...>
struct RowDescImpl;

template <std::size_t... Is, typename... Ts>
struct RowDescImpl<std::index_sequence<Is...>, Ts...> : RowDescLeaf<Is, Ts>...
{
    constexpr RowDescImpl(Ts... args) : RowDescLeaf<Is, Ts>{args}... {}
    using size = std::integral_constant<std::size_t, sizeof...(Ts)>;
};

template <typename T, std::size_t I> constexpr const T& get(const RowDescLeaf<I, T>& t) { return t.accessor; }
template <typename T, std::size_t I> constexpr T& get(RowDescLeaf<I, T>& t) { return t.accessor; }
template <std::size_t I, typename T> constexpr const T& get(const RowDescLeaf<I, T>& t) { return t.accessor; }
template <std::size_t I, typename T> constexpr T& get(RowDescLeaf<I, T>& t) { return t.accessor; }

template <std::size_t I, typename T>
tag<T> row_desc_element_tag(const RowDescLeaf<I, T>&);

template <std::size_t I, typename RowDesc>
using RowDescElement = decltype(tuple_element_tag<I>(std::declval<RowDesc>()));

template <std::size_t I, typename RowDesc>
using RowDescElementT = typename RowDescElement<I, RowDesc>::type;

template <typename RowDesc>
struct RowDescSize : public RowDesc::size {};

template <class RowDesc, class F>
constexpr decltype(auto) for_each(RowDesc&& desc, F&& f)
{
    return [] <std::size_t... I>
    (RowDesc&& desc, F&& f, std::index_sequence<I...>)
    {
        (f(get<I>(desc)), ...);
        return f;
    }(std::forward<RowDesc>(desc), std::forward<F>(f),
      // std::make_index_sequence<RowDesc::size>{});
      std::make_index_sequence<RowDescSize<std::remove_reference_t<RowDesc>>::value>{});
      // std::make_index_sequence<std::tuple_size<std::remove_reference_t<RowDesc>>::value>{});
}

template <typename ... Ts>
using RowDesc = RowDescImpl<std::make_index_sequence<sizeof...(Ts)>, Ts...>;

template<typename... Accessors>
constexpr auto describe_row(Accessors... acc) -> RowDesc<Accessors...> {
  return RowDesc<Accessors...>(acc...);
}

template<typename T, auto rows>
void print_table(std::ostream& os, const T& v) {
  for_each(rows, [&os, &v](auto accessor) { accessor(os, v); });
}

} // namespace tabla
