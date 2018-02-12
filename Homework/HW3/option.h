#ifndef _OPTION_H_
#define _OPTION_H_
#include "payoff.h"
#include "marketvariable.h"
#include <vector>

enum OptionType { Call = 1, Put = -1 };
enum BinomialType { CRR, RB, LR };

class Option {
public:
    Option() {};
    Option(double strike, double maturity, OptionType type);
    void setMarketVariable(MarketVariable mktVar);
    virtual ~Option();
    virtual double bntprice(unsigned int steps, BinomialType bntType) = 0;
protected:
    /* Market Variables */
    double s_, strike_, r_, div_, t_, sigma_;
    MarketVariable mktVar_;

    /* Option Characteristic */
    Payoff *payoff_;
    OptionType type_;

    /* Binomial Tree Paramaters */
    double u_, d_, q_, dt_;

    /* Internal functions */
    double getd1();
    double getd2();
    double h(double x, double n);
    std::vector<double> makeTree(unsigned int steps, BinomialType bntType);
};

#endif
