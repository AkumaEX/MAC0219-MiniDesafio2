main:
	@gcc -fopenmp main.c -o main

clean:
	@rm -rf *.o main

run: main
	@./main
	@rm -rf *.o main