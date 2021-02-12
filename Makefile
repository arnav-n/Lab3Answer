#CXX=clang++
CXX=g++

CXXFLAGS= -std=c++14 -Wall

BINARIES=dataProj testStates testSort1 testSort2 testSort3 testSort4

all: ${BINARIES}

tests: ${BINARIES}
	./testStates
	./testSort1
	./testSort2
	./testSort3
	./testSort4

dataProj: hospitalData.o rating.o dataAQ.o stateHosp.o stateDemog.o demogData.o parse.o main.o
	${CXX} $^ -o $@

testStates: rating.o stateHosp.o testStates.o dataAQ.o stateDemog.o demogData.o parse.o  tddFuncs.o
	${CXX} $^ -o $@

testSort1: rating.o stateHosp.o testSort1.o dataAQ.o stateDemog.o demogData.o parse.o  tddFuncs.o
	${CXX} $^ -o $@

testSort2: rating.o stateHosp.o testSort2.o dataAQ.o stateDemog.o demogData.o parse.o  tddFuncs.o
	${CXX} $^ -o $@

testSort3: rating.o stateHosp.o testSort3.o dataAQ.o stateDemog.o demogData.o parse.o  tddFuncs.o
	${CXX} $^ -o $@

testSort4: rating.o stateHosp.o testSort4.o dataAQ.o stateDemog.o demogData.o parse.o  tddFuncs.o
	${CXX} $^ -o $@

clean:
	/bin/rm -f ${BINARIES} *.o 
