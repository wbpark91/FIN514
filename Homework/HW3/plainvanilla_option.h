#ifndef _PLAINVANILLA_OPTION_H_
#define _PLAINVANILLA_OPTION_H_
#include "european_option.h"
#include "payoff.h"
#define MAX(x, y)   (((x) > (y)) ? (x) : (y))

class PlainvanillaPayoff: public Payoff {
public:
    PlainvanillaPayoff(double strike, OptionType type);
    virtual double operator()(double s);
private:
    double strike_;
    OptionType type_;
};

class PlainvanillaOption: public EuropeanOption {
public:
    PlainvanillaOption() {}
    PlainvanillaOption(double strike, double maturity, OptionType type);
    virtual ~PlainvanillaOption() {};
    virtual double bsprice();
private:
};

#endif
