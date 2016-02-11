CPP_FILES := $(wildcard modules/*.cpp)
OBJ_FILES := $(addprefix bin/,$(notdir $(CPP_FILES:.cpp=.o)))

TOBJ_FILES := $(addprefix bin/,$(notdir $(wildcard bin/*.o)))

CC_FLAGS := -g

raytracer: $(OBJ_FILES)
	g++ -o $@ main.cpp $^

bin/%.o: modules/%.cpp
	g++ $(CC_FLAGS) -c -o $@ $<

test: raytracer
	g++ -c -o tests/headers.o tests/headers.cpp
	g++ -c -o tests/vectors.o tests/vectors.cpp
	g++ -o runTests tests/headers.o tests/vectors.o $(TOBJ_FILES)

clean:
	rm -f bin/*.o
	rm -f tests/*.o
	rm -f runTests
	rm -f raytracer
