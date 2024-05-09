#include "Degree.h"
using namespace std;

Degree::Degree(string func, bool sign) {
	this->func = func;
	this->sign = sign;
}
void Degree::Find(std::vector<std::pair<std::vector<Cord>, bool>>& coordinates) {
	string argument;
	bool flag = false;
	auto it = this->func.begin();
	if (*it == '|') {
		flag = true;
		it++;
		for (it; *it != '|'; it++) {
			argument += *it;
		}
	}
	else { argument = this->func; }
	if (flag) { cout << "�������� ������: " << argument << endl; }
	else { cout << "�������� ���������: " << argument << endl; }
	for (double x = A; x < B; x += 0.125) {
		double y = Calculate(x, argument, argument.size());
		Cord ss;
		if (flag) {
			double y1 = abs(y);
			ss.x = x;
			ss.y = y1;
			this->cd.push_back(ss);
		}
		else {
			ss.x = x;
			ss.y = y;
			this->cd.push_back(ss);
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
	/*for (auto pa_el : coordinates) {
		std::vector<Cord> vec1 = pa_el.first;
		for (auto elem : vec1) {
			std::cout << elem.x << ' ';
		}
	}*/
}
