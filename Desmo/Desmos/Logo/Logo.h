#pragma once
#include "Functions.h"

class Logo : public Functions {
public:
	Logo();
	Logo(std::string func, bool sign);
	~Logo() override {}
	void Find(std::vector<std::pair<std::vector<Cord>, bool>>& coordinates) override;
	double log_base_a(double x, double a);
private:
	std::vector<Cord> cd;
	std::string func;
	bool sign;
	friend std::vector<std::pair<double, double>> Get(std::string func);
};
