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

std::vector<double> Option::makeTree(unsigned int steps, BinomialType bntType) {
    dt_ = t_ / steps;

    switch (bntType) {
        case CRR:                                /* CRR Tree */
            u_ = exp(sigma_ * sqrt(dt_));          /* Upward node */
            d_ = 1 / u_;                           /* Downward node */
            q_ = (exp((r_ - div_) * dt_) - d_) / (u_ - d_);    /* Risk neutral probability */
            break;
        case RB:                                /* Rendleman and Bartter */
            u_ = exp((r_ - div_ - 0.5 * sigma_ * sigma_) * dt_ + sigma_ * sqrt(dt_));
            d_ = u_ / exp(2 * sigma_ * sqrt(dt_));
            q_ = (exp((r_ - div_) * dt_) - d_) / (u_ - d_);    /* Risk neutral probability */
            break;
        case LR:                                /* Leisen and Reimer */
            q_ = h(getd2(), steps);
            double q1 = h(getd1(), steps);
            u_ = exp((r_ - div_) * dt_) * q1 / q_;
            d_ = (exp((r_ - div_) * dt_) - q_ * u_) / (1 - q_);
            break;
    }
    std::vector<double> tree(steps + 1);

    /* Set up final node */
    for (int i = 0; i < tree.size(); ++i) {
        tree[i] = (*payoff_)(s_ * pow(u_, steps - i) * pow(d_, i));
    }

    return tree;
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
