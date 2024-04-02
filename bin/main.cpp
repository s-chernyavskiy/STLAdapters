#include <lib/adapter.hpp>

int main() {
  std::map<int, int> a = {{1, 2}, {3, 5}};
  for (auto& v : a | luvabl::values([](int i) { return i % 2; }) | luvabl::keys([](int i) { return i % 2; })) {
    std::cout << v.first << ' ' << v.second << '\n';
  }

  return 0;
}
