#pragma once
#include "Functions.h"
class Indct : public Functions {
public:
	Indct(std::string func, bool sign);
	~Indct() override {}
	void Find(std::vector<std::pair<std::vector<Cord>, bool>>& coordinates) override;
private:
	std::vector<Cord> cd;
	std::string func;
	bool sign;
};