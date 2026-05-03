all: color-code-trainer.o
	g++ -Wall -std=c++11 -o color-code-trainer color-code-trainer.o

color-code-trainer.o: color-code-trainer.cpp
	g++ -Wall -std=c++11 -c color-code-trainer.cpp

clean:
	rm -f *.o color-code-trainer

