#include "straddle.h"
#include "u_math.h"

StraddlePayoff::StraddlePayoff(double strike): strike_(strike) {}

double StraddlePayoff::operator()(double s) {
    return MAX(s - strike_, 0) + MAX(strike_ - s , 0);
}

Straddle::Straddle(double strike): strike_(strike), Derivative(maturity) {
    call_ = new PlainVanillaOption(strike, maturity, Call);
    put_ = new PlainVanillaOption(strike, maturity, Put);
}

Straddle::~Straddle() {
    delete call_;
    delete put_;
}

void Straddle::setMarketVariable(MarketVariable mktVar) {
    mktVar_ = mktVar;
    s_ = mktVar.getSpot();
    r_ = mktVar.getRate();
    div_ = mktVar.getDiv();
    sigma_ = mktVar.getVol();

    /* Set marketvariable to each option */
    call_ -> setMarketVariable(mktVar);
    put_ -> setMarketVariable(mktVar);
}

double Straddle::bsprice() {
    return call_ -> bsprice() + put_ -> bsprice();
}

double Straddle::delta() {
    return call_ -> delta() + put -> delta();
}
