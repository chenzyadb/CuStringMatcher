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
			case '^':
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
						auto keys = ParseKey_(key);
						keySet.insert(keySet.end(), keys.begin(), keys.end());
						key.clear();
					}
				} else {
					throw std::runtime_error("Invalid Matching Rule.");
				}
				break;
			case ')':
				if (atKeySet) {
					if (!key.empty()) {
						auto keys = ParseKey_(key);
						keySet.insert(keySet.end(), keys.begin(), keys.end());
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

std::vector<std::string> CuSimpleMatch::ParseKey_(const std::string &text)
{ 
	constexpr char CHARSET_A[] = "Aa";
	constexpr char CHARSET_B[] = "Bb";
	constexpr char CHARSET_C[] = "Cc";
	constexpr char CHARSET_D[] = "Dd";
	constexpr char CHARSET_E[] = "Ee";
	constexpr char CHARSET_F[] = "Ff";
	constexpr char CHARSET_G[] = "Gg";
	constexpr char CHARSET_H[] = "Hh";
	constexpr char CHARSET_I[] = "Ii";
	constexpr char CHARSET_J[] = "Jj";
	constexpr char CHARSET_K[] = "Kk";
	constexpr char CHARSET_L[] = "Ll";
	constexpr char CHARSET_M[] = "Mm";
	constexpr char CHARSET_N[] = "Nn";
	constexpr char CHARSET_O[] = "Oo";
	constexpr char CHARSET_P[] = "Pp";
	constexpr char CHARSET_Q[] = "Qq";
	constexpr char CHARSET_R[] = "Rr";
	constexpr char CHARSET_S[] = "Ss";
	constexpr char CHARSET_T[] = "Tt";
	constexpr char CHARSET_U[] = "Uu";
	constexpr char CHARSET_V[] = "Vv";
	constexpr char CHARSET_W[] = "Ww";
	constexpr char CHARSET_X[] = "Xx";
	constexpr char CHARSET_Y[] = "Yy";
	constexpr char CHARSET_Z[] = "Zz";
	constexpr char CHARSET_AZ[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	constexpr char CHARSET_az[] = "abcdefghijklmnopqrstuvwxyz";
	constexpr char CHARSET_NUM[] = "0123456789";
	const auto getCharSet = [=](const std::string &str) -> std::string {
		std::string charSet = "";
		if (str == "Aa") {
			charSet = CHARSET_A;
		} else if (str == "Bb") {
			charSet = CHARSET_B;
		} else if (str == "Cc") {
			charSet = CHARSET_C;
		} else if (str == "Dd") {
			charSet = CHARSET_D;
		} else if (str == "Ee") {
			charSet = CHARSET_E;
		} else if (str == "Ff") {
			charSet = CHARSET_F;
		} else if (str == "Gg") {
			charSet = CHARSET_G;
		} else if (str == "Hh") {
			charSet = CHARSET_H;
		} else if (str == "Ii") {
			charSet = CHARSET_I;
		} else if (str == "Jj") {
			charSet = CHARSET_J;
		} else if (str == "Kk") {
			charSet = CHARSET_K;
		} else if (str == "Ll") {
			charSet = CHARSET_L;
		} else if (str == "Mm") {
			charSet = CHARSET_M;
		} else if (str == "Nn") {
			charSet = CHARSET_N;
		} else if (str == "Oo") {
			charSet = CHARSET_O;
		} else if (str == "Pp") {
			charSet = CHARSET_P;
		} else if (str == "Qq") {
			charSet = CHARSET_Q;
		} else if (str == "Rr") {
			charSet = CHARSET_R;
		} else if (str == "Ss") {
			charSet = CHARSET_S;
		} else if (str == "Tt") {
			charSet = CHARSET_T;
		} else if (str == "Uu") {
			charSet = CHARSET_U;
		} else if (str == "Vv") {
			charSet = CHARSET_V;
		} else if (str == "Ww") {
			charSet = CHARSET_W;
		} else if (str == "Xx") {
			charSet = CHARSET_X;
		} else if (str == "Yy") {
			charSet = CHARSET_Y;
		} else if (str == "Zz") {
			charSet = CHARSET_Z;
		} else if (str == "A-Z") {
			charSet = CHARSET_AZ;
		} else if (str == "a-z") {
			charSet = CHARSET_az;
		} else if (str == "0-9") {
			charSet = CHARSET_NUM;
		}
		return charSet;
	};

	std::vector<std::string> keys{};
	std::vector<std::string> charSets{};
	{
		std::string baseStr = "";
		bool inBracket = false;
		std::string charSetStr = "";
		for (const auto &c : text) {
			switch (c) {
				case '[':
					if (!inBracket) {
						inBracket = true;
						baseStr += '|';
					} else {
						throw std::runtime_error("Invalid Matching Rule.");
					}
					break;
				case ']':
					if (inBracket) {
						inBracket = false;
						charSets.emplace_back(getCharSet(charSetStr));
						charSetStr.clear();
					} else {
						throw std::runtime_error("Invalid Matching Rule.");
					}
					break;
				default:
					if (inBracket) {
						charSetStr += c;
					} else {
						baseStr += c;
					}
					break;
			}
		}
		keys.emplace_back(baseStr);
	}
	if (charSets.size() > 0) {
		int charSetIdx = 0;
		while (charSetIdx < charSets.size()) {
			auto prevKeys = keys;
			keys.clear();
			for (const auto &prevKey : prevKeys) {
				auto pos = prevKey.find("|");
				if (pos != std::string::npos) {
					for (const auto &c : charSets[charSetIdx]) {
						std::string key = prevKey;
						key[pos] = c;
						keys.emplace_back(key);
					}
				}
			}
			charSetIdx++;
		}
	}

	return keys;
}
