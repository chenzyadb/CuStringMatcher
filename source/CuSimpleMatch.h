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
		bool operator==(const CuSimpleMatch &other);
		bool operator!=(const CuSimpleMatch &other);
		bool operator<(const CuSimpleMatch &other);
		bool operator>(const CuSimpleMatch &other);

		bool match(const std::string &text) const;
		std::string data() const;

	private:
		std::string rule_;
		std::vector<std::string> front_;
		std::vector<std::string> middle_;
		std::vector<std::string> back_;

		void ParseRule_();
};

#endif
