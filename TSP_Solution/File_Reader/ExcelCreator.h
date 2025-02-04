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
		worksheet_set_column_pixels(worksheet, 1, 1, 310, NULL);
		worksheet_set_column_pixels(worksheet, 2, 2, 128, NULL);
		worksheet_set_column_pixels(worksheet, 3, 3, 156, NULL);
		worksheet_set_column_pixels(worksheet, 4, 4, 199, NULL);
		worksheet_set_column_pixels(worksheet, 5, 5, 158, NULL);
		worksheet_set_column_pixels(worksheet, 6, 6, 186, NULL);
		worksheet_set_column_pixels(worksheet, 7, 7, 127, NULL);

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
			lxw_table_column col7 = { .header = "Performance", .formula = "=(1-[@DistanceComparison])/[@TimeComparison]", .total_function = LXW_TABLE_FUNCTION_NONE, .format = percentage_format };

			lxw_table_column* columns[] = { &col1, &col2, &col3, &col4, &col5, &col6, &col7, NULL};

			lxw_table_options options = { .name = name.c_str(),
			.total_row = LXW_TRUE,
			.columns = columns};


			worksheet_add_table(worksheet, 
				row, 1,
				row + lxw_row_t(entries.size()) + 1, lxw_col_t(sizeof(columns)/sizeof(lxw_table_column*) - 1),
				&options);

			lxw_row_t start_row = row;

			for (const auto& entry : entries) {
				row++;

				std::string name = jsonconversion::runModeToName(*entry);

				worksheet_write_string(worksheet, row, 1, name.c_str(), NULL);
				worksheet_write_number(worksheet, row, 2, entry->total_run_time.count() / (double)entry->number_of_valid_routes, double_format);
				worksheet_write_number(worksheet, row, 3, entry->total_final_distance / (double)entry->number_of_valid_routes, double_format);
				worksheet_write_number(worksheet, row, 4, entry->number_of_valid_routes / (double)entry->number_of_runs, percentage_format);
			}


			std::string names = "=" + name + "[Algoirthm]";
			std::string times = "=" + name + "[TimeAverage]";
			std::string distance = "=" + name + "[DistanceAverage]";

			lxw_chart* time_chart = workbook_add_chart(workbook, LXW_CHART_COLUMN);
			lxw_chart_series* series1 = chart_add_series(time_chart, names.c_str(), times.c_str());;
			chart_series_set_name(series1, "Time");
			chart_axis_set_name(time_chart->y_axis, "MicroSeconds");
			chart_axis_set_name(time_chart->x_axis, "Algorithm");
			worksheet_insert_chart(worksheet, start_row, 9, time_chart);

			lxw_chart* distance_chart = workbook_add_chart(workbook, LXW_CHART_COLUMN);
			lxw_chart_series* series2 = chart_add_series(distance_chart, names.c_str(), distance.c_str());
			chart_series_set_name(series2, "Distance");
			chart_axis_set_name(distance_chart->y_axis, "Distance");
			chart_axis_set_name(distance_chart->x_axis, "Algorithm");
			worksheet_insert_chart(worksheet, start_row, 17, distance_chart);
			row += 3;
		}
	};
};
