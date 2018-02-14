#include "american_option.h"
#include "plainvanilla_payoff.h"
#include "plainvanilla_option.h"
#include "u_math.h"
#include <cmath>
#include <iostream>

AmericanOption::AmericanOption(double strike, double maturity, OptionType type)
    :Option(strike, maturity, type) {
    payoff_ = new PlainVanillaPayoff(strike, type);
}

double AmericanOption::bntprice(unsigned int steps, BinomialType bntType) {
    std::vector<double> tree;
    if (bntType == BD) {                    /* Broadie and Detemple Method */
        tree.resize(steps);    /* Tree at N - 1 */

        /* Use parameters of CRR */
        dt_ = t_ / steps;
        u_ = exp(sigma_ * sqrt(dt_));                      /* Upward node */
        d_ = 1 / u_;                                       /* Downward node */
        q_ = (exp((r_ - div_) * dt_) - d_) / (u_ - d_);    /* Risk neutral probability */

        PlainVanillaOption vOption(strike_, dt_, type_);    /* European option for calculating last node */
        vOption.setMarketVariable(mktVar_);

        /* Payoff setting at last node */
        for (int i = 0; i < tree.size(); ++i) {
            double spot = s_ * pow(u_, steps - i - 1) * pow(d_, i);
            vOption.setSpot(spot);
            tree[i] = MAX(vOption.bsprice(), (*payoff_)(spot));
        }
    }
    else {                              /* Other Method */
        tree = makeTree(steps, bntType);
    }

    /* Backward induction */
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
