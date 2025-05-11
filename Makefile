CXX = g++ 
CXX_FLAGS = -std=c++23 -Wall -Wextra -g

SOURCE = $(shell find source -name '*.cpp')
objects = $(patsubst source/%.cpp, build/%.o, $(SOURCE))
exe = run
BUILD = build

all: $(exe)

clean: 	
	rm -rf $(exe) $(BUILD)
	clear

$(exe): $(objects)
	$(CXX) $(CXX_FLAGS) $(objects) -o $(exe)

build/%.o: source/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXX_FLAGS) -c $< -o $@
