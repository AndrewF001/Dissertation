#pragma once
#include <xlsxwriter.h>

#include "tsp_file.h"

class ExcelCreator {
public:
	static inline int createExcel(const TSPFile& file) {
		lxw_workbook* workbook = workbook_new((file.m_name + ".xlsx").c_str());

		return workbook_close(workbook);
	}

private:
};
