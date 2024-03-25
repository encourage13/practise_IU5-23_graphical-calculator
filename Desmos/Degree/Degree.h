#pragma once
#include "Functions.h"
class Degree : public Functions {
public:
	Degree();
	Degree(string func, bool sign);
	~Degree() override {}
	void Find(string func) override;
private:
	vector<Cord> cd;
	string func;
	bool sign;


};