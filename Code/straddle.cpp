#include "straddle.h"
#include "u_math.h"
#include <random>

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

/* Calculate expected payoff using dynamic replication */
/* Need to moved into derivative class */
double Straddle::hedgeSimulation(unsigned int numPath, unsigned int steps) {
    /* Payoffs */
    std::vector<double> payoffStream;

    /* Random Number Generator */
    std::mt19937_64 gen;
    std::normal_distribution<double> engine(0.0, 1.0);
    gen.seed(std::random_device{}());

    /* Initialize parameters */
    double dt = t_ / steps;
    double diffusion = sigma_ * sqrt(dt);
    double expret = exp((r_ - 0.5 * sigma_ * sigma_) * dt   /* Expected Return */

    for (int i = 0; i < numPath; ++i) {
        /* Initialize Spot, Delta, Cash Stream */
        std::vector<double> spotStream = {s_};
        std::vector<double> deltaStream = {this -> delta()};
        std::vector<double> cashStream = {this -> bsprice() - s_ * delta()};

        /* at each path */
        /* Might be better to separate from the whole function */
        for (int j = 1; j <= steps; ++j) {
            /* Create random number */
            double e = engine(gen);

            /* new stock price */
            double s = spotStream[j-1] * expret + diffusion * e);

            if (j != steps) {
                /* change spot and maturity for getting delta */
                call_ -> setSpot(s);
                call_ -> setMaturity(t_ - j * dt);
                put_ -> setSpot(s);
                put_ -> setMaturity(t_ - j * dt);

                /* new delta */
                double delta = call_ -> delta() + put_ -> delta();

                /* new cash */
                double cash = cashStream[j-1] * exp(r_ * dt) + s * (deltaStream[j-1] - delta);

                /* update stream */
                spotStream.push_back(s);
                deltaStream.push_back(delta);
                cashStream.push_back(cash);
            }
            else {
                double payoff = delta[j-1] * s + cash * exp(r_ * dt);
                payoffStream.push_back(payoff);
            }
        }
    }
    /* Need to calculate average, standard deviation */
}
