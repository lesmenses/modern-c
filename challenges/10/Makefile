CC = clang

STD = -std=gnu17

SORT_FILES_LOCATION = ../1

double : timing_double.o sort_double.o
		${CC} -o timing_double timing_double.o sort_double.o

timing_double.o : timing_double.c ${SORT_FILES_LOCATION}/sort_double.h
		${CC} -c timing_double.c

sort_double.o : ${SORT_FILES_LOCATION}/sort_double.c ${SORT_FILES_LOCATION}/sort_double.h
		${CC} -c ${SORT_FILES_LOCATION}/sort_double.c -D "INCLUDE"

clean :
	rm ./*.o timing_double