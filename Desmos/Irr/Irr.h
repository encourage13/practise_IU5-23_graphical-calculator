#pragma once 
#include "Functions.h"
class Irr : public Functions {
public:
	Irr();
	Irr(string func, bool sign);
	~Irr() override {}
	void Find(string func) override;
private:
	vector<Cord> cd;
	string func;
	bool sign;


};