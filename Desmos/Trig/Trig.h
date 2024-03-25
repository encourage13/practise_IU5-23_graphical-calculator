#pragma once
#include "Functions.h"
class Trig : public Functions {
public:
	Trig();
	Trig(string func, bool sign);
	~Trig() override {}
	void Find(string func) override;
private:
	vector<Cord> cd;
	string func;
	bool sign;


};