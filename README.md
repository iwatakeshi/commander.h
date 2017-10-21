# commander.h
A basic command line utility for C.

## API

```c 
/**
 * Returns the number of options created
 */
int cmd_opt_count();
/**
 * Prints a list of options
 */
void cmd_opt_print();
/**
 * Returns the index of where the option is located in argv
 */
int cmd_opt_index();
/**
 * Returns the index of where the value is located in argv.
 * Note: When no value is provided, the index will be 0 which points to argv[0].
 */
int cmd_val_index();
/**
 * Create an option that expects a value.
 */
void cmd_opt_value();
/**
 * Create an option that expects a flag that could have a value.
 */
void cmd_opt(char* flag, char* name, bool valuable);
/**
 * Parse the command arguments.
 * Returns -1 once the process has completed.
 */
int cmd_parse(int argc, char* argv[]);
/**
 * Frees the memory used for commander.
 * Returns 0 when completed.
 */
int cmd_free(); 
```

## Usage

Simply include "commander.h" into your program and compile.


> Note: Warnings about write strings may appear when compiling in C++. You can add the `-Wno-write-strings` option to surpress it.


```c
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
```
