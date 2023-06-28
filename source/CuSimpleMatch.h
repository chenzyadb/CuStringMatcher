#ifndef _CU_SIMPLE_MATCH_H
#define _CU_SIMPLE_MATCH_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

class CuSimpleMatch
{
	public:
		CuSimpleMatch();
		CuSimpleMatch(const std::string &rule);
		CuSimpleMatch(const CuSimpleMatch &other);
		~CuSimpleMatch();
		CuSimpleMatch &operator=(const CuSimpleMatch &other);
		bool operator==(const CuSimpleMatch &other) const;
		bool operator!=(const CuSimpleMatch &other) const;
		bool operator<(const CuSimpleMatch &other) const;
		bool operator>(const CuSimpleMatch &other) const;

		bool match(const std::string &text) const;
		std::string data() const;

	private:
		std::string rule_;
		std::vector<std::string> front_;
		std::vector<std::string> middle_;
		std::vector<std::string> back_;
		std::vector<std::string> entire_;

		void ParseRule_();
		std::vector<std::string> ParseKey_(const std::string &text);
};

#endif
