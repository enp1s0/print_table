# print_table

A simple table printing library in C++

## Sample
```cpp
// sample.cpp
// g++ sample.cpp -I/path/to/include
#include <print_table.hpp>

...

mtk::print_table::table_t table;

std::vector<std::string> col_names = {"N", "N^2", "test"};

mtk::print_table::print_table(table, col_names);
```

## License
MIT
