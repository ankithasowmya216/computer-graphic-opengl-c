all:
	g++ bibutil.c -c
	g++ main.c -o main bibutil.o -lGL -lglut -lGLU