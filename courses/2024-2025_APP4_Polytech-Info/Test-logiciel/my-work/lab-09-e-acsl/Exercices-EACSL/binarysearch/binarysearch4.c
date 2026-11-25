#include"binarysearch.h"

int binarysearch(int *tab, int length, int val) {
  int low = 0;
  int high = length;
  int med;

  while(low <= high) {
    med = low + (high - low) / 2;
    if(val < tab[med]) {
      high = med - 1;
    } else if(val > tab[med]) {
      low = med + 1;
    } else {
      return med;
    }
  }

  return -1;
}
