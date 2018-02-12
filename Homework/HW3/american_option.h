#ifndef _AMERICAN_OPTION_H_
#define _AMERICAN_OPTION_H_
#include "option.h"

class AmericanOption: public Option {
public:
    AmericanOption() {}
    AmericanOption(double strike, double maturity, OptionType type);
    ~AmericanOption() {}
    double bntprice(unsigned int steps, BinomialType bntType);
private:
};

#endif
