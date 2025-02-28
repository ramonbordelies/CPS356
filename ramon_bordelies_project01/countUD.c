#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

char buf[512];

// Initialize xv6 Program
int main(int argc, char *argv[]) {
  int fd, i;
  int n, count = 0, noneCount = 0;

  // If no file is entered by terminal, exit with exit() command
  if (argc <= 1) {
    printf(1, "Enter a file. Use 'echo' cmd to write into the file. For example: echo 'UD' > test.txt\n");
    exit();
  }

  // Loop that itirates for each file after inputted in qemu 
  for (i = 1; i < argc; i++) {

    // If open() recieves an error opening the file, print error message and exit() 
    if ((fd = open(argv[i], O_RDONLY)) < 0) {
      printf(1, "Error opening file. %s\n", argv[i]);
      exit();
    }

    // Reading in chunks the 'U's and 'D's from files opened in fd using xv6 read()
    while ((n = read(fd, buf, sizeof(buf))) > 0) {

        for (int i = 0; i < n; i++) {

            if (buf[i] == 'U' || buf[i] == 'D') {
                count++;
            } else if (buf[i] != ' ' && buf[i] != '\n' && buf[i] != '\t') {
                noneCount++;
            }
    }
  }
    close(fd);
  }
  if (n < 0) {
    printf(1, "Error reading file.\n");
    exit();
  }

  // Program prints amount of characters if any 'U' or 'D' are found in files and returns exit() otherwise 
  if (count > 0) {
    printf(1, "UD characters: %d\n", count);
    printf(1, "Non UD characters: %d\n", noneCount);
  } else {
    exit();
  }

  exit();
}
 