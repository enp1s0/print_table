#include <print_table.hpp>

int main() {
	mtk::print_table::table_t table;

	for (unsigned i = 0; i < 10; i++) {
		mtk::print_table::row_t row;
		row.insert(std::make_pair("N"   , std::to_string(i)));
		row.insert(std::make_pair("N^2" , std::to_string(i * i)));
		row.insert(std::make_pair("test", "TEST-" + std::to_string(i * i * i * i)));
		table.push_back(row);
	}

	std::vector<std::string> col_names = {"N", "N^2", "test"};

	mtk::print_table::print_table(table, col_names);
}
