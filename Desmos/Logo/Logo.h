#pragma once
#include "Functions.h"

class Logo : public Functions {
public:
	Logo();
	Logo(string func, bool sign);
	~Logo() override {}
	void Find(string func) override;
	double log_base_a(double x, double a);
private:
	vector<Cord> cd;
	string func;
	bool sign;


};