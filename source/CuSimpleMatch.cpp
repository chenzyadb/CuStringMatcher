#include "CuSimpleMatch.h"

CuSimpleMatch::CuSimpleMatch() : rule_(), front_(), middle_(), back_() { }

CuSimpleMatch::CuSimpleMatch(const std::string &rule) : rule_(rule), front_(), middle_(), back_()
{
	ParseRule_();
}

CuSimpleMatch::CuSimpleMatch(const CuSimpleMatch &other) : rule_(), front_(), middle_(), back_()
{
	rule_ = other.data();
	ParseRule_();
}

CuSimpleMatch::~CuSimpleMatch() { }

CuSimpleMatch &CuSimpleMatch::operator=(const CuSimpleMatch &other)
{
	rule_ = other.data();
	ParseRule_();

	return *this;
}

bool CuSimpleMatch::operator==(const CuSimpleMatch &other)
{
	return rule_ == other.data();
}

bool CuSimpleMatch::operator!=(const CuSimpleMatch &other)
{
	return rule_ != other.data();
}

bool CuSimpleMatch::operator<(const CuSimpleMatch &other)
{
	return rule_ < other.data();
}

bool CuSimpleMatch::operator>(const CuSimpleMatch &other)
{
	return rule_ > other.data();
}

bool CuSimpleMatch::match(const std::string &text) const
{
	bool match = false;
	if (!match && front_.size() > 0) {
		for (const auto &key : front_) {
			if (text.find(key) == 0) {
				match = true;
				break;
			}
		}
	}
	if (!match && middle_.size() > 0) {
		for (const auto &key : middle_) {
			if (text.find(key) != std::string::npos) {
				match = true;
				break;
			}
		}
	}
	if (!match && back_.size() > 0) {
		for (const auto &key : back_) {
			if (text.find(key) == text.size() - key.size()) {
				match = true;
				break;
			}
		}
	}

	return match;
}

std::string CuSimpleMatch::data() const
{
	return rule_;
}

void CuSimpleMatch::ParseRule_()
{
	std::string key{};
	std::vector<std::string> keySet{};
	bool atKeySet = false;
	bool atFront = false;
	bool atBack = false;
	bool matchFront = false;
	bool matchBack = false;
	for (const auto &c : rule_) {
		if (!atKeySet && !atFront && !atBack) {
			atFront = true;
		}
		switch (c) {
			case '*':
				if (atFront) {
					matchFront = true;
				} else if (atBack) {
					matchBack = true;
				} else {
					throw std::runtime_error("Invalid Matching Rule.");
				}
				break;
			case '(':
				if (atFront) {
					atKeySet = true;
					atFront = false;
				} else {
					throw std::runtime_error("Invalid Matching Rule.");
				}
				break;
			case '|':
				if (atKeySet) {
					if (!key.empty()) {
						keySet.emplace_back(key);
						key.clear();
					}
				} else {
					throw std::runtime_error("Invalid Matching Rule.");
				}
				break;
			case ')':
				if (atKeySet) {
					if (!key.empty()) {
						keySet.emplace_back(key);
						key.clear();
					}
					atKeySet = false;
					atBack = true;
				} else {
					throw std::runtime_error("Invalid Matching Rule.");
				}
				break;
			case ';':
				if (atBack) {
					if (matchFront && matchBack) {
						middle_.insert(middle_.end(), keySet.begin(), keySet.end());
					} else if (matchFront) {
						front_.insert(front_.end(), keySet.begin(), keySet.end());
					} else if (matchBack) {
						back_.insert(back_.end(), keySet.begin(), keySet.end());
					} else {
						throw std::runtime_error("Invalid Matching Rule.");
					}
					keySet.clear();
					atBack = false;
					matchFront = false;
					matchBack = false;
				} else {
					throw std::runtime_error("Invalid Matching Rule.");
				}
				break;
			default:
				if (atKeySet) {
					key += c;
				}
				break;
		}
	}
}
