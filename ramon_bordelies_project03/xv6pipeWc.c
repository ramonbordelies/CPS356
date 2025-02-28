#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char*argv[]){

    int p[2];
    char *wc_args[] = { "wc", 0 };

    if (argc < 2) 
    {
    printf(1, "Usage: <filename>\n", argv[0]);
    exit();
    }
    if (pipe(p) < 0) {
        printf(1, "failed pipe\n");
        exit();
    }

    int pid = fork();
    if (pid < 0) {
        printf(1, "failed fork\n");
        exit();
    }

    if (pid == 0) { 
        close(0);      
        dup(p[0]);    
        close(p[0]); 
        close(p[1]);
        exec("wc", wc_args);
        printf(1, "Error: exec failed\n");
        exit();
    } 
    else {
        close(p[0]);  

        int fd = open(argv[1], O_RDONLY);
        if (fd < 0) {
            printf(1, "cannot open file %s\n", argv[1]);
            exit();
        }

        char buffer[512];
        int i;
        while ((i = read(fd, buffer, sizeof(buffer))) > 0) {
            if(write(p[1], buffer, i) != i)
            {
                printf(1, "error\n");
                exit();
            }
        }
        if(i < 0)
        {
            printf(1, "error\n");
        }

        close(fd);
        close(p[1]);
        wait();  
    }

    exit();

}
