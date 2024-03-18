CC := g++ -fsanitize=address
rm := rm -f
build := build/

%:
	$(CC) task$@/*.cpp -o $(build)task$@ -fsanitize=address
	./$(build)task$@
