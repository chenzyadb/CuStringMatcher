#include <iostream>
#include <chrono>
#include <regex>
#include <map>
#include "CuSimpleMatch.hpp"

uint64_t GetTimeStampMs()
{
	auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
	return now_ms.time_since_epoch().count();
}

int main()
{
	{
		std::cout << "Test Match Front:" << std::endl;
		CuSimpleMatch matcher("Hello*");
		std::cout << (matcher.match("Hello, World!") ? "true" : "false") << std::endl;
		std::cout << (matcher.match("World, Hello!") ? "true" : "false") << std::endl;
	}
	{
		std::cout << "Test Match Middle:" << std::endl;
		CuSimpleMatch matcher("*lo, Wo*");
		std::cout << (matcher.match("Hello, World!") ? "true" : "false") << std::endl;
		std::cout << (matcher.match("World, Hello!") ? "true" : "false") << std::endl;
	}
	{
		std::cout << "Test Match Back:" << std::endl;
		CuSimpleMatch matcher("*World!");
		std::cout << (matcher.match("Hello, World!") ? "true" : "false") << std::endl;
		std::cout << (matcher.match("World, Hello!") ? "true" : "false") << std::endl;
	}
	{
		std::cout << "Test Match Entire:" << std::endl;
		CuSimpleMatch matcher("Hello, World!");
		std::cout << (matcher.match("Hello, World!") ? "true" : "false") << std::endl;
		std::cout << (matcher.match("Hello,World!") ? "true" : "false") << std::endl;
	}
	{
		std::cout << "Test Multi Key:" << std::endl;
		CuSimpleMatch matcher("(test|Hello)*");
		std::cout << (matcher.match("Hello, World!") ? "true" : "false") << std::endl;
		std::cout << (matcher.match("test, World!") ? "true" : "false") << std::endl;
		std::cout << (matcher.match("World, Hello!") ? "true" : "false") << std::endl;
	}
	{
		std::cout << "Test Multi Rule:" << std::endl;
		CuSimpleMatch matcher("*World!|test*");
		std::cout << (matcher.match("Hello, World!") ? "true" : "false") << std::endl;
		std::cout << (matcher.match("test, hello!") ? "true" : "false") << std::endl;
		std::cout << (matcher.match("Hello, test!") ? "true" : "false") << std::endl;
	}
	{
		std::cout << "Test charSet:" << std::endl;
		CuSimpleMatch matcher("[A-Z][0-9]");
		std::cout << (matcher.match("A0") ? "true" : "false") << std::endl;
		std::cout << (matcher.match("B1") ? "true" : "false") << std::endl;
		std::cout << (matcher.match("a9") ? "true" : "false") << std::endl;
	}
	{
		std::cout << "Test complex string:" << std::endl;
		CuSimpleMatch matcher("[Hh]ello, [Ii]'m [0-9][0-9] years old, my favorite letter is [A-Z].");
		std::cout << (matcher.match("Hello, I'm 18 years old, my favorite letter is G.") ? "true" : "false") << std::endl;
		std::cout << (matcher.match("Hello, I'm 24 years old, my favorite letter is A.") ? "true" : "false") << std::endl;
		std::cout << (matcher.match("hello, i'm 99 years old, my favorite letter is Z.") ? "true" : "false") << std::endl;
		std::cout << (matcher.match("Hello, I'm 18 years old, my favorite letter is z.") ? "true" : "false") << std::endl;
		std::cout << (matcher.match("Hello, I'm 1 years old, my favorite letter is F.") ? "true" : "false") << std::endl;
	}
	{
		std::cout << "Test setRule & clear:" << std::endl;

		CuSimpleMatch matcher{};
		matcher.setRule("*Hello*");
		std::cout << (matcher.match("Hello India Mi Fans, do you like mi 4i?") ? "true" : "false") << std::endl;
		matcher.clear();
		std::cout << (matcher.match("Hello India Mi Fans, do you like mi 4i?") ? "true" : "false") << std::endl;
		std::cout << matcher.data() << std::endl;
	}
	{
		std::cout << "std::vector & std::map support test." << std::endl;

		CuSimpleMatch matcher = CuSimpleMatch("*(this|test)*");
		std::cout << (matcher.match("this is test text") ? "true" : "false") << std::endl;

		std::vector<CuSimpleMatch> testList{};
		testList.resize(100, CuSimpleMatch("Hello*"));
		std::cout << testList[0].data() << std::endl;

		std::map<int, CuSimpleMatch> testMap{};
		testMap[123] = CuSimpleMatch("Hello*");
		testMap[123] = CuSimpleMatch();
		std::cout << testMap.at(123).data() << std::endl;
	}

	std::cout << "Speed Test:" << std::endl;
	{
		auto startTime = GetTimeStampMs();
		for (int i = 0; i < 10000; i++) {
			std::regex testRegex("^(Red|Orange|Yello|Green|Blue|Purple|White|Black|Grey|Gold|Silver)");
		}
		std::cout << "std::regex use time: " << GetTimeStampMs() - startTime << " ms." << std::endl;
	}
	{
		auto startTime = GetTimeStampMs();
		for (int i = 0; i < 10000; i++) {
			CuSimpleMatch testMatch("(Red|Orange|Yello|Green|Blue|Purple|White|Black|Grey|Gold|Silver)*");
		}
		std::cout << "CuSimpleMatch use time: " << GetTimeStampMs() - startTime << " ms." << std::endl;
	}
	{
		std::regex testRegex("^The price of the shirt is [0-9] pounds");
		auto startTime = GetTimeStampMs();
		for (int i = 0; i < 10000; i++) {
			bool match = false;
			match = std::regex_search("The price of the shirt is 9 pounds 15 pence.", testRegex);
			match = std::regex_search("The price of the shirt is 8 pounds 99 pence.", testRegex);
			match = std::regex_search("The shirt is free.", testRegex);
		}
		std::cout << "std::regex_search use time: " << GetTimeStampMs() - startTime << " ms." << std::endl;
	}
	{
		CuSimpleMatch testMatch("The price of the shirt is [0-9] pounds*");
		auto startTime = GetTimeStampMs();
		for (int i = 0; i < 10000; i++) {
			bool match = false;
			match = testMatch.match("The price of the shirt is 9 pounds 15 pence.");
			match = testMatch.match("The price of the shirt is 8 pounds 99 pence.");
			match = testMatch.match("The shirt is free.");
		}
		std::cout << "CuSimpleMatch use time: " << GetTimeStampMs() - startTime << " ms." << std::endl;
	}
	
	return 0;
}
