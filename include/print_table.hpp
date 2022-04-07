#ifndef __PRINT_TABLE_HPP__
#define __PRINT_TABLE_HPP__
#include <vector>
#include <unordered_map>

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
		std::vector<std::string> col_names,
		std::unordered_map<std::string, std::size_t> max_col_name_length,
		const unsigned padding,
		FILE* const output) {
	// Make a col name table row to input to `print_row` above.
	std::unordered_map<std::string, std::string> col_names_row;
	for (const auto& col_name : col_names) {
		col_names_row.insert(std::make_pair(col_name, col_name));
	}

	print_row(col_names, col_names_row, max_col_name_length, padding, output);
}

} // namespace detail

inline void print_table(
		const table_t table,
		const std::vector<std::string> col_names,
		FILE* output = stdout
		) {
	// Calculate the each column width
	std::unordered_map<std::string, std::size_t> max_col_name_length;
	for (const auto &col_name : col_names) {
		max_col_name_length.insert(std::make_pair(col_name, col_name.length()));
	}

	for (const auto &row : table) {
		for (const auto &col_name : col_names) {
			max_col_name_length[col_name] = std::max(max_col_name_length[col_name], row.at(col_name).length());
		}
	}

	constexpr auto padding = 1;
	unsigned table_width = 1;
	for (const auto& col_name : col_names) {
		table_width += (max_col_name_length[col_name] + padding * 2 + 1);
	}

	// Output col names
	detail::print_hline(col_names, max_col_name_length, padding, output);
	detail::print_row(col_names, max_col_name_length, padding, output);
	detail::print_hline(col_names, max_col_name_length, padding, output);
	for (const auto &row : table) {
		detail::print_row(col_names, row, max_col_name_length, padding, output);
	}
	detail::print_hline(col_names, max_col_name_length, padding, output);
}
} // namespace print_table
} // namespace mtk
#endif
