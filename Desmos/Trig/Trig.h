#pragma once
#include "Functions.h"
class Trig : public Functions {
public:
	Trig();
	Trig(string func, bool sign);
	~Trig() override {}
	void Find(string func) override;
	double cot(double x);
	double acot(double x);
private:
	vector<Cord> cd;
	string func;
	bool sign;


};