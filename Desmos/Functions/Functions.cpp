#include "Functions.h"
#include "Logo.h"
#include "Irr.h"
#include "Indct.h"
#include "Trig.h"
#include "Degree.h"
Functions::~Functions() {}
void Functions::set() {
	this->Casting();
	/*for (const auto& tupleElem : vec) {
		std::pair<std::string, std::string> pairElem = std::get<0>(tupleElem);
		bool boolElem = std::get<1>(tupleElem);
	}*/
	auto tup_el = this->vec[0];
	pair<string, string> pa_el = get<0>(tup_el);
	bool sign = get<1>(tup_el);
	string mas[] = { "sin","arcsin","arctg","arcctg","arccos","cos","tg","ctg" };
	bool flag = false;
	bool flag1 = false;
	for (const string& element : mas) {
		if (element == pa_el.first) {
			flag = true;
			break;
		}
	}
	for (auto element = pa_el.second.begin(); element != pa_el.second.end(); element++) {
		if (*element == '^') {
			flag1 = true;
			break;
		}
	}
	if (pa_el.first.compare(0, 3, "log", 0, 3) == 0) {
		Functions* pointer = new Logo(pa_el.second, sign);
		cout << "Logo" << endl;
		pointer->Find(pa_el.second);
		delete pointer;

	}
	else if (pa_el.first.compare(0, 1, "x", 0, 1) == 0) {
		auto it = pa_el.second.begin();
		if (*it == '(') {
			cout << "IRR" << endl;
			Functions* pointer = new Irr(pa_el.second, sign);
			pointer->Find(pa_el.second);
			delete pointer;
		}
		else {
			cout << "Stepennaya" << endl;
			Functions* pointer = new Degree(pa_el.second, sign);
			pointer->Find(pa_el.second);
			delete pointer;
		}
	}
	else if (flag) {
		cout << "TRIG" << endl;
		Functions* pointer = new Trig(pa_el.second, sign);
		pointer->Find(pa_el.second);
		delete pointer;
	}
	else if (flag1) {
		cout << "Pokazatelnaya" << endl;
		Functions* pointer = new Indct(pa_el.second, sign);
		pointer->Find(pa_el.second);
		delete pointer;
	}
	else {
		cout << "value" << endl;
	}
}
void Functions::Casting() {
	setlocale(LC_ALL, "RUS");
	string str;
	bool sign;
	getline(std::cin, str);
	vector<string> elements = this->Split(str);
	for (const auto& element : elements) {
		cout << element << endl;
	}
	auto it = elements.begin();
	if (*it != "-") {
		sign = true;
		auto result1 = detectMathFunction(*it);
		this->vec.push_back({ {result1}, sign });
		it++;
	}
	for (it; it != elements.end(); it++) {
		if (*it == "-") {
			sign = false;
			it++;
			auto result1 = detectMathFunction(*it);
			this->vec.push_back({ {result1}, sign });
		}
		else {
			sign = true;
			it++;
			auto result1 = detectMathFunction(*it);
			this->vec.push_back({ {result1}, sign });
		}
	}
	auto result1 = detectMathFunction(elements[0]);
	cout << "Название функции: " << result1.first << ", Выражение: " << result1.second << endl;
}
vector<string> Functions::Split(const string& expression) {
	vector<string> elements;
	istringstream iss(expression);
	string element;
	while (iss >> element) {
		elements.push_back(element);
	}
	return elements;
}
pair<string, string> Functions::detectMathFunction(const string& str) {
	regex mathFunctionRegex("([a-zA-Z]+)|(\\d+(?:\\.\\d+)?)(\\^[0-9]+)?([a-zA-Z])?");

	smatch match;
	if (regex_search(str, match, mathFunctionRegex)) {
		if (match[2].length() > 0 && match[4].length() > 0) {
			return make_pair(match[4], str);
		}
		return make_pair(match.str(), str);
	}
	else {
		return make_pair("Не найдено", "Математическая функция не найдена или не соответствует общему шаблону");
	}
}
string Functions::Defi(string func) {
	smatch match;
	regex argRegex("\\((.+)\\)");
	regex_search(func, match, argRegex);
	if (!match.empty()) {
		string argument = match[1];
		return argument;
	}
	else {
		return "Не удалось извлечь аргумент из функции.";
	}
}

double Functions::Calculate(double x, string save) {
	double y = x + 5;
	return y;
}

