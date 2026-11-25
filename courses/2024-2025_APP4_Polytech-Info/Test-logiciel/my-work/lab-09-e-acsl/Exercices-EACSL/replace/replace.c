/* @ requires length > 0;
  @ requires 0 <= ind < length;
  @ ensures tab[ind] == val;
  @ ensures \result == \old(tab[ind]);
  @*/

int replace(int *tab, int length, int ind, int val) {
  // @ assert \valid(tab[ind]);
  int temp = tab[ind];
  tab[ind] = val;
  return temp;
}

int tab[3] = {5,1,2};

void test1() {
  int res = replace(tab,3,0,4);
  assert(res == 5);
  assert(tab[0] == 4);
}

void test2() {
  int res = replace(tab,5,2,0);
  assert(res == 2);
  assert(tab[2] == 0);
}

void test3() {
  int res = replace(tab,1,2,4);
  assert(res == 2);
  assert(tab[2] == 4);
}

int main() {
  test1();
  test2();
  test3();
}
