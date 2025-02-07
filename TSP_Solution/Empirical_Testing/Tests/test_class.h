#pragma once
#include <chrono>
#include <mutex>
#include <future>

#define NOMINMAX	// This is to prevent windows.h from defining min and max macros
#include <Windows.h>

#include "tsp_template.h"
#include "file_handling/tsp_file.h"
#include "multithread_tester.h"
// TODO: MOVE ALL IMPLEMENTATION TO A .CPP FILE!!!

BOOL __stdcall ConsoleCtrlHandler(DWORD ctrlType); // TODO: THIS IS HORRIBLE!!!

class TestClass
{
public:
	TestClass(std::string name, bool use_file) :
		m_name(name),
		m_use_file(use_file)
	{
		m_file = std::make_shared<TSPFile>(use_file ? name : "");
	}
	~TestClass() = default;

	std::shared_ptr<TSPFile> RunTests(size_t num_of_ittr = SIZE_MAX, std::chrono::seconds timeout = std::chrono::seconds::max()) {

		if (!SetConsoleCtrlHandler(ConsoleCtrlHandler, TRUE)) {
			std::cerr << "Error: Could not set control handler.\n";
		}

		// package task to cancel if it takes too long
		std::packaged_task<void()> task(std::bind(&TestClass::_test, this, num_of_ittr));

		// Future for probing status
		auto future = task.get_future();

		// Start the task in a separate thread
		std::thread thr(std::move(task));

		// Wait for the task to finish or timeout
		std::cout << "Test running\n";
		if (future.wait_for(timeout) != std::future_status::timeout) {
			// Task was succefully completed
			thr.join();
			future.get();
		}
		else {
			// Task took too long
			thr.detach();
		}

		return m_file;
	}

	static void Exit() { s_shouldExit = true; }

protected:
	Tester m_tester;

	void addResult(TSPVerboseResultDynamic&& result) {
		std::lock_guard<std::mutex> lock(m_mutex);
		m_file->addEntry(std::move(result));
	}

private:
	const std::string m_name;
	const bool m_use_file;
	
	std::mutex m_mutex;
	std::shared_ptr<TSPFile> m_file;

	static inline std::atomic<bool> s_shouldExit = false;

	void _test(size_t num_of_ittr) {
		size_t i = 0;

		std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
		const std::chrono::steady_clock::time_point const_start = std::chrono::steady_clock::now();

		while (!TestClass::s_shouldExit && i < num_of_ittr) {

			SetThreadExecutionState(ES_CONTINUOUS | ES_SYSTEM_REQUIRED | ES_AWAYMODE_REQUIRED);
			Test();

			auto r = m_tester.collectResults();
			for (auto& res : r) {
				addResult(std::move(res));
			}

			i++;

			if (std::chrono::duration<double>(std::chrono::steady_clock::now() - start).count() > 1) {
				writeToFile(std::chrono::duration<double>(std::chrono::steady_clock::now() - const_start).count(), i);
				start = std::chrono::steady_clock::now();
			}
		}
		writeToFile(std::chrono::duration<double>(std::chrono::steady_clock::now() - const_start).count(), i); 
		SetThreadExecutionState(ES_CONTINUOUS);
	}

	void writeToFile(double time, size_t i)
	{
		if (m_use_file) {
			m_file->writeFile();
			std::cout << time << " seconds, Test" << i << ": file written\n";
		}
	}
	
	virtual void Test() = 0;
};

BOOL __stdcall ConsoleCtrlHandler(DWORD ctrlType) {
	switch (ctrlType) {
	case CTRL_C_EVENT:
		std::cout << "Ctrl-C event\n\n";
		TestClass::Exit();
		return TRUE;
	default:
		return FALSE;
	}
};
