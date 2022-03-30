#pragma once
#include <chrono>
#include <functional>
#include <vector>
#include "windows.h"
#include "profileapi.h"

namespace jam
{
	class Benchmarker
	{
	public:
		Benchmarker(std::function<void()>& target);
		float average(unsigned int count);
		std::vector<long long> run(unsigned int count);
		long long run();
	private:
		std::function<void()>& target;
		LARGE_INTEGER nextResult;
		std::vector<long long> results;
	};
}


