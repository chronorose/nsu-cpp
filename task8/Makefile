CC := zig c++
CCFLAGS := -std=c++23 -Wall -lasan -fsanitize=leak -fsanitize=address -fsanitize=undefined

SRC := $(shell find src/ -name '*.cpp')
EXE := ./build/exec

test:
	make -C build/
	make test -C build/

run: cmp
	$(EXE)

clean:
	rm $(EXE)

build/:
	@mkdir build/

cmp: build/
	@$(CC) $(CCFLAGS) $(SRC) -o $(EXE)
