#Makefile

#UGL Coding
#BASE = /Users/wanbaep2/Desktop
#LOC = $(BASE)/Derivatives
#EFILE = $(BASE)/FIN514/Homework/HW3/Result

#Home Coding
BASE = /Users/park-wanbae/Desktop
LOC = $(BASE)/MFE/2018-1/Derivatives
OPTION = $(LOC)/multiasset
ETC = $(LOC)/etc
OBJS = multiasset_derivative.o multiasset_autocall.o autocall_yieldnote_least_perform.o	\
	*payoff.o normal.o u_math.o matrix.o marketvariable.o
INCLS = -I$(ETC) -I$(OPTION)
CFLAGS = -std=c++11 -o
#EFILE = $(BASE)/MFE/2018-1/FIN514/Homework/HW3/Result

all: main
derivative:
	g++ $(INCLS) -std=c++11 -c $(OPTION)/multiasset_derivative.cpp

option:
	g++ $(INCLS) -std=c++11 -c $(OPTION)/multiasset_autocall.cpp $(OPTION)/autocall_yieldnote_least_perform.cpp

payoff:
	g++ $(INCLS) -std=c++11 -c $(OPTION)/*payoff.cpp

etc:
	g++ $(INCLS) -std=c++11 -c $(ETC)/normal.cpp $(ETC)/u_math.cpp $(ETC)/matrix.cpp $(ETC)/marketvariable.cpp

main: etc derivative payoff option
	g++ $(INCLS) $(CFLAGS) main main.cpp $(OBJS)

clear:
	rm -f multiasset_derivative.o
	rm -f multiasset_autocall.o
	rm -f autocall_yieldnote_least_perform.o
	rm -f *payoff.o
	rm -f normal.o
	rm -f u_math.o
	rm -f matrix.o
	rm -f marketvariable.o
