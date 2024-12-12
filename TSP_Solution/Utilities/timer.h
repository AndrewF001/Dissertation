#pragma once
#include <chrono>

using TimeScale = std::chrono::microseconds;

class Timer {
public:
	Timer() : m_duration() { start_timer();	};
	~Timer() = default;

	void start_timer() {
		m_start = std::chrono::high_resolution_clock::now();
	}

	TimeScale time() {
		return std::chrono::duration_cast<TimeScale>(std::chrono::high_resolution_clock::now() - m_start);
	}

	TimeScale interval() {
		auto pause = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<TimeScale>(pause - m_start);
		m_duration += duration;
		m_start = pause;
		return duration;
	}

	TimeScale resetTimer() {
		auto dur = m_duration;
		m_duration = TimeScale(0);
		m_start = std::chrono::steady_clock::time_point{};
		return dur;
	}

	TimeScale stopTimer() {
		m_duration += std::chrono::duration_cast<TimeScale>(std::chrono::high_resolution_clock::now() - m_start);
		m_start = std::chrono::steady_clock::time_point{};

		return m_duration;
	}

private:
	std::chrono::steady_clock::time_point m_start;
	TimeScale m_duration;
};
