all: parse_args.o shell.o
	gcc -o shell shell.o parse_args.o

shell.o: shell.c parse_args.c
	gcc -c shell.c

parse_args.o: parse_args.c
	gcc -c parse_args.c

run:
	./shell
