#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>

// Initialize C Program
int main(int argc, char* argv[]) {

    // If no file is entered by terminal, exit the return 1
    if (argc == 1) 
    {
        return 1;
    } 

    int count = 0; 
    int noneCount = 0;

    // Loop that itirates for each file after executable
    for (int i = 1; i < argc; i++)
    {
        int fd = open(argv[i], O_RDONLY);
        // If open() recieves an error opening the file, print error message 
        if (fd == -1) {
            perror("Error opening file");
            continue;
        }
    
        // Reading in chunks the 'U's and 'D's from files opened in fd using read()
        char buffer[1024];
        ssize_t readBytes; 
        while ((readBytes = read(fd, buffer, 1024)) > 0)
        {
            for(ssize_t j = 0; j < readBytes; j++)
            {
                if (buffer[j] == 'U' || buffer[j] == 'D')
                {
                    count++; 
                }
                else if (!isspace((unsigned char)buffer[j])) {
                        noneCount++;
                }
            }
        }

        close(fd);
    }

    // Program returns 0 if any 'U' or 'D' are found in files and returns 1 otherwise 
    if(count > 0) {
        printf("UD characters: %d\n", count);
        fprintf(stderr, "Non UD characters: %d\n",noneCount);
    }
    else 
    {
        return 1;
    }

    return 0; 

}
