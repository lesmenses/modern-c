/* This may look like nonsense, but really is -*- mode: C -*- */
#include <stdio.h> // needed to add the library for printf.

/* The main thing that this program does. */
int main() { // needed to have int return type for main.
  // Declarations
  int i;
  double A[5] = {
    9.0,
    2.9,
    3.E+25,
    .00007,
  };

  // Doing some work
  for (i = 0; i < 5; ++i) {
     printf("element %d is %g, \tits square is %g\n", /*@\label{printf-start-badly}*/
            i,
            A[i],
            A[i]*A[i]);                               /*@\label{printf-end-badly}*/
  }

  return 0;                                           /*@\label{main-return-badly}*/
}
