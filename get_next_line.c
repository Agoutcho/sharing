#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

char *get_next_line(int fd)
{
    printf("Function name : %s\n",__FUNCTION__);
    int i = 0;
    int flag = 0;
    char buffer[BUFFER + 1];
    int after_read = read(fd, buffer, BUFFER);
    printf("nombre of byte read : %d\n",after_read);
    buffer[after_read] = 0;
    while (buffer[i])
    {
        if(buffer[i] == '\n')
        {
            flag = 1;
            printf("tik \n");
            printf("buffer = %s§§§\n",buffer);
            buffer[i + 1] = 0;
            printf("buffer = %s§§§\n",buffer);
            // printf("i = %d break\n",i);
            break;
            //write(1, "tik", 3);
        }
        //printf("pok \n");
        //write(1, "tak", 3);
        //printf("i = %d ",i);
        i++;
    }
    if(flag)
        // printf("tak \n");
        //write(1, "pok", 3);
        printf("i = %d tak\n",i);
    return (NULL);
}

int main(int argc, char **argv)
{
    printf("BUFFER = %d\n",BUFFER);
    int fd = open("file.txt",  O_RDONLY);
    if (open("file.txt",  O_RDONLY) != -1){
        get_next_line(fd);
        get_next_line(fd);
        get_next_line(fd);
        get_next_line(fd);
    }
    close(fd);
	return (0);
}