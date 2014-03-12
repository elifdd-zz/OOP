Compile_This=g++ -g

all: part3


part3: test.o 
	$(Compile_This) test.o -o part3


test.o: test.cpp Array.cpp Array.hpp
	$(Compile_This)  -c  test.cpp

clean:
	rm -f *.o *~ core part3


