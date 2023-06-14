#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

void map(int fd)
{
    char line[1024];
    while (read(fd, line, sizeof(line)) > 0)
    {
        int number = atoi(line);
        printf("%d\t%d\n", number, number);
    }
}
int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

void reduce()
{

    int key, value;
    int count = 0;
    int sorted_values[1024];

    while (scanf("%d\t%d\n", &key, &value) > 0)
    {
        sorted_values[count++] = value;
    }

    qsort(sorted_values, count, sizeof(int), compare);

    for (int i = 0; i < count; i++)
    {
        printf("%d\n", sorted_values[i]);
    }
}

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("Usage: ./sort <input_file>\n");
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        printf("Failed to open input file.\n");
        return 1;
    }

    pid_t pid = fork();
    if (pid < 0)
    {
        printf("Failed to create child process.\n");
        return 1;
    }

    if (pid == 0)
    {
        map(fd);
    }
    else
    {
        wait(NULL);

        lseek(fd, 0, SEEK_SET);
        dup2(fd, STDIN_FILENO);
        close(fd);

        reduce();
    }

    return 0;
}