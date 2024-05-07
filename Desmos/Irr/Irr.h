#pragma once 
#include "Functions.h"
class Irr : public Functions {
public:
	Irr(std::string func, bool sign);
	~Irr() override {}
	void Find() override;
private:
	std::vector<Cord> cd;
	std::string func;
	bool sign;


};