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
	string argument = this->Defi(func);
	cout << "Аргумент иррациональной: " << argument << endl;
}