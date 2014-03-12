Compile_This=g++ -g

all: part4


part4: test.o 
	$(Compile_This) test.o -o part4


test.o: test.cpp CachingNew.cpp CachingNew.hpp
	$(Compile_This)  -c  test.cpp

clean:
	rm -f *.o *~ core part4

