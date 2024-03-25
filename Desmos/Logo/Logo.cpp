#include "Logo.h"
Logo::Logo() {
	this->sign = true;
	this->func = "";
}
Logo::Logo(string func, bool sign) {
	this->func = func;
	this->sign = sign;
}
void Logo::Find(string func) {
	bool flag = false;
	auto it = func.begin();
	it += 3;
	if (*it == '1' || *it == '0') { return; }
	if (*it == 'e') flag = true;
	string argument = this->Defi(func);
	cout << "Аргумент логарифма: " << argument << endl;
	//       Продолжить
}