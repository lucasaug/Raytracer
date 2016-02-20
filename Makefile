# Please don't actually read this file, this is a horror show

CPP_FILES := $(wildcard modules/*.cpp)
OBJ_FILES := $(addprefix bin/,$(notdir $(CPP_FILES:.cpp=.o)))

TEST_FILES := $(wildcard tests/*.cpp)
TOBJ_FILES := $(TEST_FILES:.cpp=.o)

CC_FLAGS := -std=c++11

raytracer: $(OBJ_FILES)
	g++ -o $@ main.cpp $^

bin/%.o: modules/%.cpp
	g++ $(CC_FLAGS) -c -o $@ $<

tests: test

test: raytracer testdep

testdep: $(TOBJ_FILES)
	g++ -o runTests $^ $(addprefix bin/,$(notdir $(wildcard bin/*.o)))

tests/%.o: tests/%.cpp
	g++ $(CC_FLAGS) -c -o $@ $<

clean:
	rm -f bin/*.o
	rm -f tests/*.o
	rm -f runTests
	rm -f raytracer
