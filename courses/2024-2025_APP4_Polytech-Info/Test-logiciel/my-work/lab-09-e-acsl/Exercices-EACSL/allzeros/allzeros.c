
int all_zeros(int *tab, int length) {
  for(int i = 0; i < length; i++) {
    if(tab[i] != 0) {
      return 0;
    }
  }
  return 1;
}

int main(void) {
  int tab[5] = {0,0,0,0,0};
  int tab2[4] = {0,1,0,1};
  all_zeros(tab,5);
  all_zeros(tab2,4);
  return 0;
}
