#pragma once
#include <xlsxwriter.h>

#include "file_handling/tsp_file.h"
#include "Tests/Test_Compenents.h"

class ExcelCreator {
public:
	static inline int createExcel(const TSPFile& file) {
		lxw_workbook* workbook = workbook_new((file.m_name + ".xlsx").c_str());

		writeForCityCount(workbook, file);

		return workbook_close(workbook);
	}

private:
	static inline void writeForCityCount(lxw_workbook* workbook, const TSPFile& file) {
		lxw_worksheet* worksheet = workbook_add_worksheet(workbook, "CitySizes");

		lxw_row_t row = 1;

		for (const auto size : SIZES) {
			std::vector<const StatisticEntry*> entries;

			for (const auto& entry : file.getStatistics()) {
				if (entry.num_cities == size)
					entries.push_back(&entry);
			}

			if (entries.size() == 0)
				continue;

			std::string name = ("Cities" + std::to_string(size));
			worksheet_write_string(worksheet, row++, 1, name.c_str(), NULL);

			lxw_format* percentage_format = workbook_add_format(workbook);
			format_set_num_format(percentage_format, "0.00%");

			lxw_format* double_format = workbook_add_format(workbook);
			format_set_num_format(double_format, "0.00");

			std::string timeComparisonFormula("=[@TimeAverage]/" + name + "[[#Totals],[TimeAverage]]");
			std::string distanceComparisonFormula("=[@DistanceAverage]/" + name + "[[#Totals],[DistanceAverage]]");

			lxw_table_column col1 = { .header = "Algorithm", .total_string = "Totals", };
			lxw_table_column col2 = { .header = "TimeAverage", .total_function = LXW_TABLE_FUNCTION_AVERAGE, .format = double_format };
			lxw_table_column col3 = { .header = "DistanceAverage", .total_function = LXW_TABLE_FUNCTION_AVERAGE,.format = double_format};
			lxw_table_column col4 = { .header = "ValidRoutePercentage", .total_function = LXW_TABLE_FUNCTION_AVERAGE, .format = percentage_format };
			lxw_table_column col5 = { .header = "TimeComparison", .formula = timeComparisonFormula.c_str(), .total_function = LXW_TABLE_FUNCTION_NONE, .format = percentage_format};
			lxw_table_column col6 = { .header = "DistanceComparison", .formula = distanceComparisonFormula.c_str(), .total_function = LXW_TABLE_FUNCTION_NONE, .format = percentage_format };
			lxw_table_column col7 = { .header = "Performance", .formula = "=[@DistanceComparison]/[@TimeComparison]", .total_function = LXW_TABLE_FUNCTION_NONE, .format = percentage_format };

			lxw_table_column* columns[] = { &col1, &col2, &col3, &col4, &col5, &col6, &col7, NULL};

			lxw_table_options options = { .name = name.c_str(),
			.total_row = LXW_TRUE,
			.columns = columns};


			worksheet_add_table(worksheet, 
				row, 1,
				row + lxw_row_t(entries.size()) + 1, lxw_col_t(sizeof(columns)/sizeof(lxw_table_column*) - 1),
				&options);

			for (const auto& entry : entries) {
				row++;

				std::string name = jsonconversion::constructionTypeToString(entry->Construction);
				if(entry->Construction == ConstructionType::StaticLookahead ||
					entry->Construction == ConstructionType::StaticLookaheadConvexHullInserstion)
					name += "(" + std::to_string(entry->args.max_depth) + ")";

				worksheet_write_string(worksheet, row, 1, name.c_str(), NULL);
				worksheet_write_number(worksheet, row, 2, entry->total_run_time.count() / (double)entry->number_of_valid_routes, double_format);
				worksheet_write_number(worksheet, row, 3, entry->total_final_distance / (double)entry->number_of_valid_routes, double_format);
				worksheet_write_number(worksheet, row, 4, entry->number_of_valid_routes / (double)entry->number_of_runs, percentage_format);
			}

			row += 3;

		}
	};

};
