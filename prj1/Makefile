PROJECT = prj1
SRC_FILES = \
        Animals.cpp \
        List_AnimalPtr.cpp \
        test_correctness.cpp \
	test_speed.cpp \
	DynamicArray.hpp \
	Animals.hpp \
	List_AnimalPtr.hpp \
        Makefile \
	README
all: test speed

test:
	g++ -g Animals.cpp List_AnimalPtr.cpp test_correctness.cpp -o test

speed:
	g++ -g Animals.cpp List_AnimalPtr.cpp test_speed.cpp -o speed

#Removes all objects and executables.
clean:
	rm -f  *.out *.o  core *.core *~ test speed

#This target makes a archive containing all the project source files,
#suitable for submission.
submit: $(SRC_FILES)
	tar cvfz $(PROJECT).tar.gz $(SRC_FILES)

