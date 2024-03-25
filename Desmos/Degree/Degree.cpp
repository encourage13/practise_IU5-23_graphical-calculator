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
}