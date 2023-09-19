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
		CuSimpleMatch matcher("^(Hello);");
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
		CuSimpleMatch matcher("(World!)^;");
		std::cout << (matcher.match("Hello, World!") ? "true" : "false") << std::endl;
		std::cout << (matcher.match("World, Hello!") ? "true" : "false") << std::endl;
	}
	{
		std::cout << "Test Match Entire:" << std::endl;
		CuSimpleMatch matcher("(Hello, World!);");
		std::cout << (matcher.match("Hello, World!") ? "true" : "false") << std::endl;
		std::cout << (matcher.match("World, Hello!") ? "true" : "false") << std::endl;
	}
	{
		std::cout << "Test Multi Key:" << std::endl;
		CuSimpleMatch matcher("^(test|Hello);");
		std::cout << (matcher.match("Hello, World!") ? "true" : "false") << std::endl;
		std::cout << (matcher.match("test, World!") ? "true" : "false") << std::endl;
		std::cout << (matcher.match("World, Hello!") ? "true" : "false") << std::endl;
	}
	{
		std::cout << "Test Multi Rule:" << std::endl;
		CuSimpleMatch matcher("(World!)^;(test)*;");
		std::cout << (matcher.match("Hello, World!") ? "true" : "false") << std::endl;
		std::cout << (matcher.match("test, hello!") ? "true" : "false") << std::endl;
		std::cout << (matcher.match("Hello, test!") ? "true" : "false") << std::endl;
	}
	{
		std::cout << "Test charSet:" << std::endl;
		CuSimpleMatch matcher("([A-Z][0-9]);");
		std::cout << (matcher.match("A0") ? "true" : "false") << std::endl;
		std::cout << (matcher.match("B1") ? "true" : "false") << std::endl;
		std::cout << (matcher.match("a9") ? "true" : "false") << std::endl;
	}
	{
		std::cout << "Test complex string:" << std::endl;
		CuSimpleMatch matcher("^([Hh]ello, [Ii]'m [0-9][0-9] years old, my favorite letter is [A-Z].);");
		std::cout << (matcher.match("Hello, I'm 18 years old, my favorite letter is G.") ? "true" : "false") << std::endl;
		std::cout << (matcher.match("Hello, I'm 24 years old, my favorite letter is A.") ? "true" : "false") << std::endl;
		std::cout << (matcher.match("hello, i'm 99 years old, my favorite letter is Z.") ? "true" : "false") << std::endl;
		std::cout << (matcher.match("Hello, I'm 18 years old, my favorite letter is z.") ? "true" : "false") << std::endl;
		std::cout << (matcher.match("Hello, I'm 1 years old, my favorite letter is F.") ? "true" : "false") << std::endl;
	}
	{
		std::cout << "std::vector & std::map support test." << std::endl;

		CuSimpleMatch matcher = CuSimpleMatch("*(this|test)*;");
		std::cout << (matcher.match("this is test text") ? "true" : "false") << std::endl;

		std::vector<CuSimpleMatch> testList{};
		testList.resize(100, CuSimpleMatch("^(Hello);"));
		std::cout << testList[0].data() << std::endl;

		std::map<int, CuSimpleMatch> testMap{};
		testMap[123] = CuSimpleMatch("^(Hello);");
		testMap[123] = CuSimpleMatch();
		std::cout << testMap.at(123).data() << std::endl;
	}

	std::cout << "Speed Test:" << std::endl;
	{
		std::regex testRegex("^([Aa]pple|[Bb]anana|[Oo]range)|(good|tasty)$");
		auto startTime = GetTimeStampMs();
		for (int i = 0; i < 10000; i++) {
			bool match = false;
			match = std::regex_search("Apple is very good", testRegex);
			match = std::regex_search("Banana is very good", testRegex);
			match = std::regex_search("Orange is very good", testRegex);
			match = std::regex_search("apple is very tasty", testRegex);
			match = std::regex_search("banana is very tasty", testRegex);
			match = std::regex_search("orange is very tasty", testRegex);
			match = std::regex_search("Hello, World!!!", testRegex);
		}
		std::cout << "STL Regex use time: " << GetTimeStampMs() - startTime << " ms." << std::endl;
	}
	{
		CuSimpleMatch testMatch("^([Aa]pple|[Bb]anana|[Oo]range);(good|tasty)^;");
		auto startTime = GetTimeStampMs();
		for (int i = 0; i < 10000; i++) {
			bool match = false;
			match = testMatch.match("Apple is very good");
			match = testMatch.match("Banana is very good");
			match = testMatch.match("Orange is very good");
			match = testMatch.match("apple is very tasty");
			match = testMatch.match("banana is very tasty");
			match = testMatch.match("orange is very tasty");
			match = testMatch.match("Hello, World!!!");
		}
		std::cout << "CuSimpleMatch use time: " << GetTimeStampMs() - startTime << " ms." << std::endl;
	}
	
	return 0;
}
