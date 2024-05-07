#pragma once
#include "Functions.h"
class Degree : public Functions {
public:
	Degree(std::string func, bool sign);
	~Degree() override {}
	void Find() override;
private:
	std::vector<Cord> cd;
	std::string func;
	bool sign;


};