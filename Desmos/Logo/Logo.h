#pragma once
#include "Functions.h"

class Logo : public Functions {
public:
	Logo();
	Logo(std::string func, bool sign);
	~Logo() override {}
	void Find() override;
	double log_base_a(double x, double a);
private:
	std::vector<Cord> cd;
	std::string func;
	bool sign;


};