#ifndef _MARKETVARIABLE_H_
#define _MARKETVARIABLE_H_

class MarketVariable {
public:
    double getSpot() const;
    double getRate() const;
    double getDiv() const;
    double getVol() const;
private:
    double spot_, r_, div_, sigma_;
};
#endif
