#pragma once

#include <iostream>

namespace luvabl {

template<class Container>
concept Base = requires(Container c) {
  c.begin();
  c.end();
};

template<class Container>
concept Pushbackable = requires(Container c) {
  { c.push_back(std::declval<typename Container::value_type>()) } -> std::same_as<void>;
  requires Base<Container>;
};

template<class Container>
concept RandomAccess = requires(Container c) {
  requires std::same_as<typename std::iterator_traits<typename Container::iterator>::iterator_category,
               std::random_access_iterator_tag>;
  requires Pushbackable<Container>;
};

template<class Container>
concept Associative = requires(Container c) {
  typename Container::key_type;
  typename Container::mapped_type;
};

struct take {
  size_t n;
  explicit take(size_t n) noexcept: n(n) {}
  take& operator=(const take&) = default;
  template<RandomAccess Container>
  auto operator()(const Container& c) const {
    Container ans;
    if (c.size() < n) {
      std::cerr << "Error: Can't take more elements than there are present in the container." << std::endl;
      exit(EXIT_FAILURE);
    }
    for (auto it = c.begin(); it != c.end() - (c.size() - n); ++it) {
      ans.push_back(*it);
    }
    return ans;
  }
};

struct drop {
  size_t n;
  explicit drop(size_t n) noexcept: n(n) {}
  drop& operator=(const drop&) = default;
  template<RandomAccess Container>
  auto operator()(const Container& c) const {
    Container ans;
    if (c.size() < n) {
      std::cerr << "Error: Can't drop more elements than there are present in the container." << std::endl;
      exit(EXIT_FAILURE);
    }
    for (auto it = c.begin() + n; it != c.end(); ++it) {
      ans.push_back(*it);
    }
    return ans;
  }
};

template<typename Func>
struct filter {
  Func f;
  explicit filter(Func f) noexcept: f(f) {}
  filter& operator=(const filter&) = default;

  template<Pushbackable Container>
  auto operator()(const Container& c) const {
    Container ans;
    for (auto& i : c) {
      if (f(i)) {
        ans.push_back(i);
      }
    }
    return ans;
  }
};

template<typename Func>
struct transform {
  Func f;
  explicit transform(Func f) noexcept: f(f) {}
  transform& operator=(const transform&) = default;
  template<Pushbackable Container>
  auto operator()(const Container& c) const {
    Container ans;
    for (auto& i : c) {
      ans.push_back(f(i));
    }
    return ans;
  }
};

struct reverse {
  explicit reverse() noexcept = default;
  reverse& operator=(const reverse&) = default;
  template<Base Container>
  auto operator()(const Container& c) const noexcept {
    Container ans;
    for (auto it = --c.end(); it != --c.begin(); --it) {
      ans.push_back(*it);
    }
    return ans;
  }
};

template<typename Func>
struct keys {
  Func f;
  explicit keys(Func f) noexcept: f(f) {}
  keys& operator=(const keys&) = default;
  template<Associative Container>
  auto operator()(const Container& c) const noexcept {
    Container ans;
    for (auto& i : c) {
      if (f(i.first)) {
        ans.insert(i);
      }
    }
    return ans;
  }
};

template<typename Func>
struct values {
  Func f;
  explicit values(Func f) noexcept: f(f) {}
  values& operator=(const values&) = default;
  template<Associative Container>
  auto operator()(const Container& c) const noexcept {
    Container ans;
    for (auto& i : c) {
      if (f(i.second)) {
        ans.insert(i);
      }
    }
    return ans;
  }
};

template<Pushbackable Container, typename Func>
auto operator|(const Container& c, transform<Func> t) {
  return t(c);
}

template<Pushbackable Container, typename Func>
auto operator|(const Container& c, filter<Func> f) {
  return f(c);
}

template<RandomAccess Container>
auto operator|(const Container& c, take t) {
  return t(c);
}

template<RandomAccess Container>
auto operator|(const Container& c, drop t) {
  return t(c);
}

template<Base Container>
auto operator|(const Container& c, reverse r) {
  return r(c);
}

template<Associative Container, typename Func>
auto operator|(const Container& c, keys<Func> k) {
  return k(c);
}

template<Associative Container, typename Func>
auto operator|(const Container& c, values<Func> v) {
  return v(c);
}

} // namespace luvabl