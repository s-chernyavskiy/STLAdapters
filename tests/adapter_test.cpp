#include <gtest/gtest.h>

#include <lib/adapter.hpp>

TEST(ADAPTER, EMPTY_ADAPTER) {
  std::vector<int> a = {1, 2, 3, 4};

  auto modified = a | luvabl::transform([](int i) {return i; });

  ASSERT_EQ(modified, a);
}

TEST(ADAPTER, TRANSFORM_ADAPTER) {
  std::vector<int> a = {1, 2, 3, 4};

  auto modified = a | luvabl::transform([](int i){ return i * 2; });

  std::vector<int> expected = {2, 4, 6, 8};

  ASSERT_EQ(modified, expected);
}

TEST(ADAPTER, FILTER_ADAPTER) {
  std::vector<int> a = {1, 2, 3, 4};

  auto modified = a | luvabl::filter([](int i) { return i % 2 == 0; });

  std::vector<int> expected = {2, 4};

  ASSERT_EQ(modified, expected);
}

TEST(ADAPTER, TAKE_ADAPTER) {
  std::vector<int> a = {1, 2, 3, 4, 5};

  auto modified = a | luvabl::take(2);

  std::vector<int> expected = {1, 2};

  ASSERT_EQ(modified, expected);
}

TEST(ADAPTER, TAKE_ADAPTER_ILLEGAL) {
  std::vector<int> a = {1, 2, 3, 4, 5};

  ASSERT_DEATH(a | luvabl::take(6), "Error: Can't take more elements than there are present in the container.");
}

TEST(ADAPTER, DROP_ADAPTER) {
  std::vector<int> a = {1, 2, 3, 4, 5};

  auto modified = a | luvabl::drop(3);

  std::vector<int> expected = {4, 5};

  ASSERT_EQ(modified, expected);
}

TEST(ADAPTER, DROP_ADAPTER_ILLEGAL) {
  std::vector<int> a = {1, 2, 3, 4, 5};

  ASSERT_DEATH(a | luvabl::drop(6), "Error: Can't drop more elements than there are present in the container.");
}

TEST(ADAPTER, REVERSE_ADAPTER) {
  std::vector<int> a = {1, 2, 3, 4, 5};

  auto modified = a | luvabl::reverse();

  std::vector<int> expected = {5, 4, 3, 2, 1};

  ASSERT_EQ(modified, expected);
}

TEST(ADAPTER, KEYS_ASSOCIATIVE_ADAPTER) {
  std::map<int, int> a = {{1, 2}, {3, 4}, {5, 6}};

  auto modified = a | luvabl::keys([](int i) { return i % 2 == 0; });

  std::map<int, int> expected = {};

  ASSERT_EQ(modified, expected);
}

TEST(ADAPTER, VALUES_ASSOCIATIVE_ADAPTER) {
  std::map<int, std::string> a = {{1, "foo"}, {3, "bar"}, {5, "bazzzingas"}};

  auto modified = a | luvabl::values([](const std::string& i) { return i.size() > 3; });

  std::map<int, std::string> expected = {{5, "bazzzingas"}};

  ASSERT_EQ(modified, expected);
}

TEST(ADAPTER, MULTIPLE_ADAPTER) {
  std::vector<int> a = {1, 2, 3, 4};

  auto modified = a
      | luvabl::filter([](int i) { return i % 2 == 0; })
      | luvabl::transform([](int i) { return i * i; });

  std::vector<int> expected = {4, 16};

  ASSERT_EQ(modified, expected);
}

TEST(ADAPTER, MULTIPLE_ADAPTER_SPLIT) {
  std::vector<int> a = {1, 2, 3, 4};

  auto filtered = a | luvabl::filter([](int i) { return i % 2 == 0; });
  auto transformed = filtered | luvabl::transform([](int i) { return i * i; });

  std::vector<int> expected = {4, 16};

  ASSERT_EQ(transformed, expected);
}

TEST(ADAPTER, MULPTIPLE_USAGES_OF_SAME_ENTITY) {
  auto func = [](int i) {
    return i % 2 == 0;
  };

  auto view = luvabl::filter(func);

  std::vector<int> a = {1, 2, 3};
  std::vector<int> b = {4, 5, 6};

  a = a | view;
  b = b | view;

  std::vector<int> expected_a = {2};
  std::vector<int> expected_b = {4, 6};

  ASSERT_TRUE((a == expected_a) && (b == expected_b));
}
