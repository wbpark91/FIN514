#include "barrier_payoff.h"
#include "u_math.h"

BarrierPayoff::BarrierPayoff(double strike, double barrier, optionType type, BarrierFeature barrierFeature)
    :strike_(strike), barrier_(barrier), type_(type), barrierFeature_(barrierFeature) {}

double BarrierPayoff::operator()(double spot) {
    switch(barrierFeature_) {
        case DO:
            if (spot <= barrier_)
                return 0.0;
            else
                return MAX(type_ * (s - strike_), 0.0);
        case DI:
            if (spot <= barrier_)
                return MAX(type_ * (s - strike_), 0.0);
            else
                return 0.0;
        case UO:
            if (spot >= barrier_)
                return 0.0;
            else
                return MAX(type_ * (s - strike_), 0.0);
        case UI:
            if (spot >= barrier_)
                return return MAX(type_ * (s - strike_), 0.0);
            else
                return 0.0;
    }
}
