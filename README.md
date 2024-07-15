# STL. Адаптеры.

Библиотека адаптеров для упрощенной работы с алгоритмами и контейнерами.

# Примеры работы адаптеров 

Адаптеры выполнены подобно схожим адаптерам в библиотеке [Ranges](https://en.cppreference.com/w/cpp/ranges)

```cpp
std::vector<int> v = {1,2,3,4,5,6};

auto removed = v | filter([](int i){return i % 2;});
auto result = removed | transform([](int i){return i * i;});

for (int i : result)
    std::cout << i << " ";
```

Однако, этого результата можно достигнуть, написав еще более коротко, использовав [пайплайн, наподобие того как это принято в unix-системах](https://en.wikipedia.org/wiki/Pipeline_(Unix))

```cpp
std::vector<int> v = {1,2,3,4,5,6};

for(int i : v | filter([](int i){return i % 2;}) | transform([](int i){return i * i;}))
     std::cout << i << " ";
```

Еще одним значимым отличием такого подхода от изначального является то, что вычисления являются ленивыми, а создаваемые объекты не владеют массивом данных для решения данной задачи. Подобный подход в частонсти применяется в классах [std::string_view](https://en.cppreference.com/w/cpp/string/basic_string_view) и [std::span](https://en.cppreference.com/w/cpp/container/span)

### Список адаптеров

* transform - изменяют значения элементов наподобие того, как это делает алгоритм transform
* filter    - фильтрация по определенному признаку, признак передается в качестве аргумента
* take      - берет только N первых элементов
* drop      - пропускаем N первых элементов
* reverse   - реверсия
* keys      - ключи для ассоциативных контейнеров
* values    - значения для ассоциативных контейнеров

## NB

Все вышеуказанные сущности покрыты тестами, с помощью фреймворка [Google Test](http://google.github.io/googletest).