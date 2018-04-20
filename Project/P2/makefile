#Makefile

#UGL Coding
#BASE = /Users/wanbaep2/Desktop
#LOC = $(BASE)/Derivatives
#EFILE = $(BASE)/FIN514/Homework/HW3/Result

#Home Coding
BASE = /Users/park-wanbae/Desktop
LOC = $(BASE)/MFE/2018-1/Derivatives
OPTION = $(LOC)/option
FDM = $(LOC)/fdmengine
ETC = $(LOC)/etc
OBJS = derivatives.o normal.o u_math.o fdm_engine.o explicit_fdm.o mesh.o \
		explicit_fdm_contcpn.o cont_cpn_buf.o cn_fdm_contcpn.o
INCLS = -I$(ETC) -I$(OPTION) -I$(FDM)
CFLAGS = -std=c++11 -O3 -o
#EFILE = $(BASE)/MFE/2018-1/FIN514/Homework/HW3/Result

all: main
derivative:
	g++ $(INCLS) -c $(OPTION)/derivatives.cpp

fdm:
	g++ $(INCLS) -c $(FDM)/fdm_engine.cpp $(FDM)/explicit_fdm.cpp $(FDM)/mesh.cpp	\
		$(FDM)/explicit_fdm_contcpn.cpp $(FDM)/cn_fdm_contcpn.cpp

option:
	g++ $(INCLS) -c $(OPTION)/cont_cpn_buf.cpp

payoff:
	g++ $(INCLS) -c $(OPTION)/*payoff.cpp

etc:
	g++ $(INCLS) -c $(ETC)/normal.cpp $(ETC)/u_math.cpp

main: fdm derivative option etc
	g++ $(INCLS) $(CFLAGS) main main.cpp $(OBJS)

clear:
	rm -f derivatives.o
	rm -f *option.o
	rm -f *payoff.o
	rm -f normal.o
	rm -f u_math.o
	rm -f fdm_engine.o
	rm -f explicit_fdm.o
	rm -f mesh.o
	rm -f cont_cpn_buf.o
	rm -f explicit_fdm_contcpn.o
	rm -f cn_fdm_contcpn.o
