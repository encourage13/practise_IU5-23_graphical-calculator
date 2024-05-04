#include "Indct.h"
Indct::Indct() {
	this->sign = true;
	this->func = "";
}
Indct::Indct(string func, bool sign) {
	this->func = func;
	this->sign = sign;
}
void Indct::Find(string func) {
	bool flag = false;
	auto it = func.begin();
	if (*it == '-' || *it == '1') { return; } // Исправить для 1.6666
	string argument = this->Defi(func);
	cout << "Аргумент показательной: " << argument << endl;
	if (*it == 'e') { flag = true; }
	string osn;
	osn.push_back(*it);
	for (double x = -10; x < 10.1; x += 0.1) {
		double y = Calculate(x, argument, argument.size());
			Cord ss;
			if (flag == false) {
				double a = stod(osn);
				double y1 = pow(a,y);
				ss.x = x;
				ss.y = y1;
				cd.push_back(ss);
			}
			else {
				double y1 = exp(y);
				ss.x = x;
				ss.y = y1;
				cd.push_back(ss);
			}
	}
	this->coordinates.push_back({ cd,sign });
	for (const auto& it : cd) {
		cout << "X: " << it.x << "   Y: " << it.y << endl;
	}
}