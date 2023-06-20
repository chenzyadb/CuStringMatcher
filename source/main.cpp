#include <iostream>
#include <chrono>
#include <regex>
#include <map>
#include "CuSimpleMatch.h"

uint64_t GetTimeStampMs()
{
	auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
	uint64_t timestamp_ms = now_ms.time_since_epoch().count();

	return timestamp_ms;
}

int main()
{
	{
		std::cout << "Test Match Front:" << std::endl;
		CuSimpleMatch matcher("*(Hello);");
		std::cout << (matcher.match("Hello, World!") ? "true" : "false") << std::endl;
		std::cout << (matcher.match("World, Hello!") ? "true" : "false") << std::endl;
	}
	{
		std::cout << "Test Match Middle:" << std::endl;
		CuSimpleMatch matcher("*(lo, Wo)*;");
		std::cout << (matcher.match("Hello, World!") ? "true" : "false") << std::endl;
		std::cout << (matcher.match("World, Hello!") ? "true" : "false") << std::endl;
	}
	{
		std::cout << "Test Match Back:" << std::endl;
		CuSimpleMatch matcher("(World!)*;");
		std::cout << (matcher.match("Hello, World!") ? "true" : "false") << std::endl;
		std::cout << (matcher.match("World, Hello!") ? "true" : "false") << std::endl;
	}
	{
		std::cout << "Test Multi Key:" << std::endl;
		CuSimpleMatch matcher("*(test|Hello);");
		std::cout << (matcher.match("Hello, World!") ? "true" : "false") << std::endl;
		std::cout << (matcher.match("test, World!") ? "true" : "false") << std::endl;
		std::cout << (matcher.match("World, Hello!") ? "true" : "false") << std::endl;
	}
	{
		std::cout << "Test Multi Rule:" << std::endl;
		CuSimpleMatch matcher("(World!)*;*(test);");
		std::cout << (matcher.match("Hello, World!") ? "true" : "false") << std::endl;
		std::cout << (matcher.match("test, hello!") ? "true" : "false") << std::endl;
		std::cout << (matcher.match("Hello, test!") ? "true" : "false") << std::endl;
	}
	{
		std::cout << "std::vector & std::map support test." << std::endl;

		CuSimpleMatch matcher = CuSimpleMatch("*(this|test)*;");
		std::cout << (matcher.match("this is test text") ? "true" : "false") << std::endl;

		std::vector<CuSimpleMatch> testList{};
		testList.resize(100, CuSimpleMatch("*(Hello);"));
		std::cout << testList[0].data() << std::endl;

		std::map<int, CuSimpleMatch> testMap{};
		testMap[123] = CuSimpleMatch("*(Hello);");
		std::cout << testMap.at(123).data() << std::endl;
	}

	std::cout << "Speed Test:" << std::endl;
	{
		std::regex testRegex("^(apple|banana|orange)|(good|tasty)$");
		auto startTime = GetTimeStampMs();
		for (int i = 0; i < 10000; i++) {
			bool match = false;
			match = std::regex_search("apple is very good", testRegex);
			match = std::regex_search("banana is very good", testRegex);
			match = std::regex_search("orange is very good", testRegex);
			match = std::regex_search("apple is very tasty", testRegex);
			match = std::regex_search("banana is very tasty", testRegex);
			match = std::regex_search("orange is very tasty", testRegex);
		}
		std::cout << "STL Regex use time: " << GetTimeStampMs() - startTime << " ms." << std::endl;
	}
	{
		CuSimpleMatch testMatch("*(apple|banana|orange);(good|tasty)*;");
		auto startTime = GetTimeStampMs();
		for (int i = 0; i < 10000; i++) {
			bool match = false;
			match = testMatch.match("apple is very good");
			match = testMatch.match("banana is very good");
			match = testMatch.match("orange is very good");
			match = testMatch.match("apple is very tasty");
			match = testMatch.match("banana is very tasty");
			match = testMatch.match("orange is very tasty");
		}
		std::cout << "CuSimpleMatch use time: " << GetTimeStampMs() - startTime << " ms." << std::endl;
	}
	
	return 0;
}
