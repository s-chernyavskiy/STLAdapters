#include <vector>

#include <lib/adapter.hpp>

int main() {
  std::vector<int> v = {1,2,3,4,5,6};

  for(int i : v | luvabl::filter([](int i){return i % 2;}) | luvabl::transform([](int i){return i * i;}))
    std::cout << i << " ";

  return 0;
}
