CXX=		g++
CXXFLAGS=	-g -Wall -std=gnu++11
SHELL=		bash
MEASURE=	../common/measure

all:		main strTree.o 

main:	main.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

strTree.o:	strTree.h
	$(CXX) -c -o $@ $^

clean:
	rm -f solution bTree.o
	rm -rf solution.dSYM

test:		test-time

test-time:	$(MEASURE) ain
	@echo Testing time...
	@$(MEASURE) ./main < input | tail -n 1 | awk '{ if ($$1 > 1.0) { print "Time limit exceeded"; exit 1} }'
