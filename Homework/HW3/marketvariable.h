#ifndef _MARKETVARIABLE_H_
#define _MARKETVARIABLE_H_

class MarketVariable {
public:
    MarketVariable(double spot, double r, double dividend, double sigma)
        :spot_(spot), r_(r), div_(dividend), sigma_(sigma) {}
    ~MarketVariable() {}
    double getSpot() const { return spot_; }
    double getRate() const { return r_; }
    double getDiv() const { return div_; }
    double getVol() const { return sigma_; }
private:
    double spot_, r_, div_, sigma_;
};
#endif
