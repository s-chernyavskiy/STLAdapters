#include <iostream>
#include <vector>

template<typename func>
struct filter {
  func f;
  explicit filter(func f) : f(f) {}
  std::vector<int> operator()(const std::vector<int>& v) const {
    std::vector<int> ans;
    for (auto& i : v) {
      if (f(i)) {
        ans.push_back(i);
      }
    }
    return ans;
  }
};

template<typename func>
struct transform {
  func f;
  explicit transform(func f) : f(f) {}
  std::vector<int> operator()(const std::vector<int>& v) const {
    std::vector<int> ans;
    for (auto& i : v) {
      ans.push_back(f(i));
    }
    return ans;
  }
};

template<typename func>
auto operator|(const std::vector<int>& v, transform<func> t) {
  return t(v);
}

template<typename func>
auto operator|(const std::vector<int>& v, filter<func> f) {
  return f(v);
}

int main() {
  std::vector<int> v = {1, 2, 3, 4, 5, 6};

  for (auto i : v | transform([](int i) { return i * i; }) | filter([](int i) { return i % 2 == 0; }))
    std::cout << i << " ";

  std::cout << std::endl;

  auto transformed = v | transform([](int i) { return i * i;} );

  for (auto i : transformed)
    std::cout << i << " ";

  return 0;
}
