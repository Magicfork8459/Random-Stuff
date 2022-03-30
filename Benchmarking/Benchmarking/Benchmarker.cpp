#include "Benchmarker.h"

using namespace jam;

Benchmarker::Benchmarker(std::function<void()>& target)
	: target(target)
{

}

float Benchmarker::average(unsigned int count)
{
	auto results = run(count);
	int sum = 0;

	for (auto result : results)
		sum += result;
	return static_cast<float>(sum) / results.size();
}

std::vector<long long> Benchmarker::run(unsigned int count)
{
	std::vector<long long> results;

	do
	{
		results.push_back(run());
		--count;
	} while (count > 0);

	return results;
}

long long Benchmarker::run()
{
	LARGE_INTEGER before;
	LARGE_INTEGER after;
	LARGE_INTEGER frequency;
	LARGE_INTEGER calculating;

	long long result(0);
	if (QueryPerformanceCounter(&before))
	{
		target();

		if (QueryPerformanceCounter(&after))
		{
			QueryPerformanceFrequency(&frequency);
			calculating.QuadPart = after.QuadPart - before.QuadPart;
			calculating.QuadPart *= 1000000;
			calculating.QuadPart /= frequency.QuadPart;
			result = calculating.QuadPart;
			results.push_back(result);
		}
	}

	return result;
}