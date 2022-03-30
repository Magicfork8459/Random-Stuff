// Benchmarking.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <ranges>
#include <algorithm>
#include <numeric>
#include <chrono>
#include <sstream>
#include <variant>
#include <iostream>
#include "Benchmarker.h"

const std::string stringBy3 = "FIZZ";
const std::string stringBy5 = "BUZZ";

using fizzy = std::variant<int, std::string>;

void reverseThis(std::string& input)
{
    for (int i = 0; i < input.length() / 2; ++i)
    {
        std::swap(input[i], input[input.length() - i - 1]);
    }
}

std::string standardReverse(std::string input)
{
    std::string reversing;
    for (int i = input.length() - 1; i >= 0; --i)
    {
        reversing += input[i];
    }

    return reversing;
}

void getNumbers(const int& amount)
{    
    std::stringstream out;

    for (int i = 1; i <= amount; ++i)
    {
        const bool by3 = (i % 3 == 0);
        const bool by5 = (i % 5 == 0);
        
        //out << "[";
        if (by3)
            out << stringBy3;

        if (by5)
            out << stringBy5;

        if (!by3 && !by5)
            out << i;
        out << ", ";
    }

    out << "...";
    std::cout << out.str() << std::endl;
}

int main()
{
    static std::string reverseMe("H");
    std::function<void()> f1 = [&]()
    {
        std::string in(reverseMe);
        reverseThis(in);
    };

    std::function<void()> f2 = [&]()
    {
        standardReverse(reverseMe);
    };

    jam::Benchmarker bench(f1);
    jam::Benchmarker bench2(f2);
    ;
    //std::cout << "Result: " << std::chrono::microseconds(bench.run()).count() << " microseconds" << std::endl;

    std::cout << "Mine : " << std::endl;
    int count = 1;
    for (auto result : bench.run(5))
    {
        std::cout << "result #" << count++ << " : " << result << " microseconds" << std::endl;
    }

    std::cout << "Other : " << std::endl;
    count = 1;
    for (auto result : bench2.run(5))
    {
        std::cout << "result #" << count++ << " : " << result << " microseconds" << std::endl;
    }

}