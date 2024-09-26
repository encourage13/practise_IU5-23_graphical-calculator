#pragma once
#include "Functions/Functions.h"
class Hyperbolic : public Functions {
public:
    Hyperbolic(std::string func, bool sign);
    ~Hyperbolic() override {}
    void Find(std::vector<std::pair<std::vector<Cord>, bool>>& coordinates) override;
    double sinh(double x);
    double cosh(double x);
    double coth(double x);
    double acoth(double x);
    double asinh(double x);
    double acosh(double x);
    double atanh(double x);
private:
    std::vector<Cord> cd;
    std::string func;
    bool sign;
};
