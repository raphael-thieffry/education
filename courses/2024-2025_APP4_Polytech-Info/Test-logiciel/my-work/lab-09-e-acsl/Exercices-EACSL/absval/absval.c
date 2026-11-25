
int absval(int x) {
  if(x >= 0) {
    return x;
  }
  return -x;
}

int main(void) {
  absval(6);
  absval(-3);
  return 0;
}
