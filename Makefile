LINK_FLAGS = -lSDL2
FILES := $(shell find *.cpp)

#Compile cpp
# a:
# 	g++ -o build/a.out $(LINK_FLAGS) $(FILES)

main:
	g++ -o build/a.out $(LINK_FLAGS) main.cpp

run:
	./build/a.out
