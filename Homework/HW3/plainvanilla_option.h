#ifndef _PLAINVANILLA_OPTION_H_
#define _PLAINVANILLA_OPTION_H_
#include "option.h"
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

class PlainvanillaOption: public Option {
public:
    PlainvanillaOption(double s, double strike, double r, double div, double t, double sigma,
                        OptionType type);
    virtual ~PlainvanillaOption() {};
    virtual double bsprice();
private:
};

#endif
