// Purcaru Ioana Denisa 314CA
#include <stdio.h>
#include <stdlib.h>
void task1(int n, int **m, int *v) {
  int suma, count, i, j;
  char *p;
  for (i = 0; i < n; i++) {
    scanf("%d", &v[i]);
    m[i] = malloc(v[i] * sizeof(int));
    for (j = 0; j < v[i]; j++)
      scanf("%x", &m[i][j]);
  }
  suma = 0;
  count = 0;
  for (i = 0; i < n; i++) {
    if (i == 0) {
      for (j = 0; j < v[i]; j++) {
        p = (char *)&m[i][j];
        suma = suma + (int)*(p) + (int)*(p + 1) + (int)*(p + 2) + (int)*(p + 3);
      }
      count = count + 4 * v[i];
    } else if (i == n - 1) {
      for (j = 0; j < v[i]; j++) {
        p = (char *)&m[i][j];
        suma = suma + (int)*(p) + (int)*(p + 1) + (int)*(p + 2) + (int)*(p + 3);
      }
      count = count + 4 * v[i];
    } else {
      p = (char *)&m[i][0];
      suma = suma + (int)*(p);
      count = count + 2;
      if (v[i] != 1) {
        p = (char *)&m[i][v[i] - 1];
        suma = suma + (int)*(p + 3);
      } else {
        suma = suma + (int)*(p + 3);
      }
    }
  }
  long double m_a;
  m_a = (long double)suma / count;
  printf("task 1\n");
  printf("%.8Lf\n", m_a);
}

void modify(int **m, int *v) {
  int i, linie, pozitie, numar;
  char *p, dimensiune;
  short int *pointer;
  scanf(" %c", &dimensiune);
  if (dimensiune == 'S') {
    scanf(" %d", &linie);
    scanf("%d", &pozitie);
    scanf("%x", &numar);
    int w = pozitie / 2;
    int t = pozitie % 2;
    if (t == 1) {
      if (w < v[linie]) {
        *((short int *)&m[linie][w] + t - 1) = numar;
      } else {
        m[linie] = realloc(m[linie], (w + 1) * sizeof(int));
        for (i = w -1; i >= w - v[linie]; i--)
          m[linie][i] = 0;
        v[linie] = w + 1;
        pointer = (short int *)&m[linie][pozitie / 2];
        *(pointer) = numar;
      }
    } else {
      if (w - 1 < v[linie]) {
        pointer = (short int *)&m[linie][w - 1];
        *(pointer + 1) = numar;
      } else {
        m[linie] = realloc(m[linie], (w + 1) * sizeof(int));
        for (i = w - 1; i >= w - v[linie]; i--)
          m[linie][i] = 0;
        v[linie] = w;
        pointer = (short int *)&m[linie][w - 1];
        *(pointer + 1) = numar;
      }
    }
  }
  if (dimensiune == 'I') {
    scanf(" %d", &linie);
    scanf("%d", &pozitie);
    scanf("%x", &numar);
    if (pozitie < v[linie]) {
      m[linie][pozitie - 1] = numar;
    } else {
      m[linie] = realloc(m[linie], (pozitie) * sizeof(int));
      for (i = pozitie - 1; i >= v[linie]; i--)
        m[linie][i] = 0;
      v[linie] = pozitie;
      m[linie][pozitie - 1] = numar;
    }
  }
  if (dimensiune == 'C') {
    scanf(" %d", &linie);
    scanf("%d", &pozitie);
    scanf("%x", &numar);
    int t = pozitie % 4;
    int w = pozitie / 4;
    if (t != 0) {
      if (w < v[linie]) {
        p = (char *)&m[linie][w];
        *(p + (t) - 1) = numar;
      } else {
        m[linie] = realloc(m[linie], (w + 1) * sizeof(int));
        for (i = w - 1; i >= w; i--)
          m[linie][i] = 0;
        v[linie] = w + 1;
        p = (char *)&m[linie][w];
        *(p + (t) - 1) = numar;
      }
    } else {
      if (v[linie] > w - 1) {
        p = (char *)&m[linie][w - 1];
        *(p + 3) = numar;
      } else {
        m[linie] = realloc(m[linie], (w + 1) * sizeof(int));
        for (i = w - 1; i >= w - v[linie]; i--)
          m[linie][i] = 0;
        p = (char *)&m[linie][w - 1];
        *(p + 3) = numar;
      }
    }
  }
}
void task2(int n, int *v, int **m) {
  int k, i, j, var1, var2, linie, pozitie, b;
  char *p, operatie, dimensiune;
  scanf("%d", &k);
  short int *pointer;
  for (b = k; b > 0; b--) {
    scanf(" %c", &operatie);
    if (operatie == 'D') {
      scanf(" %c", &dimensiune);
      if (dimensiune == 'C') {
        scanf("%d %d", &linie, &pozitie);
        if (pozitie % 4 == 0) {
          p = (char *)&m[linie][(pozitie - 1) / 4];
          *(p + 3) = 0;
        } else {
          p = (char *)&m[linie][pozitie / 4];
          *(p + (pozitie % 4) - 1) = 0;
        }
      }
      if (dimensiune == 'I') {
        scanf("%d %d", &linie, &pozitie);
        m[linie][pozitie - 1] = 0;
      }
      if (dimensiune == 'S') {
        scanf("%d %d", &linie, &pozitie);
        if (pozitie % 2 != 0) {
          pointer = (short int *)&m[linie][pozitie / 2];
          *(pointer + (pozitie % 2) - 1) = 0;
        } else {
          pointer = (short int *)&m[linie][(pozitie - 1) / 2];
          *(pointer + 1) = 0;
        }
      }
    }
    if (operatie == 'S') {
      scanf(" %c", &dimensiune);
      scanf("%d ", &linie);
      scanf("%d", &pozitie);
      if ('I' == dimensiune) {
        p = (char *)&m[linie][pozitie];
        var1 = *p;
        int i = 1;
        *p = *(p + i + 2);
        var2 = *(p + i);
        *(p + i) = *(p + i + 1);
        *(p + i + 1) = var2;
        *(p + i + 2) = var1;
      }
      if (dimensiune == 'S') {
        if (pozitie % 2 !=1) {
          int i = -2;
          pointer = (short int *)m[linie];
          p = (char *)&pointer[pozitie + 1];
          var1 = *(p + i);
          *(p + i) = *(p + i + 1);
          *(p + i + 1) = var1;
        }
        }
      if (dimensiune == 'S') {
        if (pozitie %2 ==1) {
          int i = 2;
          pointer = (short int *)m[linie];
          p = (char *)&pointer[pozitie - 1];
          var1 = *(p + i);
          *(p + i) = *(p + i + 1);
          *(p + i + 1) = var1;
        }
      }
      }
    if (operatie == 'M') {
      modify(m, v);
    }
  }
  printf("task 2\n");
  for (i = 0; i < n; i++) {
    for (j = 0; j < v[i]; j++)
      printf("%.8X ", m[i][j]);
    printf("\n");
  }
}
int main() {
  int n, i;
  scanf("%d", &n);
  int *v;
  int **m;
  m = malloc(n * sizeof(int *));
  v = malloc(n * sizeof(int));
  task1(n, m, v);
  task2(n, v, m);
  printf("task 3\n");
  for (i = 0; i < n; i++)
    free(m[i]);
  free(m);
  free(v);
  return 0;
}
