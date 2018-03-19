#Makefile

#UGL Coding
#BASE = /Users/wanbaep2/Desktop
LOC = $(BASE)/Derivatives
EFILE = $(BASE)/FIN514/Homework/HW3/Result

#Home Coding
BASE = /Users/park-wanbae/Desktop
LOC = $(BASE)/MFE/2018-1/Derivatives
OPTION = $(LOC)/option
ETC = $(LOC)/etc
OBJS = derivatives.o *option.o *payoff.o normal.o u_math.o
INCLS = -I$(ETC) -I$(OPTION)
CFLAGS = -std=c++11 -o
#EFILE = $(BASE)/MFE/2018-1/FIN514/Homework/HW3/Result

all: problem1 problem2 problem3 problem4
derivative:
	g++ $(INCLS) -c $(OPTION)/derivatives.cpp

option:
	g++ $(INCLS) -c $(OPTION)/*option.cpp

payoff:
	g++ $(INCLS) -c $(OPTION)/*payoff.cpp

etc:
	g++ $(INCLS) -c $(ETC)/normal.cpp $(ETC)/u_math.cpp

problem1: derivative option payoff etc
	g++ $(INCLS) $(CFLAGS) problem1 problem1.cpp $(OBJS)

problem2: derivative option payoff etc
	g++ $(INCLS) $(CFLAGS) problem2 problem2.cpp $(OBJS)

problem3: derivative option payoff etc
	g++ $(INCLS) $(CFLAGS) problem3 problem3.cpp $(OBJS)

problem4: derivative option payoff etc
	g++ $(INCLS) $(CFLAGS) problem4 problem4.cpp $(OBJS)

clear:
	rm -f derivatives.o
	rm -f *option.o
	rm -f *payoff.o
	rm -f normal.o
	rm -f u_math.o
