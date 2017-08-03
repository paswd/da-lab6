FLAGS=-pedantic -Wall -Werror -Wno-sign-compare -Wno-long-long -lm -std=c++11 -O2
COMPILLER=g++

all: start

start: converter.o calc.o main.o
	$(COMPILLER) $(FLAGS) -o da-lab6 converter.o calc.o main.o

main.o: main.cpp
	@$(COMPILLER) -c $(FLAGS) main.cpp

converter.o: converter.cpp
	$(COMPILLER) -c $(FLAGS) converter.cpp

calc.o: calc.cpp
	$(COMPILLER) -c $(FLAGS) calc.cpp

clean:
	@-rm -f *.o *.gch *.dat da-lab6
	@echo "Clean success"
