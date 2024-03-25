#pragma once
#include "Functions.h"
class Indct : public Functions {
public:
	Indct();
	Indct(string func, bool sign);
	~Indct() override {}
	void Find(string func) override;
private:
	vector<Cord> cd;
	string func;
	bool sign;


};