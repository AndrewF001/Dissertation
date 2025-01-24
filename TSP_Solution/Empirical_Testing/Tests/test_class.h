#pragma once
#include <chrono>
#include <mutex>

#include <tsp_template.h>
#include <file_handling/tsp_file.h>

class TestClass
{
public:
	TestClass(std::string name, bool use_file);
	~TestClass() = default;

	const TSPFile& RunTests(size_t num_of_ittr = SIZE_MAX, std::chrono::seconds timeout = std::chrono::seconds::max());

	static void Exit() { s_shouldExit = true; }

protected:
	void addResult(TSPVerboseResultDynamic&& result);

private:
	const std::string m_name;
	const bool m_use_file;
	
	std::mutex m_mutex;
	TSPFile m_file;	// Maybe make this std::shared_ptr<TSPFile>

	static inline std::atomic<bool> s_shouldExit = false;

	void _test(size_t num_of_ittr);
	void writeToFile(double time, size_t i);
	virtual void Test() = 0;
};
