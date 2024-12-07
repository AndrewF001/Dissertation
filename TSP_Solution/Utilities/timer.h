#pragma once
#include <chrono>

class Timer {
public:
	Timer() : m_duration() { start_timer();	};
	~Timer() = default;

	void start_timer() {
		m_start = std::chrono::high_resolution_clock::now();
	}

	std::chrono::milliseconds time() {
		return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - m_start);
	}

	std::chrono::milliseconds interluve() {
		auto pause = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(pause - m_start);
		m_duration += duration;
		m_start = pause;
		return duration;
	}

	std::chrono::milliseconds reset_timer() {
		auto dur = m_duration;
		m_duration = std::chrono::milliseconds(0);
		m_start = std::chrono::steady_clock::time_point{};
		return dur;
	}

	std::chrono::milliseconds stop_timer() {
		auto duration = interluve();
		reset_timer();
		return duration;
	}

private:
	std::chrono::steady_clock::time_point m_start;
	std::chrono::milliseconds m_duration;
};
