#include <tabla/tabla.hpp>

#include <gtest/gtest.h>

struct Foo {
  int a;
  std::string b;
};

constexpr auto FooRow = tabla::describe_row(
  [](std::ostream& os, const Foo& f) { os << f.a; },
  [](std::ostream& os, const Foo& f) { os << f.b; }
);

TEST(Test, Simple) {
  Foo v{ .a = 42, .b = "Hi there" };
  tabla::print_table<Foo, FooRow>(std::cout, v);
}
