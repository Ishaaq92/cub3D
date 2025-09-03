// int main (void)
// {
//     int fd;
//     int count = 0;
//     char* str;

//     fd = open("example.txt", O_RDONLY);
//     while (1)
//     {
//         str = get_next_line(fd);
//         if (str == NULL)
//             break;
//         count++;
//         printf("[%d]:%s\n", count, str);
//         free(str);
//         str = NULL;
//     }
//     close(fd);
//     return (0);
// }

//cc main.c -L./libft -lft -I./libft -o main