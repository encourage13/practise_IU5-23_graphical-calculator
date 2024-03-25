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
	auto it = func.begin();
	if (*it == '-' || *it == '1') { return; }
	string argument = this->Defi(func);
	cout << "Аргумент показательной: " << argument << endl;
}