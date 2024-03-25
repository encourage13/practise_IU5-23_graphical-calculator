#pragma once
#include "Functions.h"

class Logo : public Functions {
public:
	Logo();
	Logo(string func, bool sign);
	~Logo() override {}
	void Find(string func) override;
private:
	vector<Cord> cd;
	string func;
	bool sign;


};