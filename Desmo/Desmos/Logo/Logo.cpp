#include "Logo.h"
using namespace std;

Logo::Logo() {
	this->func = "";
	this->sign = true;
}
Logo::Logo(string func, bool sign) {
	this->func = func;
	this->sign = sign;
}
double Logo::log_base_a(double x, double a) {
	return std::log(x) / std::log(a);
}
void Logo::Find(std::vector<std::pair<std::vector<Cord>, bool>>& coordinates) {
	bool flag = false;
	auto it = this->func.begin();
	it += 3;
	if (*it == '1' && (*(it + 1) == '\0' || *(it + 1) == '(')) { return; }
	if (*it == '0') { return; }
	if (*it == 'e') flag = true;
	string osn(it, find(it, this->func.end(), '('));
	string argument = this->Defi(this->func);
	cout << "Аргумент логарифма: " << argument << endl;
	for (double x = A; x < B; x += C) {
		double y = Calculate(x, argument, argument.size());
		if (y > 0) {
			Cord ss;
			if (flag == false) {
				double a = stod(osn);
				double y1 = log_base_a(y, a);
				ss.x = x;
				ss.y = y1;
				this->cd.push_back(ss);
			}
			else {
				double y1 = log(y);
				ss.x = x;
				ss.y = y1;
				this->cd.push_back(ss);
			}
		}
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
	coordinates.push_back({ this->cd,this->sign });
}