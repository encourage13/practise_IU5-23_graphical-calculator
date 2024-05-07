#pragma once
#include "Functions.h"
class Indct : public Functions {
public:
	Indct(std::string func, bool sign);
	~Indct() override {}
	void Find() override;
private:
	std::vector<Cord> cd;
	std::string func;
	bool sign;


};