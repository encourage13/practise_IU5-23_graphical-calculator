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
	int index = 0;
	for (int i = 0; i != func.size(); i++) {
		if (func[i] == '^') {
			index = i;
		}
	}
	index++;
	string save;
	for (index; index!=func.size(); index++) {
		save += func[index];
	}
	for (double x = -10; x < 10.1; x += 0.125) {
		double y = Calculate(x, argument, argument.size());
		Cord ss;
		double a = stod(save);
		double y1 = pow(y, a);   // корень четной степени из отриц числа 
		ss.x = x;
		ss.y = y1;
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
