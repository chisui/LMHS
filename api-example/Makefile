SAT = lingeling
MIP = cplex
LIBDIR = ../lib # location of libLMHS-$(SAT)-$(MIP).so
SRCDIR = ../src # location of LMHS_C_API.h
c:
	gcc -I$(SRCDIR) example.c -L$(LIBDIR) -lLMHS-$(SAT)-$(MIP) -Wl,-rpath,$(LIBDIR) -o c-example
ipasir:
	gcc -I$(SRCDIR) ipasir_test.c -L$(LIBDIR) -lLMHS-$(SAT)-$(MIP) -Wl,-rpath,$(LIBDIR) -o ipasir-example
cpp:
	g++ -std=c++11 -I$(SRCDIR) example.cpp -L$(LIBDIR) -lLMHS-$(SAT)-$(MIP) -Wl,-rpath,$(LIBDIR) -o cpp-example