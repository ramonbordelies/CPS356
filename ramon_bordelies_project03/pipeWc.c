#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {

    if (argc == 1) 
    {
        exit(1);
    } 

    int p[2];  
    if (pipe(p) == -1) {
        perror("pipe failed");
        exit(1);
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {  
        close(0);        
        dup(p[0]);      
        close(p[0]); 
        close(p[1]); 

        execlp("wc", "wc", NULL);
    
        perror("execlp failed");
        exit(1);
    } else {  
        close(p[0]); 

        int fd = open(argv[1], O_RDONLY);
        if (fd < 0) {
            perror("open failed");
            exit(1);
        }
     
        char buffer[1024];
        int i;
        while ((i = read(fd, buffer, sizeof(buffer))) > 0) {
            int written = write(p[1], buffer, i);
            if (written != i)
            {
                perror("write failed");
                exit(1);
            }
        }
        if (i < 0)
        {
            perror("read failed");
            exit(1);
        }
        close(fd);  
        close(p[1]); 
        waitpid(pid, NULL, 0);
    }

    return 0;
}
