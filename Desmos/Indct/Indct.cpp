#include "Indct.h"
using namespace std;

Indct::Indct(string func, bool sign) {
	this->func = func;
	this->sign = sign;
}
void Indct::Find() {
	bool flag = false;
	auto it = this->func.begin();
	if (*it == '1' && *(it + 1) != '.' && *(it + 1) != ',') { return; }
	if (*it == '-') { return; } 
	string argument = this->Defi(this->func);
	cout << "Аргумент показательной: " << argument << endl;
	if (*it == 'e') { flag = true; }
	string osn;
	for (it; *it != '^'; it++) {
		osn += *it;
	}
	for (double x = -10; x < 10.1; x += 0.125) {
		double y = Calculate(x, argument, argument.size());
			Cord ss;
			if (flag == false) {
				double a = stod(osn);
				double y1 = pow(a,y);
				ss.x = x;
				ss.y = y1;
				this->cd.push_back(ss);
			}
			else {
				double y1 = exp(y);
				ss.x = x;
				ss.y = y1;
				this->cd.push_back(ss);
			}
	}
	int j = this->cd.size();
	for (int i = 0; i < j;) {
		if (isfinite(this->cd[i].y) == false) {
			cd.erase(this->cd.begin() + i);
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