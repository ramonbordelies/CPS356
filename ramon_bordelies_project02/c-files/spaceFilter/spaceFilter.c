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

    

    // Loop that itirates for each file after executable
    for (int i = 1; i < argc; i++)
    {
        int fd = open(argv[i], O_RDONLY);
        // If open() recieves an error opening the file, print error message 
        if (fd == -1) {
            perror("Error opening file");
            continue;
        }
    
        // Reading in chunks from files opened in fd using read()
        char buffer[1024];
        ssize_t readBytes; 
        int newline = 0;

        while ((readBytes = read(fd, buffer, 1024)) > 0)
        {
            for(ssize_t j = 0; j < readBytes; j++)
            {
                if (buffer[j] == '\n')
                {
                    // Filter consecutive newlines
                    if (!newline) {
                        write(STDIN_FILENO, &buffer[j], 1);
                    }
                    // Determines if last character was a new line
                    newline = 1;
                }
                else {
                    // Output the current non-newline character
                    write(STDOUT_FILENO, &buffer[j], 1); 
                    newline = 0;
                }
            }
        }

        close(fd);
    }

    return 0; 

}
