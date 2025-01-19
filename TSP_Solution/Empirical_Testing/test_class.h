#pragma once
#include <file_handling/tsp_file.h>

class TestClass
{
public:
	TestClass(std::string name, size_t printItter = 1, std::chrono::seconds timeout = std::chrono::seconds::max());
	~TestClass() = default;

	void RunTests();

	static void Exit() { s_shouldExit = true; }

protected:
	void addResult(TSPVerboseResultDynamic& result);

private:
	const std::string m_name;

	const size_t m_printintervals;
	const std::chrono::seconds m_timeout;
	
	TSPFile m_file;

	static inline std::atomic<bool> s_shouldExit = false;

	void _test();
	virtual void Test() = 0;
};
