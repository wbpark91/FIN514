#ifndef _CONT_CPN_BUF_H_
#define _CONT_CPN_BUF_H_
#include "derivatives.h"
#include "payoff.h"
#include <vector>

class ContCpnBuf: public Derivative {
public:
    ContCpnBuf();
private:
    double mPrincipal;
    double mCoupon;
    double mBarrier;
    double mBuffer;

    std::vector<double> mCpnSchedule;
    bool mTrigger;
};

class ContCpnBufPayoff: public Payoff {
public:
    /* Constructors and Destructor */
    ContCpnBufPayoff();
    ContCpnBufPayoff(double spot, double barrier, double coupon,
                        double buffer);
    ~ContCpnBufPayoff();

    virtual double operator()(double s);
    void setTrigger(bool trigger);
private:
    double mSpot;
    double mBarrier;
    double mCoupon;
    double mBuffer;

    bool mTrigger;
};

#endif
