#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

#ifndef BUFFER_SIZE
#    define BUFFER_SIZE 5000000
#endif

#include <unistd.h>
#include <stdlib.h>

char    *ft_strdup(char *str)
{
        int     len = 0;
        while (str[len])
                len++;
        char    *res = malloc(len + 1); 
        len = 0;
        while (str[len])
        {
                res[len] = str[len];
                len++;
        }
        res[len] = 0;
        return res;
}

char    *get_next_line(int fd) 
{
        static char     buffer[BUFFER_SIZE];
        static char            line[100000];
        static int      buffer_pos;
        static int      reads_size;
        int             i;

        i = 0;
        if (fd < 0 || BUFFER_SIZE <= 0)
                return NULL;
        while (1337)
        {
                if (buffer_pos >= reads_size)
                {   
                        reads_size = read(fd, buffer, BUFFER_SIZE);
                        buffer_pos = 0;
                        if (reads_size <= 0)
                                break ;
                }
                line[i++] = buffer[buffer_pos++];
                if (buffer[buffer_pos - 1] == '\n' || i >= (int)sizeof(line) - 1)
                        break ;
        }
        line[i] = 0;
        if (i == 0)
                return NULL;
        return (ft_strdup(line));
}


int main(void)
{
    printf("BUFFER_SIZE: %d\n", BUFFER_SIZE);
    int fd = open("test.txt", O_RDWR);
    char    *line = get_next_line(fd);
    while (line)
    {
        printf("[%s]\n", line);
        line = get_next_line(fd);
    }
    printf("[%s]\n", line);
}