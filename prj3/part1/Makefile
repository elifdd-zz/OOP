Compile_This=g++ -g -pthread

all: part1


part1: test.o 
	$(Compile_This) test.o -o part1


test.o: test.cpp Sptr.cpp Sptr.hpp
	$(Compile_This)  -c  test.cpp

clean:
	rm -f *.o *~ core part1

