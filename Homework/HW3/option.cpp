#include "option.h"
#include <cmath>

Option::Option(double strike, double maturity, OptionType type)
    :strike_(strike), t_(maturity), type_(type) { }

Option::~Option() {
    delete payoff_;
}

void Option::setMarketVariable(MarketVariable mktVar) {
    mktVar_ = mktVar;
    s_ = mktVar.getSpot();
    r_ = mktVar.getRate();
    div_ = mktVar.getDiv();
    sigma_ = mktVar.getVol();
}

double Option::getd1() {
    return (log(s_ / strike_) + (r_ - div_ + 0.5 * sigma_ * sigma_)) / (sigma_ * sqrt(t_));
}

double Option::getd2() {
    return getd1() - sigma_ * sqrt(t_);
}

double Option::h(double x, double n) {
    int sgnx;            /* sign of x */
    /* Implement sign(x) */
    if (x >= 0)
        sgnx = 1;
    else
        sgnx = -1;
    double result = 0.5 + sgnx * sqrt(0.25 - 0.25 * exp(-(x / (n + 1 / 3.0)) *
                            (x / (n + 1 / 3.0)) * (n + 1 / 6.0)));
    return result;
}
