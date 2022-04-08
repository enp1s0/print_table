#ifndef __PRINT_TABLE_HPP__
#define __PRINT_TABLE_HPP__
#include <vector>
#include <unordered_map>
#include <map>

namespace mtk {
namespace print_table {
using row_t = std::unordered_map<std::string, std::string>;
using table_t = std::vector<row_t>;

namespace detail {
inline void print_hline(
		std::vector<std::string> col_names,
		std::unordered_map<std::string, std::size_t> max_col_name_length,
		const unsigned padding,
		FILE* const output) {
	for (const auto& col_name : col_names) {
		const auto width = max_col_name_length.at(col_name);
		std::fprintf(output, "+");
		for (std::size_t i = 0; i < width + padding * 2; i++) {
			std::printf("-");
		}
	}
	std::fprintf(output, "+\n");
}

inline void print_row(
		std::vector<std::string> col_names,
		row_t row,
		std::unordered_map<std::string, std::size_t> max_col_name_length,
		const unsigned padding,
		FILE* const output) {
	for (const auto& col_name : col_names) {
		const auto value = row.at(col_name);
		const auto width = max_col_name_length.at(col_name);
		std::fprintf(output, "|");
		// left padding
		for (std::size_t i = 0; i < padding; i++) {
			std::printf(" ");
		}
		// main content
		std::printf("%*s", static_cast<int>(width), value.c_str());
		// right padding
		for (std::size_t i = 0; i < padding; i++) {
			std::printf(" ");
		}
	}
	std::fprintf(output, "|\n");
}

inline void print_row(
		std::vector<std::string> cols,
		std::vector<std::string> col_names,
		std::unordered_map<std::string, std::size_t> max_col_name_length,
		const unsigned padding,
		FILE* const output) {
	// Make a col name table row to input to `print_row` above.
	std::unordered_map<std::string, std::string> col_names_row;
	for (unsigned i = 0; i < cols.size(); i++) {
		col_names_row.insert(std::make_pair(cols[i], col_names[i]));
	}

	print_row(cols, col_names_row, max_col_name_length, padding, output);
}

} // namespace detail

inline void print_table(
		const table_t table,
		const std::vector<std::string> cols,
		const std::vector<std::string> col_names,
		FILE* output = stdout
		) {
	// Calculate the each column width
	std::unordered_map<std::string, std::size_t> max_col_name_length;
	for (unsigned i = 0; i < col_names.size(); i++) {
		max_col_name_length.insert(std::make_pair(cols[i], col_names[i].length()));
	}

	for (const auto &row : table) {
		for (const auto &col_name : cols) {
			max_col_name_length[col_name] = std::max(max_col_name_length[col_name], row.at(col_name).length());
		}
	}

	constexpr auto padding = 1;
	unsigned table_width = 1;
	for (const auto& col_name : cols) {
		table_width += (max_col_name_length[col_name] + padding * 2 + 1);
	}

	// Output col names
	detail::print_hline(cols, max_col_name_length, padding, output);
	detail::print_row(cols, col_names, max_col_name_length, padding, output);
	detail::print_hline(cols, max_col_name_length, padding, output);
	for (const auto &row : table) {
		detail::print_row(cols, row, max_col_name_length, padding, output);
	}
	detail::print_hline(cols, max_col_name_length, padding, output);
}

inline void print_table(
		const std::vector<std::map<std::string, std::string>>& table,
		const std::vector<std::string> cols,
		const std::vector<std::string> col_names,
		FILE* output = stdout
		) {
	table_t t;
	for (const auto& row : table) {
		row_t r;
		for (const auto& c : row) {
			r.insert(std::make_pair(c.first, c.second));
		}
		t.push_back(r);
	}
	
	print_table(t, cols, col_names, output);
}

template <class TABLE_T>
inline void print_table(
		const TABLE_T& table,
		const std::vector<std::string> cols,
		FILE* output = stdout
		) {
	print_table(table, cols, cols, output);
}
} // namespace print_table
} // namespace mtk
#endif
