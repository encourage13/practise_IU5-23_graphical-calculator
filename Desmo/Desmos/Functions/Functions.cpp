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
		if (pa_el.first.compare(0, 3, "log", 0, 3) == 0) {
			std::cout << "Logo" << std::endl;
			return object = new Logo(pa_el.second, sign);
		}
		else if (pa_el.first.compare(0, 1, "x", 0, 1) == 0) {
			if (pa_el.second.front() == '(') {
				std::cout << "IRR" << std::endl;
				return object = new Irr(pa_el.second, sign);
			}
			else {
				std::cout << "Stepennaya" << std::endl;
				return object = new Degree(pa_el.second, sign);
			}
		}
		else if (TrigFunction(pa_el.first)) {
			std::cout << "TRIG" << std::endl;
			return object = new Trig(pa_el.second, sign);
		}
		else if (pa_el.second.find('^') != std::string::npos) {
			std::cout << "Pokazatelnaya" << std::endl;
			return object = new Indct(pa_el.second, sign);
		}
		else {
			return nullptr;
		}
	}
	catch (const std::invalid_argument& e) {
		std::cerr << "Invalid argument: " << e.what() << std::endl;
		return nullptr;
	}
}

bool Functions::TrigFunction(const std::string& func) {
	static const std::vector<std::string> trigFunctions = { "sin", "arcsin", "arctg", "arcctg", "arccos", "cos", "tg", "ctg" };
	return std::find(trigFunctions.begin(), trigFunctions.end(), func) != trigFunctions.end();
}
Functions::~Functions() {}
void Functions::set(string func) {
	this->Casting(func);
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
			pointer->Find(this->coordinates);
			delete pointer;
		}
	}
}
void Functions::Casting(string func) {
	bool sign;
	vector<string> elements = this->Split(func);
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
	cout << "Function name: " << result1.first << ", Expression: " << result1.second << endl;
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
	return 0;
}

std::vector<std::pair<double, double>> Get(string func) {
	Functions* p = Functions::Create(std::make_pair("log", "loge(2x)"), false);
	p->set(func);
	std::map<double, double> sum_map;
	for (const auto& coord : p->coordinates) {
		bool flag = coord.second;
		for (const auto& elements : coord.first) {
			if (flag) {
				sum_map[elements.x] += elements.y;
			}
			else {
				sum_map[elements.x] -= elements.y;
			}
		}
	}
	std::vector<std::pair<double, double>> result;
	for (const auto& pair : sum_map) {
		result.push_back(std::make_pair(pair.first, pair.second));
	}
	delete p;
	return result;
}

