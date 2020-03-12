LINK_FLAGS = -lSDL2
TEST_FLAGS = -lSDL2
FILES := $(shell ls *.cpp)

#Compile cpp
# a:
# 	g++ -o build/a.out $(LINK_FLAGS) $(FILES)

default:
	g++ -o build/a.out $(LINK_FLAGS) main.cpp

t:
	g++ -o build/test.out $(TEST_FLAGS) test.cpp

run:
	./build/a.out

trun:
	./build/test.out
