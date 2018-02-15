#include "barrier_option.h"
#include "barrier_payoff.h"
#include "normal.h"
#include <cmath>
#include <vector>

BarrierOption::BarrierOption(double strike, double barrier, double maturity, OptionType type,
                            BarrierFeature barrierFeature)
                            :Option(strike, maturity, type), barrier_(barrier), barrierFeature_(barrierFeature) {
                                payoff_ = new BarrierPayoff(strike, barrier, type, barrierFeature);
                            }

/* Only for Down and Out Call */
double BarrierOption::bsprice() {
    if (barrierFeature_ == DO && type_ == Call) {
        double nd1 = normcdf(getd1());
        double nd2 = normcdf(getd2());
        double nh1 = normcdf(geth1());
        double nh2 = normcdf(geth2());

        return s_ * exp(-div_ * t_) * nd1 - strike_ * exp(-r_ * t_) * nd2 \
            - pow(barrier_ / s_, 1 + 2 * r_ / (sigma_ * sigma_)) * s_ * nh1 \
            + pow(barrier_ / s_, -1 + 2 * r_ / (sigma_ * sigma_)) * strike_ * exp(-r_ * t_) * nh2;
    }
    else {
        return 0;
    }
}

double BarrierOption::bntprice(unsigned int steps, BinomialType bntType) {
    std::vector<double> tree = makeTree(steps, bntType);
    double prevSpot;                /* Spot price at previous period */

    for (int i = tree.size() - 1; i > 0; --i) {
        for (int j = 0; j < i; ++j) {
            prevSpot = s_ * pow(u_, i - j - 1) * pow(d_, j);
            switch(barrierFeature_) {
                case DO:
                    if (prevSpot <= barrier_) {
                        tree[j] = 0.0;
                        break;
                    }
                    else {
                        tree[j] = exp(-r_ * dt_) * (q_ * tree[j] + (1 - q_) * tree[j + 1]);
                        break;
                    }
                case DI:
                    if (prevSpot <= barrier_) {
                        tree[j] = exp(-r_ * dt_) * (q_ * tree[j] + (1 - q_) * tree[j + 1]);
                        break;
                    }
                    else {
                        tree[j] = 0.0;
                        break;
                    }
                case UO:
                    if (prevSpot >= barrier_) {
                        tree[j] = 0.0;
                        break;
                    }
                    else {
                        tree[j] = exp(-r_ * dt_) * (q_ * tree[j] + (1 - q_) * tree[j + 1]);
                        break;
                    }
                case UI:
                    if (prevSpot >= barrier_) {
                        tree[j] = exp(-r_ * dt_) * (q_ * tree[j] + (1 - q_) * tree[j + 1]);
                        break;
                    }
                    else {
                        tree[j] = 0.0;
                        break;
                    }
            }
        }
    }
    return tree[0];
}

double BarrierOption::geth1() const {
    return (log(barrier_ * barrier_ / (strike_ * s_)) + (r_ - div_ + 0.5 * sigma_ * sigma_) * t_) / (sigma_ * sqrt(t_));
}

double BarrierOption::geth2() const {
    return geth1() - sigma_ * sqrt(t_);
}
