Compile_This=g++ -g

all: part2


part2: test.o 
	$(Compile_This) test.o -o part2


test.o: test.cpp List.cpp List.hpp
	$(Compile_This)  -c  test.cpp

clean:
	rm -f *.o *~ core part2

