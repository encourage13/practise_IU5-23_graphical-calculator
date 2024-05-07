#include "Degree.h"
Degree::Degree() {
	this->sign = true;
	this->func = "";
}
Degree::Degree(string func, bool sign) {
	this->func = func;
	this->sign = sign;
}
void Degree::Find(string func) {
	string argument = func;
	cout << "Аргумент степенной: " << argument << endl;
	for (double x = -10; x < 10.1; x += 0.125) {
		double y = Calculate(x, argument, argument.size());
		Cord ss;
			ss.x = x;
			ss.y = y;
			this->cd.push_back(ss);
	}
	int j = this->cd.size();
	for (int i = 0; i < j;) {
		if (isfinite(this->cd[i].y) == false) {
			this->cd.erase(this->cd.begin() + i);
			j--;
		}
		else {
			i++;
		}
	}
	this->coordinates.push_back({ this->cd,this->sign });
	for (const auto& it : this->cd) {
		cout << "X: " << it.x << "   Y: " << it.y << endl;
	}
}