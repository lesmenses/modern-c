CC = clang

OPTIONS = -std=gnu17 -Wall

ORIGIN = /home/lesmenses/modern-c

UNION_FILES_LOCATION = ${ORIGIN}/challenges/4

segment : segment.o union_find.o
		${CC} ${OPTIONS} -o segment segment.o union_find.o -L ${ORIGIN}/lib -lpng

debug : segment.o union_find.o
		${CC} ${OPTIONS} -g -o segment segment.o union_find.o -L ${ORIGIN}/lib -lpng

segment.o : segment.c ${UNION_FILES_LOCATION}/union_find.h ${ORIGIN}/include/png.h
		${CC} ${OPTIONS} -c segment.c -g

union_find.o : ${UNION_FILES_LOCATION}/union_find.c ${UNION_FILES_LOCATION}/union_find.h
		${CC} ${OPTIONS} -c ${UNION_FILES_LOCATION}/union_find.c -D "INCLUDE" -g

clean:
	rm ./*.o segment