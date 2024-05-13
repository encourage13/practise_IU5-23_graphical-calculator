#pragma once
#include "Functions.h"
class Trig : public Functions {
public:
	Trig(std::string func, bool sign);
	~Trig() override {}
	void Find(std::vector<std::pair<std::vector<Cord>, bool>>& coordinates) override;
	double cot(double x);
	double acot(double x);
private:
	std::vector<Cord> cd;
	std::string func;
	bool sign;
};
