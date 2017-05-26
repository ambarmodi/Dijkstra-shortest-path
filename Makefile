all: project

project: Q2_dijikstra.out

Q2_dijikstra.out: Q2_dijikstra.c
	gcc -g Q2_dijikstra.c -o Q2_dijikstra.out

clean:
	find . -type f -name "*.o" -delete
	find . -type f -executable -delete
