#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <regex>
#include<tuple>

struct Cord {
	double x;
	double y;
};
using namespace std;
class Logo;
class Indct;
class Trig;
class Degree;
class Irr;

class Functions {

protected:
	vector<tuple<pair<string, string>, bool>> vec;
public:
	virtual void Find(string func) = 0;
	virtual ~Functions() = 0;
	void set();
	void Casting();
	vector<string> Split(const string& expression);
	pair<string, string> detectMathFunction(const string& str);
	string Defi(string func);
};
