#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>

class Timer
{
public:
	using clock_t = std::chrono::steady_clock;
	using time_point_t = clock_t::time_point;
	using time_micro_t = std::chrono::microseconds;

	Timer() : m_begin(clock_t::now()), time_pause(0) {}


	void t_pause() // ставим на паузу
	{
		start_pause = clock_t::now();
	}


	void t_continue() // продолжаем 
	{
		auto end_pause = clock_t::now();
		time_pause += std::chrono::duration_cast <std::chrono::microseconds> (end_pause - start_pause);
	}


	~Timer()
	{
		auto end = clock_t::now();

		std::cout << "microseconds: " << std::chrono::duration_cast <std::chrono::microseconds> (end - m_begin-time_pause).count() << std::endl;
	}


private:
	time_point_t m_begin;//начало отсчета таймера
	time_point_t start_pause;// начало паузы
	time_micro_t time_pause;// продолжительность паузы
};



int main()
{
	std::vector <int> v(1000, 0);
	for (int i  =0; i < std::size(v); i++)
	{
		v[i] = i;
	}


	{
		Timer vector_time;

		std::sort(std::begin(v), std::end(v), std::greater < int >());

		vector_time.t_pause();

		for (auto c : v)
		{
			std::cout << c << ' ';
		}

		std::cout << std::endl;

		std::cout << "///////////////////////////////////" << std::endl;

		vector_time.t_continue();

	}


	return 0;
} 
