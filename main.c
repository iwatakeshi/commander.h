#include "commander.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  cmdopt1("%d");
  cmdopt2("-r", "--row");
  cmdopt2("-c", "--column");
  
  int flag, index;
  while((flag = cmdparse(argc, argv, &index)) != -1) {
    switch(flag) {
      case 1: printf("index: %d, argv[index]: %s\n", index, argv[index]); break;
      case 2: printf("index: %d, argv[index]: %s\n", index, argv[index]); break;
    }
  }
  cmdprint();
  printf("%d\n", cmdcount());
  return 0;
}