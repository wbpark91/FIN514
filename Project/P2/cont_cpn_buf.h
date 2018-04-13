#ifndef _CONT_CPN_BUF_H_
#define _CONT_CPN_BUF_H_
#include "derivatives.h"
#include "payoff.h"
#include "forex.h"
#include <vector>

enum CpnFreq { Month = 12, Quarter = 4, SemiAnnual = 2, Annual = 1 };

class ContCpnBuf: public Derivative {
public:
    /* Constructors and Destructor */
    ContCpnBuf();
    ContCpnBuf(double principal, double maturity, double barrier,
            double buffer, CpnFreq freq);
    ~ContCpnBuf();

    /* set functions */
    void setTrigger(bool trigger);
    void setForex(Forex forex);

    /* pricing functions */
    virtual double bntprice(unsigned int steps, BinomialType bntType);
    double fdmprice(unsigned int imax, unsigned int jmax, FDMType fdmType);
private:
    double mPrincipal;
    double mCoupon;
    double mBarrier;
    double mBuffer;

    std::vector<double> mCpnSchedule;
    CpnFreq mFreq;
    bool mTrigger;

    /* correlation */
    double mCorr;

    /* Foreign exchange rate*/
    Forex mForex;
};

class ContCpnBufPayoff: public Payoff {
public:
    /* Constructors and Destructor */
    ContCpnBufPayoff();
    ContCpnBufPayoff(double principal, double barrier,
        double coupon, double buffer, CpnFreq freq);
    ~ContCpnBufPayoff();

    virtual double operator()(double s);

    /* set functions */
    void setTrigger(bool trigger);
    void setSpot(double spot);
private:
    double mSpot;
    double mPrincipal;
    double mBarrier;
    double mCoupon;
    double mBuffer;

    CpnFreq mFreq;

    bool mTrigger;
};

#endif
