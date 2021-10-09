project1: main.o
	${CXX} $(CXXFLAGS) -o $@ $+

main.o: main.cpp hashtable.h
	${CXX} $(CXXFLAGS) -c -o $@ $<