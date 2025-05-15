#include <unistd.h>
int main(int argc, char **argv)
{
    if (argc != 2)
    {
        write(1, "Error\n", 6);
        return 1;
    }
    char *str = argv[1];
    char i = 0;
    while (str[i] != '\0')
    {
        str[i] = str[i] - i;
        i++;
    }
    write(1, str, i);
    write(1, "\n", 1);
}