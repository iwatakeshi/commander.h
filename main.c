#include "commander.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
  // Expect the options in the following order
  cmd_opt_value();
  // Expect a flag and a value
  cmd_opt("-r", "--row", true);
  cmd_opt("-c", "--column", true);
  // Expect a flag that has no value
  cmd_opt("-s", "--silent", false);
  int option;
  while ((option = cmd_parse(argc, argv)) != -1) {
      // Switch on the option id
      switch (option) {
      case 1: {
        printf("option index: %d, value: %s\n", cmd_opt_index(), argv[cmd_val_index()]);
        break;
      }
      case 4: {
        printf("option index %d, silent flag: %s\n", cmd_opt_index(), argv[cmd_opt_index()]);
        break;
      }
      default: {
        printf("option index: %d, flag: %s, value: %s\n", cmd_opt_index(), argv[cmd_opt_index()], argv[cmd_val_index()]);
        break;
      }
      }
    
  }
  cmd_opt_print();
  printf("Option count: %d\n", cmd_opt_count());
  return 0;
}