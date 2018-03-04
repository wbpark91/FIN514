setwd("/Users/park-wanbae/Desktop/MFE/2018-1/FIN514/Project/P1")
data = read.csv("vol_div.csv")
plot(data$X...vol, data$price, type = 'l', main = "Price with respect to Volatility",
     xlab = "Volatility", ylab = "Price")

div = read.csv("div_price.csv")
plot(div$X...div, div$price, type = 'l', main = "Price with respect to Dividend",
     xlab = "Dividend Yield", ylab = "Price")
