int x = 10;
#include <fmt/core.h>

#include <lista01/lista01.hpp>
import std;
import lista_modulo;

int main() {
  std::println("Olá {}", "Mundo!");
  fmt::println("Oi da FMT");
  std::println("foo() da .hpp = {}", foo());
  std::println("teste() do .cppm = {}", teste());
  return 0;
}
