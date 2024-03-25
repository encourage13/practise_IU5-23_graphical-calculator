#include "Trig.h"
Trig::Trig() {
	this->sign = true;
	this->func = "";
}
Trig::Trig(string func, bool sign) {
	this->func = func;
	this->sign = sign;
}
void Trig::Find(string func) {
	string argument = this->Defi(func);
	cout << "Аргумент тригонометрической: " << argument << endl;
}