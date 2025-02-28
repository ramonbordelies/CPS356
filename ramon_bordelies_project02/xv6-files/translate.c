#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

// implementing functions that are not available in xv6 to make the requirements
int is_digit(int ch) {
    return ch >= '0' && ch <= '9';
}

int is_punct(int ch) {
    return (ch >= 33 && ch <= 47) ||  
           (ch >= 58 && ch <= 64) ||  
           (ch >= 91 && ch <= 96) ||  
           (ch >= 123 && ch <= 126);  
}

int is_space(int ch) {
    return ch == ' ' || ch == '\t' || ch == '\n';
}

int to_upper(int ch) {
    if (ch >= 'a' && ch <= 'z') {
        return ch - ('a' - 'A'); 
    }
    return ch;
}

int main() {
    int ch;
    char buf[1];

    // while loop that reads character by character until EOF (Ctrl+D to exit)
    while (read(0, buf, 1) == 1) { 
        ch = buf[0];

        if (is_digit(ch) || is_punct(ch)) {
            continue;
        }
        
        if (is_space(ch)) {
            buf[0] = '\n';
        } 
        else {
            buf[0] = to_upper(ch);
        }

        write(1, buf, 1); // Write to standard output
    }

    exit(); 
}
