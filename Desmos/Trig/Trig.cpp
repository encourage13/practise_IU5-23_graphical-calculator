#include "Trig.h"
Trig::Trig() {
	this->sign = true;
	this->func = "";
}
Trig::Trig(string func, bool sign) {
	this->func = func;
	this->sign = sign;
}
double Trig::cot(double x) {
	return 1 / tan(x);
}
double Trig::acot(double x) {
	return atan(1 / x);
}
void Trig::Find(string func) {
	string argument = this->Defi(func);
	cout << "Аргумент тригонометрической: " << argument << endl;
	string osn;
	for (auto it = func.begin(); it != func.end(); it++) {
		if (*it == '(') {
			break;
		}
		osn += *it;
	}
	if (osn == "sin") {
		for (double x = -10; x < 10.1; x += 0.1) {
			double y = Calculate(x, argument);
			Cord ss;
			double y1 = sin(y);
			ss.x = x;
			ss.y = y1;
			cd.push_back(ss);
		}
	}
	if (osn == "cos") {
		for (double x = -10; x < 10.1; x += 0.1) {
			double y = Calculate(x, argument);
			Cord ss;
			double y1 = cos(y);
			ss.x = x;
			ss.y = y1;
			cd.push_back(ss);
		}
	}
	if (osn == "arcsin") {
		for (double x = -10; x < 10; x += 0.1) {
			double y = Calculate(x, argument);
			if (y <= 1 && y >= -1) {
				Cord ss;
				double y1 = asin(y);
				ss.x = x;
				ss.y = y1;
				cd.push_back(ss);
			}
		}
	}
	if (osn == "arccos") {
		for (double x = -10; x < 10 ; x += 0.1) {
			double y = Calculate(x, argument);
			if (y <= 1 && y >= -1) {
				Cord ss;
				double y1 = acos(y);
				ss.x = x;
				ss.y = y1;
				cd.push_back(ss);
			}
		}
	}
	if (osn == "arctg") {
		for (double x = -10; x < 10.1; x += 0.1) {
			double y = Calculate(x, argument);
			Cord ss;
			double y1 = atan(y);
			ss.x = x;
			ss.y = y1;
			cd.push_back(ss);
		}
	}
	if (osn == "arcctg") {
		for (double x = -10; x < 10.1; x += 0.1) {
			double y = Calculate(x, argument);
			Cord ss;
			double y1 = acot(y);
			ss.x = x;
			ss.y = y1;
			cd.push_back(ss);
		}
	}
	if (osn == "tg") {
		for (double x = -10; x < 10.1; x += 0.1) {
			double y = Calculate(x, argument);
			Cord ss;
			double y1 = tan(y);            // Проверять на п/2 + п*n
			ss.x = x;
			ss.y = y1;
			cd.push_back(ss);
		}
	}
	if (osn == "ctg") {
		for (double x = -10; x < 10.1; x += 0.1) {
			double y = Calculate(x, argument);
			Cord ss;
			double y1 = cot(y);            // Проверять на п*n
			ss.x = x;
			ss.y = y1;
			cd.push_back(ss);
		}
	}
	for (const auto& it : cd) {
		cout << "X: " << it.x << "   Y: " << it.y << endl;
	}
}


