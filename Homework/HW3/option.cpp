#include <vector>
#include <cmath>
#include "option.h"

Option::Option(double s, double strike, double r, double div, double t, double sigma,
                OptionType type)
    :s_(s), strike_(strike), r_(r), div_(div), t_(t), sigma_(sigma), type_(type) {}

Option::~Option() {
    delete payoff_;
}

/* Pricing using binomial tree */
double Option::bntprice(unsigned int steps, BinomialType bntType) {
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
    double result = 0.5 + sgnx * sqrt(0.25 - 0.25 * exp(-(x / (n + 1 / 3)) *
                            (x / (n + 1 / 3)) * (n + 1 / 6)));
    return result;
}
