#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <regex>
#include<tuple>
#include <cmath>

struct Cord {
	double x;
	double y;
};
class Logo;
class Indct;
class Trig;
class Degree;
class Irr;

class Functions {

protected:
	std::vector<std::tuple<std::pair<std::string, std::string>, bool>> vec;
	std::vector<std::pair<double,bool>> sum_value;
	std::vector<std::pair<std::vector<Cord>, bool>> coordinates;
public:
	static Functions* Create(std::pair<std::string, std::string> pa_el, bool sign);
	virtual void Find() = 0;
	virtual ~Functions() = 0;
	void set(); // íà âõîä str
	void Casting(); //  íà âõîä str
	std::vector<std::string> Split(const std::string& expression);
	std::pair<std::string, std::string> detectMathFunction(const std::string& str);
	std::string Defi(std::string func);
	double Calculate(double x, std::string func,int size);
	double SumValue();
};
