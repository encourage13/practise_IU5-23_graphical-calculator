#pragma once
#include "Functions.h"
class Trig : public Functions {
public:
	Trig(std::string func, bool sign);
	~Trig() override {}
	void Find() override;
	double cot(double x);
	double acot(double x);
private:
	std::vector<Cord> cd;
	std::string func;
	bool sign;


};