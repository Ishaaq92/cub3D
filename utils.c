#include "cub3d.h"

int player_error(const char *msg, t_game* game)
{
    if (game && game->player)
    {
        free(game->player);
        game->player = NULL;
    }
    printf("%s\n", msg);
    return (1);
}

void    free_array(char** arr)
{
    int i;

    if (!arr)
        return;
    i = 0;
    while (arr[i])
        free(arr[i++]);
    free(arr);
}

void    print_map(char** map)
{
    int i;

    i = 0;
    if (!map)
        printf("No map here?\n");
    while (map[i])
    {
        printf("line[%d]: %s", i, map[i]);
        i++;
    }
}

void    free_list_and_exit(t_list** map_list)
{
    ft_lstclear(map_list, free);
    printf("malloc error.....exiting\n");
    exit(1);
}

int clean_up(char** map, t_list** map_list)
{
    if (map)
        free_array(map);
    if (map_list)
        ft_lstclear(map_list, free);
    return (1);
}

char*    dup_line(char* src)
{
    char* dup;
    int str_len;

    str_len = ft_strlen(src);
    dup = malloc(sizeof(char) * (str_len + 1));
    if (!dup)
        return (NULL);
    ft_strlcpy(dup, src, (str_len + 1));
    return (dup);
}
