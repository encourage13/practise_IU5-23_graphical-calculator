#include "Irr.h"
using namespace std;

Irr::Irr(string func, bool sign) {
	this->func = func;
	this->sign = sign;
}
void Irr::Find(std::vector<std::pair<std::vector<Cord>, bool>>& coordinates) {
	bool flag = false;
	string argument = this->Defi(this->func);
	cout << "�������� ��������������: " << argument << endl;
	int index = 0;
	for (int i = 0; i != this->func.size(); i++) {
		if (this->func[i] == '^') {
			index = i;
		}
	}
	index++;
	string save;
	for (index; index != this->func.size(); index++) {
		save += this->func[index];
	}
	for (double x = A; x < B; x += 0.125) {
		double y = Calculate(x, argument, argument.size());
		Cord ss;
		double a = stod(save);
		double y1 = pow(y, a);
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
	coordinates.push_back({ this->cd,this->sign });
	/*for (auto pa_el : coordinates) {
		std::vector<Cord> vec1 = pa_el.first;
		for (auto elem : vec1) {
			std::cout << elem.x << ' ';
		}
	}*/
}
