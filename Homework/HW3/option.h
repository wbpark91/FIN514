#ifndef _OPTION_H_
#define _OPTION_H_
#include "payoff.h"

enum OptionType { Call = 1, Put = -1 };
enum BinomialType { CRR, RB, LR };

class Option {
public:
    Option(double s, double strike, double r, double div, double t, double sigma,
            OptionType type);
    virtual ~Option();
    virtual double bsprice() = 0;
    virtual double bntprice(unsigned int steps, BinomialType bntType);
protected:
    double s_, strike_, r_, div_, t_, sigma_;
    double getd1();
    double getd2();
    double h(double x, double n);
    Payoff *payoff_;
    OptionType type_;
};

#endif
