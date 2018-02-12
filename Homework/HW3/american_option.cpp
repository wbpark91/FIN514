#include "american_option.h"
#include "plainvanilla_payoff.h"
#include "u_math.h"
#include <cmath>
#include <iostream>

AmericanOption::AmericanOption(double strike, double maturity, OptionType type)
    :Option(strike, maturity, type) {
    payoff_ = new PlainVanillaPayoff(strike, type);
}

double AmericanOption::bntprice(unsigned int steps, BinomialType bntType) {
    std::vector<double> tree = makeTree(steps, bntType);
    double prevSpot;                /* Spot price at previous period */
    double exValue, contValue;      /* Exercise Value and Continuation Value */
    for (int i = tree.size() - 1; i > 0; --i) {
        for (int j = 0; j < i; ++j) {
            prevSpot = s_ * pow(u_, i - j - 1) * pow(d_, j);
            exValue = (*payoff_)(prevSpot);
            contValue = exp(-r_ * dt_) * (q_ * tree[j] + (1 - q_) * tree[j + 1]);
            tree[j] = MAX(exValue, contValue);
        }
    }
    return tree[0];
}
