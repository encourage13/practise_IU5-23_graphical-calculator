#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <regex>
#include <tuple>
#include <cmath>
#include <map>

struct Cord {
	double x;
	double y;
};
class Logo;
class Indct;
class Trig;
class Degree;
class Irr;
class GlobalVariables;

class GlobalVariables {
private:
	static GlobalVariables* instance;
	GlobalVariables();

public:

	double A;
	double B;
	double C;

	static GlobalVariables* getInstance();
	void setA(double A);
	void setB(double B);
	void setC(double C);
};


class Functions {
protected:
	std::vector<std::tuple<std::pair<std::string, std::string>, bool>> vec;
	std::vector<std::pair<double, bool>> sum_value;
	std::vector<std::pair<std::vector<Cord>, bool>> coordinates;
	friend std::vector<std::pair<double, double>> Get(std::string func);
	
public:
	static Functions* Create(std::pair<std::string, std::string> pa_el, bool sign);
	virtual void Find(std::vector<std::pair<std::vector<Cord>, bool>>& coordinates) = 0;
	virtual ~Functions() = 0;
	void set(std::string func);
	void Casting(std::string func);
	std::vector<std::string> Split(const std::string& expression);
	std::pair<std::string, std::string> detectMathFunction(const std::string& str);
	std::string Defi(std::string func);
	double Calculate(double x, std::string func, int size);
	static bool TrigFunction(const std::string& func);
	static bool HyperbolicFunction(const std::string& func);
	
};
std::vector<std::pair<double, double>> Get(std::string func);

