LINK_FLAGS = -lSDL2
FILES := $(shell find ./ -name *.cpp)

#Compile cpp
%.o:%.cpp
	g++ -o build/a.out $(LINK_FLAGS) $@ $(FILES)
run:
	./build/a.out
