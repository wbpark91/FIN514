#include "cont_cpn_buf.h"

/* Security functions */
ContCpnBuf::ContCpnBuf() { }

ContCpnBuf::ContCpnBuf(double principal, double coupon, double maturity,
    double barrier, double buffer, CpnFreq freq)
        :mPrincipal(principal), mCoupon(coupon), Derivative(maturity),
        mBarrier(barrier), mBuffer(buffer), CpnFreq(freq) {
        /* initialize payoff */
        payoff_.reset( new ContCpnBufPayoff(principal, barrier, coupon,
            buffer, freq) );

        /* trigger = 0 at initialized time */
        mTrigger = false;
}

ContCpnBuf::~ContCpnBuf() { }

/* set functions */
void ContCpnBuf::setTrigger(bool trigger) {
    mTrigger = trigger;
    payoff_ -> setTrigger(trigger);
}

void ContCpnBuf::setForex(Forex forex) {
    mForex = forex;
}

void ContCpnBuf::setCorr(double corr) {
    mCorr = corr;
}

void ContCpnBuf::setMarketVariable(MarketVariable mktVar) {
    Derivative::setMarketVariable(mktVar);
    payoff_ -> setSpot(mktVar.getSpot());
}


/* Payoff functions */
ContCpnBufPayoff::ContCpnBufPayoff() { }

ContCpnBufPayoff::ContCpnBufPayoff(double principal,
    double barrier, double coupon, double buffer, CpnFreq freq)
    : mPrincipal(principal), mBarrier(barrier), mCoupon(coupon),
        mBuffer(buffer), mFreq(freq) { mTrigger = false; }

ContCpnBufPayoff::~ContCpnBufPayoff() { }

void ContCpnBufPayoff::setTrigger(bool trigger) {
    mTrigger = trigger;
}

void ContCpnBufPayoff::setSpot(double spot) {
    mSpot = spot;
}

double ContCpnBufPayoff::operator()(double s) {
    if (s < mBarrier) {
        mTrigger = true;
    }

    /* If trigger is not hit */
    if (mTrigger == false) {
        double coupon = mPrincipal * mCoupon * (1.0 / mFreq);
        return mPrincipal + coupon;
    }
    /* If trigger is hit */
    else {
        double idxReturn = (s - mSpot) / mSpot;
        return mPrincipal + mPrincipal * (idxReturn + mBuffer);
    }
}
