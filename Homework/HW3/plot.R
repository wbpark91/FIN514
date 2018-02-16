setwd("/Users/wanbaep2/Desktop/FIN514/Homework/HW3")
error1 = read.csv("out1.csv") #CRR, RB ERROR
error2 = read.csv("out2.csv") #LR ERROR
error3 = read.csv("out3.csv") #CRR, RB Extrapolation
error4 = read.csv("out4.csv") #LR Extrapolation

par(mfrow = c(3, 1))
plot(error1$STEPS, error1$CRR, type = 'l', main = "Error of CRR method",
     xlab = "STEPS", ylab = "ERROR")
plot(error1$STEPS, error1$RB, type = 'l', main = "Error of RB method",
     xlab = "STEPS", ylab = "ERROR")
plot(error2$STEPS, error2$LR, type = 'l', main = "Error of LR mehod",
     xlab = "STEPS", ylab = "ERROR")

par(mfrow = c(3, 1))
plot(error3$N, error3$CRR, type = 'l', main = "Error of Extrapolation: CRR",
     xlab = "N", ylab = "ERROR")
plot(error3$N, error3$RB, type = 'l', main = "Error of Extrapolation: RB",
     xlab = "N", ylab = "ERROR")
plot(error4$N, error4$LR, type = 'l', main = "Error of Extrapolation: LR",
     xlab = "N", ylab = "ERROR")
