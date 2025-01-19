#include <future>

#define NOMINMAX	// This is to prevent windows.h from defining min and max macros
#include <Windows.h>

#include "Test_Class.h"

TestClass::TestClass(std::string name, size_t printItter, std::chrono::seconds timeout) : 
	m_name(name),
	m_printintervals(printItter),
	m_timeout(timeout),
	m_file(name)
{}


BOOL __stdcall ConsoleCtrlHandler(DWORD ctrlType) {
	switch (ctrlType) {
	case CTRL_C_EVENT:
		std::cout << "Ctrl-C event\n\n";
		TestClass::Exit();
		return TRUE;
	default:
		return FALSE;
	}
}


void TestClass::RunTests() {

	if (!SetConsoleCtrlHandler(ConsoleCtrlHandler, TRUE)) {
		std::cerr << "Error: Could not set control handler.\n";
	}

	// package task to cancel if it takes too long
	std::packaged_task<void()> task(std::bind(&TestClass::_test, this));

	// Future for probing status
	auto future = task.get_future();

	// Start the task in a separate thread
	std::thread thr(std::move(task));

	// Wait for the task to finish or timeout
	if (future.wait_for(m_timeout) != std::future_status::timeout) {
		// Task was succefully completed
		thr.join();
		future.get();
	}
	else {
		// Task took too long
		thr.detach();
	}
}

void TestClass::addResult(TSPVerboseResultDynamic& result) {
	m_file.addEntry(result);
}

void TestClass::_test() {
	int i = 0;
	while (!TestClass::s_shouldExit) {
		
		Test();
		
		if (++i >= m_printintervals) {
			m_file.writeFile();
			i = 0;
		}
	}

	m_file.writeFile();
}
