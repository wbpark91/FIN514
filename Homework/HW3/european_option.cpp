#include "european_option.h"
#include <cmath>
#include <vector>

EuropeanOption::EuropeanOption(double strike, double maturity, OptionType type)
    :Option(strike, maturity, type) {}

double EuropeanOption::bntprice(unsigned int steps, BinomialType bntType) {
    double dt = t_ / steps;
    double u, d, q;
    switch (bntType) {
        case CRR:                                /* CRR Tree */
            u = exp(sigma_ * sqrt(dt));          /* Upward node */
            d = 1 / u;                           /* Downward node */
            q = (exp((r_ - div_) * dt) - d) / (u - d);    /* Risk neutral probability */
            break;
        case RB:                                /* Rendleman and Bartter */
            u = exp((r_ - div_ - 0.5 * sigma_ * sigma_) * dt + sigma_ * sqrt(dt));
            d = u / exp(2 * sigma_ * sqrt(dt));
            q = (exp((r_ - div_) * dt) - d) / (u - d);    /* Risk neutral probability */
            break;
        case LR:                                /* Leisen and Reimer */
            q = h(getd2(), steps);
            double q1 = h(getd1(), steps);
            u = exp((r_ - div_) * dt) * q1 / q;
            d = (exp((r_ - div_) * dt) - q * u) / (1 - q);
            break;
    }
    std::vector<double> tree(steps + 1);

    /* Set up final node */
    for (int i = 0; i < tree.size(); ++i) {
        tree[i] = (*payoff_)(s_ * pow(u, steps - i) * pow(d, i));
    }

    /* Backward discount */
    for (int i = tree.size() - 1; i > 0; --i) {
        for (int j = 0; j < i; ++j) {
            tree[j] = exp(-r_ * dt) * (q * tree[j] + (1 - q) * tree[j + 1]);
        }
    }
    return tree[0];
}
