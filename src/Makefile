CC=gcc
CFLAGS=-Wall -Werror -Wextra -g -O0

s21_morphological_analysis.o:
	$(CC) $(CFLAGS) -c s21_morphological_analysis.c -o s21_morphological_analysis.o

s21_stack.o:
	$(CC) $(CFLAGS) -c s21_stack.c -o s21_stack.o

temp: clean s21_morphological_analysis.o s21_stack.o
	$(CC) $(CFLAGS) temp.c s21_morphological_analysis.o s21_stack.o -o temp

clean:
	rm -f temp *.o
