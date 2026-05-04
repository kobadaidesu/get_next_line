#include "get_next_line.h"

char *get_next_line(int fd)
{
    char temp[2];
    char *line;
    char *new_line;
    int c;

    line = malloc(1);
    line[0] = '\0';
    temp[1] = '\0';
    while(1) 
    {
        c = ft_getc(fd);
        if(c == EOF)
        {
            if (line[0] == '\0')
            {
                free(line);
                return NULL;
            }
            return line;
        }
        temp[0] = c;
        new_line = ft_strjoin(line, temp);
        free(line);
        if(temp[0] == '\n')
            return new_line;
        line = new_line;
    }

}

int main(void)
{
    char *line;
    int fd = open("test.txt", O_RDONLY);

    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            break ;
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
