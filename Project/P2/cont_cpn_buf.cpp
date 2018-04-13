#include "cont_cpn_buf.h"

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
