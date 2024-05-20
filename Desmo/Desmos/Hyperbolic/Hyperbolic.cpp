#include "Hyperbolic.h"
using namespace std;
Hyperbolic::Hyperbolic(string func, bool sign) {
    this->func = func;
    this->sign = sign;
}
double Hyperbolic::coth(double x) {
    return 1 / tanh(x);
}

double Hyperbolic::acoth(double x) {
    return atanh(1 / x);
}

double Hyperbolic::sinh(double x) {
    return (exp(x) - exp(-x)) / 2.0;
}

double Hyperbolic::cosh(double x) {
    return (exp(x) + exp(-x)) / 2.0;
}

double Hyperbolic::asinh(double x) {
    return log(x + sqrt(x * x + 1));
}

double Hyperbolic::acosh(double x) {
    return log(x + sqrt(x * x - 1));
}
double Hyperbolic::atanh(double x) {
    return 0.5 * log((1 + x) / (1 - x));
}
void Hyperbolic::Find(std::vector<std::pair<std::vector<Cord>, bool>>& coordinates) {
    string argument = this->Defi(this->func);
    cout << "Аргумент гиперболической: " << argument << endl;
    string osn;
    for (auto it = this->func.begin(); it != this->func.end(); it++) {
        if (*it == '(') {
            break;
        }
        osn += *it;
    }
    if (osn == "sinh") {
        for (double x = -10; x < 10.125; x += 0.125) {
            double y = Calculate(x, argument, argument.size());
            Cord ss;
            double y1 = sinh(y);
            ss.x = x;
            ss.y = y1;
            this->cd.push_back(ss);
        }
    }
    if (osn == "cosh") {
        for (double x = -10; x < 10.125; x += 0.125) {
            double y = Calculate(x, argument, argument.size());
            Cord ss;
            double y1 = cosh(y);
            ss.x = x;
            ss.y = y1;
            this->cd.push_back(ss);
        }
    }
    if (osn == "asinh") {
        for (double x = -10; x < 10.125; x += 0.125) {
            double y = Calculate(x, argument, argument.size());
            Cord ss;
            double y1 = asinh(y);
            ss.x = x;
            ss.y = y1;
            this->cd.push_back(ss);
        }
    }
    if (osn == "acosh") {
        for (double x = -10; x < 10.125; x += 0.125) {
            double y = Calculate(x, argument, argument.size());
            Cord ss;
            double y1 = acosh(y);
            ss.x = x;
            ss.y = y1;
            this->cd.push_back(ss);
        }
    }
    if (osn == "coth") {
        for (double x = -10; x < 10.125; x += 0.125) {
            double y = Calculate(x, argument, argument.size());
            Cord ss;
            double y1 = coth(y);
            ss.x = x;
            ss.y = y1;
            this->cd.push_back(ss);
        }
    }
    if (osn == "acoth") {
        for (double x = -10; x < 10.125; x += 0.125) {
            double y = Calculate(x, argument, argument.size());
            Cord ss;
            double y1 = acoth(y);
            ss.x = x;
            ss.y = y1;
            this->cd.push_back(ss);
        }
    }
    if (osn == "atanh") {
        for (double x = -10; x < 10.125; x += 0.125) {
            double y = Calculate(x, argument, argument.size());
            Cord ss;
            double y1 = atanh(y);
            ss.x = x;
            ss.y = y1;
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
}