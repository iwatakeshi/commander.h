#include "commander.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  cmdopt1("%d");
  cmdopt2("-r", "--row");
  cmdopt2("-c", "--column");
  
  int flag;
  while((flag = cmdparse(argc, argv)) != -1) {
    printf("flag: %d\n", flag);
    switch(flag) {
      case 1: printf("index: %d, argv[index]: %s\n", cmdindex(), argv[cmdindex()]); break;
      case 2: printf("index: %d, argv[index]: %s\n", cmdindex(), argv[cmdindex()]); break;
    }
  }
  cmdprint();
  printf("%d\n", cmdcount());
  return 0;
}