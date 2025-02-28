#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main() {
    // tracking current and previous character 
    char ch, prev = 0; 

    // while loop to read every character using xv6 read() cmd with respective libraries
    while (read(0, &ch, 1) == 1) {  
        if (ch == '\n') {
            if (prev != '\n') {
                // write current character as long as the previous is not a newline character
                write(1, &ch, 1); 
            }
        } 
        else 
        {
            // write the character
            write(1, &ch, 1); 
        }
        prev = ch; 
    }

    exit(); 
}

 