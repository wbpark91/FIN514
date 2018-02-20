#Makefile

BASE = /Users/park-wanbae/Desktop
LOC = $(BASE)/MFE/2018-1/FIN514/Code
OBJS = *option.o *payoff.o normal.o u_math.o
INCLS = -I$(LOC)
CFLAGS = -std=c++11 -o
EFILE = $(BASE)/MFE/2018-1/FIN514/Homework/HW3/Result

all: problem1 problem2 problem3 problem4

option:
	g++ $(INCLS) -c $(LOC)/*option.cpp

payoff:
	g++ $(INCLS) -c $(LOC)/*payoff.cpp

etc:
	g++ $(INCLS) -c $(LOC)/normal.cpp $(LOC)/u_math.cpp

problem1: option payoff etc
	g++ $(INCLS) $(CFLAGS) problem1 problem1.cpp $(OBJS)

problem2: option payoff etc
	g++ $(INCLS) $(CFLAGS) problem2 problem2.cpp $(OBJS)

problem3: option payoff etc
	g++ $(INCLS) $(CFLAGS) problem3 problem3.cpp $(OBJS)

problem4: option payoff etc
	g++ $(INCLS) $(CFLAGS) problem4 problem4.cpp $(OBJS)

clear:
	rm -f *option.o
	rm -f *payoff.o
	rm -f normal.o
	rm -f u_math.o
