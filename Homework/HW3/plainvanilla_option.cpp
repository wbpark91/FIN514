#include <cmath>
#include "plainvanilla_option.h"
#include "normal.h"

PlainvanillaPayoff::PlainvanillaPayoff(double strike, OptionType type)
    :strike_(strike), type_(type) {}

double PlainvanillaPayoff::operator()(double s) {
    return MAX(type_ * (s - strike_), 0.0);
}

PlainvanillaOption::PlainvanillaOption(double s, double strike, double r, double q, double t, double sigma,
                    OptionType type): Option(s, strike, r, q, t, sigma, type) {
    payoff_ = new PlainvanillaPayoff(strike, type);
}

double PlainvanillaOption::bsprice() {
    double d1 = getd1();
    double d2 = getd2();
    double nd1 = normcdf(type_ * d1);
    double nd2 = normcdf(type_ * d2);

    return type_ * (s_ * exp(-div_ * t_) * nd1 - strike_ * exp(-r_ * t_) * nd2);
}
