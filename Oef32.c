#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
        double meetwaarde;
        unsigned long long int timestamp;
} meting;

double randomDouble();
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

  m1p->meetwaarde = randomDouble();
  m1p->timestamp = time(NULL);

  m2p->meetwaarde = randomDouble();
  m2p->timestamp = time(NULL);

  printInfo(m1p);
  printInfo(m2p);

  return 0;
}

double randomDouble() {
  double x = (double)rand()/(double)(RAND_MAX/5);
  return x;
}

void printInfo(meting *x) {
  printf("%f\n", x->meetwaarde);
  printf("%d\n", x->timestamp);
}
