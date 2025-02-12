CC := clang++ -std=c++23 -Wall -Wextra -fsanitize=leak -fsanitize=address -fsanitize=undefined
src := main.cpp treap.cpp

run: cmp
	./out

cmp:
	$(CC) $(src) -o out

test: setup
	cd builddir && meson test

compile: setup
	cd builddir && meson compile 
	
setup:
	meson setup --reconfigure builddir
