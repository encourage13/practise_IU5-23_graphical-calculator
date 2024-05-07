#include "Functions.h"
#include "Logo.h"
#include "Irr.h"
#include "Indct.h"
#include "Trig.h"
#include "Degree.h"
using namespace std;
Functions* Functions::Create(std::pair<std::string, std::string> pa_el, bool sign) {
	Functions* object = nullptr;
	try {
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
			cout << "Logo" << endl;
			object = new Logo(pa_el.second, sign);
		}
		else if (pa_el.first.compare(0, 1, "x", 0, 1) == 0) {
			auto it = pa_el.second.begin();
			if (*it == '(') {
				cout << "IRR" << endl;
				object = new Irr(pa_el.second, sign);
			}
			else {
				cout << "Stepennaya" << endl;
				object = new Degree(pa_el.second, sign);
			}
		}
		else if (flag) {
			cout << "TRIG" << endl;
			object = new Trig(pa_el.second, sign);
		}
		else if (flag1) {
			cout << "Pokazatelnaya" << endl;
			object = new Indct(pa_el.second, sign);
		}
		else {
			return nullptr;
		}
	}
	catch (invalid_argument& e) {
		cerr << "Ошибка: " << e.what() << endl;
	}
	return object;
}
Functions::~Functions() {}
void Functions::set() {
	this->Casting();
	for (const auto& tup_el : this->vec) {
		pair<string, string> pa_el = get<0>(tup_el);
		bool sign = get<1>(tup_el);
		Functions* pointer = Functions::Create(pa_el, sign);
		if (pointer == nullptr) {
			cout << "value" << endl;
			double value = stod(pa_el.second);
			cout << value << endl;
			this->sum_value.push_back({ value, sign });
		}
		else {
			pointer->Find();
			delete pointer;
		}
	}
}
double Functions::SumValue() {
	double value = 0;
	for (auto pa_el : this->sum_value) {
		if (pa_el.second == false) {
			pa_el.first *= -1;
		}
		value += pa_el.first;
	}
	return value;
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
double Functions::Calculate(double x, string func, int size) {
	if (func[0] == 'e' && size == 1) {
		return 2.71828;
	}
	if (func[0] == 'x' && size == 1) {
		return x;
	}
	if (isdigit(func[0])) {
		bool flag = true;
		for (int i = 0; i < size; i++) {
			if (!isdigit(func[i]) && (func[i] != '.'&& func[i] != ',')) {
				flag = false;
				break;
			}
		}
		if (flag) {
			return stod(func);
		}
	}
	for (int i = 0; i < size; i++) {
		if (func[i] == '+') {
			return Calculate(x, &func[0], i) + Calculate(x, &func[i + 1], size - i - 1);
		}
		if (func[i] == '-') {
			if (i == 0 || func[i - 1] == '(') {
				return 0 - Calculate(x, &func[i + 1], size - i - 1);
			}
			else {
				return Calculate(x, &func[0], i) - Calculate(x, &func[i + 1], size - i - 1);
			}
		}
		if (func[i] == '(') {
			int k = 1;
			i++;
			for (i; k > 0; i++) {
				if (func[i] == ')') {
					k--;
				}
				else if (func[i] == '(') {
					k++;
				}
			}
			i--;
		}
	}
	for (int i = 0; i < size - 1; i++) {
		if (func[i] == '*') {
			return Calculate(x, &func[0], i) * Calculate(x, &func[i + 1], size - i - 1);
		}
		if (func[i] == '/') {
			return Calculate(x, &func[0], i) / Calculate(x, &func[i + 1], size - i - 1);
		}
		if (func[i] == '(') {
			int k = 1;
			i++;
			for (i; k > 0; i++) {
				if (func[i] == ')') {
					k--;
				}
				else if (func[i] == '(') {
					k++;
				}
			}
			i--;
		}
		//string mas = "*/^)";
		if ((func[i] == 'x' && (func[i + 1] != '*' && func[i + 1] != '/' && func[i + 1] != '^' && func[i + 1] != ')')) || (func[i] == 'e' && (func[i + 1] != '*' && func[i + 1] != '/' && func[i + 1] != '^' && func[i + 1] != ')')) || (isdigit(func[i]) && ((func[i + 1] != '.' && func[i+1]!=',') && func[i + 1] != '*' && func[i + 1] != '/' && func[i + 1] != '^' && func[i + 1] != ')' && !isdigit(func[i + 1]))) || (func[i] == ')' && (func[i + 1] != '*' && func[i + 1] != '/' && func[i + 1] != '^' && func[i + 1] != ')' && i != size - 1))) {
			return Calculate(x, &func[0], i + 1) * Calculate(x, &func[i + 1], size - i - 1);
		}
	}
	for (int i = 0; i < size; i++) {
		if (func[i] == '^') {
			if (func[i + 1] != '(') {
				int j = 0;
				for (j = i + 1; j < size; j++) {
					if (!isdigit(func[j]) && (func[j] != '.' && func[j]!=',')) {
						break;
					}
				}
				return pow(Calculate(x, &func[0], i), Calculate(x, &func[i + 1], j - i - 1));
			}
			if (func[i + 1] == '(') {
				int j;
				int k = 1;
				for (j = i + 2; k > 0; j++) {
					if (func[j] == ')') {
						k--;
					}
					else if (func[j] == '(') {
						k++;
					}
				}
				return pow(Calculate(x, &func[0], i), Calculate(x, &func[i + 1], j - i - 1));
			}
		}
		if (func[i] == '(') {
			int k = 1;
			i++;
			for (i; k > 0; i++) {
				if (func[i] == ')') {
					k--;
				}
				else if (func[i] == '(') {
					k++;
				}
			}
			i--;
		}
	}
	if (func[0] == '(') {
		return Calculate(x, &func[1], size - 2);
	}
	if (func[0] == 's' && func[1] == 'i' && func[2] == 'n') {
		return sin(Calculate(x, &func[3], size - 3));
	}
	if (func[0] == 'c' && func[1] == 'o' && func[2] == 's') {
		return cos(Calculate(x, &func[3], size - 3));
	}
	if (func[0] == 't' && func[1] == 'g') {
		return tan(Calculate(x, &func[2], size - 2));
	}
	if (func[0] == 'a' && func[1] == 'b' && func[2] == 's') {
		return abs(Calculate(x, &func[3], size - 3));
	}
}


