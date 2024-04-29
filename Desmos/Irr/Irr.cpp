#include "Irr.h"
Irr::Irr() {
	this->sign = true;
	this->func = "";
}
Irr::Irr(string func, bool sign) {
	this->func = func;
	this->sign = sign;
}
void Irr::Find(string func) {
	bool flag = false;
	string argument = this->Defi(func);
	cout << "Аргумент иррациональной: " << argument << endl;
	string save = argument;
	int index = 0;
	for (int i = 0; i != func.size(); i++) {
		if (func[i] == '^') {
			index = i;
		}
	}
	index++;
	string save2;
	for (index; index!=func.size(); index++) {
		save2 += func[index];
	}
	for (double x = -10; x < 10.1; x += 0.1) {
		double y = Calculate(x, save);
		Cord ss;
		double a = stod(save2);
		double y1 = pow(y, a);   // корень четной степени из отриц числа 
		ss.x = x;
		ss.y = y1;
		cd.push_back(ss);
	}
	for (const auto& it : cd) {
		cout << "X: " << it.x << "   Y: " << it.y << endl;
	}
}
