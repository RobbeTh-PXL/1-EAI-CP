#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
        double meetwaarde;
        unsigned long long int timestamp;
} meting;

void printInfo(meting *x);

int main(void) {
  // Intializes random number generator by seeding it with the current time
  srand((unsigned int)time(NULL));

  meting m1;
  meting *m1p;
  m1p = &m1;

  meting m2;
  meting *m2p;
  m2p = &m2;

  m1p->meetwaarde = (double)rand()/(double)(RAND_MAX/5);
  m1p->timestamp = time(NULL);

  m2p->meetwaarde = (double)rand()/(double)(RAND_MAX/5);
  m2p->timestamp = time(NULL);

  printf("Meting m1:\n");
  printInfo(m1p);
  printf("\nMeting m2:\n");
  printInfo(m2p);

  return 0;
}

void printInfo(meting *x) {
  printf("De gemete waarde: %f\n", x->meetwaarde);
  printf("Het tijdstip waarop gemeten is: %I64d\n", x->timestamp);
}
