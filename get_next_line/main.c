#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

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