test:
	make -C build/
	make test -C build/

run: cmp
	./a.out
	rm a.out

cmp: 
	clang++ -std=c++23 -fsanitize=leak -fsanitize=address main.cpp -o a.out
