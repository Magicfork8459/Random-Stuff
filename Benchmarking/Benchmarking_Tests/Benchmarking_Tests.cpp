#include "pch.h"
#include "CppUnitTest.h"
#include "../Benchmarking/Benchmarker.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BenchmarkingTests
{
	static std::function<void()> benchMe
	([&]()
		{
			std::cout << "Hey" << std::endl;
		}
	);
	TEST_CLASS(BenchmarkingTests)
	{
	public:
		jam::Benchmarker bench { benchMe };
		TEST_METHOD(SingleRun)
		{
			Assert::IsTrue(bench.run() > 0);
		}

		TEST_METHOD(MultiRun)
		{
			Assert::IsTrue(bench.run(5).size() == 5);
		}

		TEST_METHOD(Average)
		{
			//TODO Figure out why the first one is always off by so much... or just run the function one more time and drop the first one every time
			bench.average(5);
		}
	};
}
