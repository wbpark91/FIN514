#------------------------------------------------------------------------------
## PROBLEM 1
setwd("/Users/wanbaep2/Desktop/FIN514/Homework/HW3/Q1")
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

#------------------------------------------------------------------------------
## PROBLEM 2
setwd("/Users/wanbaep2/Desktop/FIN514/Homework/HW3/Q2")
error5 = read.csv("out1.csv") #CRR, BD ERROR
error6 = read.csv("out2.csv") #LR ERROR
bound = read.csv("out3.csv") #Exercise bound of option
error7 = read.csv("out4.csv") #Error of Extrapolation: CRR, BD
error8 = read.csv("out5.csv") #Error of Extrapolation: LR

par(mfrow = c(3, 1))
plot(error5$STEP, error5$CRR, type = 'l', main = "Error of CRR method",
     xlab = "STEPS", ylab = "ERROR")
plot(error5$STEP, error5$BD, type = 'l', main = "Error of BD method",
     xlab = "STEPS", ylab = "ERROR")
plot(error6$STEP, error6$LR, type = 'l', main = "Error of LR method",
     xlab = "STEPS", ylab = "ERROR")

par(mfrow = c(1, 1))
plot(bound$STEP, bound$Boundary, type = 'l', main = "Exercise boundary",
     xlab = "STEPS", ylab = "Boundary")

par(mfrow = c(3, 1))
plot(error7$N, error7$CRR, type = 'l', main = "Error of Extrapolation: CRR",
     xlab = "N", ylab = "ERROR")
plot(error7$N, error7$BD, type = 'l', main = "Error of Extrapolation: BD",
     xlab = "N", ylab = "ERROR")
plot(error8$N, error8$LR2, type = 'l', main = "Error of Extrapolation: LR",
     xlab = "N", ylab = "ERROR", ylim = c(-0.001, 0.003), col = 'red')
lines(error8$N, error8$LR1, col="green")
abline(h = 0)

#------------------------------------------------------------------------------
## PROBLEM 2
setwd("/Users/wanbaep2/Desktop/FIN514/Homework/HW3/Q3")
error9 = read.csv("out.csv") #Error of CRR: continuous barrier option

par(mfrow = c(1, 1))
plot(error9$STEPS, error9$ERROR, type = 'l', main = "Error of CRR method",
     xlab = "STEPS", ylab = "ERROR", col = 'red')
par(new = T)
with(error9, plot(error9$STEPS, error9$LAMBDA, pch=16, axes=F, xlab=NA, ylab=NA, cex=0.3), col = 'red')
axis(side = 4)
mtext(side = 4, line = 0.5, expression(Lambda))
legend("topright",
       legend=c("Error", expression(Lambda)),
       lty=c(1,0), pch=c(NA, 16), col=c("red", "black"))
