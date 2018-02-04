import numpy as np
import matplotlib.pyplot as plt

def payoff_call(spot, strike):
    return np.where(spot >= strike, spot - strike, 0)

def payoff_put(spot, strike):
    return np.where(spot <= strike, strike - spot, 0)

def payoff_digital_call(spot, strike):
    return np.where(spot >= strike, 1, 0)

def payoff_digital_put(spot, strike):
    return np.where(spot <= strike, 1, 0)

spot = np.arange(0, 300, 0.0001)
k1 = 120
k2 = 150

n1 = -8/float(120)
a1 = 4
a2 = 3.75
n2 = 1/float(15)

put1 = payoff_put(spot, k1)
digital_call1 = payoff_digital_call(spot, k1)
put2 = payoff_put(spot, k2)
put3 = payoff_put(spot, k1)
digital_call2 = payoff_digital_call(spot, k2)
bond = 6

port = n1 * put1 + a1 * digital_call1 + n2 * put2 - n2 * put1 + a2 * digital_call2 + bond

fig, ax = plt.subplots(figsize = (12, 8))
ax.plot(spot, port)
ax.set_xlim(0, 300)
ax.set_ylim(2, 20)
ax.axhline(10, color = 'k', linestyle = '--')
ax.axhline(12, color = 'k', linestyle = '--')
ax.axhline(13.75, color = 'k', linestyle = '--')
ax.axvline(120, color = 'k', linestyle = '--')
ax.axvline(206.25, color = 'k', linestyle = '--')
ax.set_xlabel("Spot Price")
ax.set_ylabel("Payoff")
fig.show()
