#include "option.h"

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
