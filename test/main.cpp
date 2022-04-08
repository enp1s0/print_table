#include <print_table.hpp>

int main() {
	std::vector<std::map<std::string, std::string>> table;

	for (unsigned i = 0; i < 10; i++) {
		std::map<std::string, std::string> row;
		row.insert(std::make_pair("N"   , std::to_string(i)));
		row.insert(std::make_pair("N^2" , std::to_string(i * i)));
		row.insert(std::make_pair("test", "TEST-" + std::to_string(i * i * i * i)));
		table.push_back(row);
	}

	std::printf("--------------------------------------\n");
	std::vector<std::string> cols = {"N", "N^2", "test"};
	mtk::print_table::print_table(table, cols);

	std::printf("--------------------------------------\n");
	std::vector<std::string> col_names = {"n", "n^2", "TEST"};
	mtk::print_table::print_table(table, cols, col_names);
}
