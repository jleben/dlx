#include <stdio.h>
#include <stdlib.h>

#define REP(i, n) for(int i=0; i<n; i++)
#define NE(m, i, n, j) if (get(m, i, n) == j) return 0;

int main() {
  char *s[3][6] = { { "Bob", "Chuck",  "Dave", "Ed", "Frank", "Gary"},
                    { "Hall", "King", "Noyes", "Pinza", "Veery", "White"},
                    { "AL", "AR", "AS", "ML", "MR", "MS" } };
  int a[6][2], p[6], q[6];
  REP(i, 6) p[i] = q[i] = i;
  void x(int *i, int *j) {
    int t = *i;
    *i = *j, *j = t;
  }
  int get(int m, int i, int n) {
    REP(k, 6) if ((m ? a[k][m-1] : k) == i) return a[k][n-1];
    fprintf(stderr, "BUG!\n"), exit(1);
  }
  int g() {
    // 1. Every order was different.
    //
    // 2. Bob, King, and a man who ordered ravioli...
    //    Chuck, Hall, and a man who ordered spaghetti...
    if (get(0, 0, 2)/3 != get(1, 1, 2)/3) return 0;
    if (get(0, 1, 2)/3 != get(1, 0, 2)/3) return 0;
    NE(0, 0, 1, 0);
    NE(0, 0, 1, 1);
    NE(0, 0, 2, 1);
    NE(0, 0, 2, 4);
    NE(1, 1, 2, 1);
    NE(1, 1, 2, 4);

    NE(0, 1, 1, 0);
    NE(0, 1, 1, 1);
    NE(0, 1, 2, 2);
    NE(0, 1, 2, 5);
    NE(1, 0, 2, 2);
    NE(1, 0, 2, 5);

    // 3. Gary and White both ordered lasagna; Hall did not.
    NE(0, 5, 1, 5);

    NE(0, 5, 2, 1);
    NE(0, 5, 2, 2);
    NE(0, 5, 2, 4);
    NE(0, 5, 2, 5);

    NE(1, 5, 2, 1);
    NE(1, 5, 2, 2);
    NE(1, 5, 2, 4);
    NE(1, 5, 2, 5);

    NE(0, 5, 1, 0);

    NE(1, 0, 2, 0);
    NE(1, 0, 2, 3);

    // 4. Frank didn't order minestrone; neither he nor Pinza ordered ravioli.
    NE(0, 4, 2, 3);
    NE(0, 4, 2, 5);

    NE(0, 4, 2, 1);
    NE(0, 4, 2, 4);

    NE(1, 3, 2, 1);
    NE(1, 3, 2, 4);

    NE(0, 4, 1, 3);

    // 5. Neither Ed nor Frank are Veery.
    NE(0, 3, 1, 4);
    NE(0, 4, 1, 4);
    return 1;
  }
  void f(int m, int n) {
    if (!m) {
      if (!n && g()) {
        REP(k, 6) printf("%s, %s, %s\n", s[0][k], s[1][a[k][0]], s[2][a[k][1]]);
        return;
      }
      REP(k, n) {
        a[n-1][1] = q[k];
        x(q+k, q+n-1);
        f(m, n-1);
        x(q+k, q+n-1);
      }
      return;
    }
    REP(k, m) {
      a[m-1][0] = p[k];
      x(p+k, p+m-1);
      f(m-1, n);
      x(p+k, p+m-1);
    }
  }
  f(6, 6);
  return 0;
}