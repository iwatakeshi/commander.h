#include "commander.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
  /* Expect the options in the following order */

  // Expect a value as the first argument
  cmd_opt_value();
  // Expect a flag and a value as the second argument
  cmd_opt("-r", "--row", true);
  cmd_opt("-c", "--column", true);
  // Expect a flag that has no value as the fourth argument
  cmd_opt("-s", "--silent", false);

  int option;
  while ((option = cmd_parse(argc, argv)) != -1) {
    // Switch on the option id
    switch (option) {
      case 1: {
        // Use the cmd_opt_index and cmd_val_index functions to print
        // the index and value of the argument for the first option;
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

  // Print the options
  cmd_opt_print();
  
  // Print the number of options
  printf("option count: %d\n", cmd_opt_count());

  // Free the memory used at the end
  return cmd_free();
}