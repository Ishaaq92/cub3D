#include "cub3d.h"



int main(int ac, char** av)
{
    char** map_arr;
    t_list* map_list;
    t_game* game;

    if (ac != 2)
    {
        printf("Usage: %s <map.cub>\n", av[0]);
        return (1);
    }
    game = NULL;
    map_arr = NULL;
    map_list = NULL;
    if (validate_input(&map_arr, &map_list, av[1], &game) != 0)
        return (clean_up(map_arr, &map_list));
    printf("Got here.\n");
    print_map(map_arr);
    free_array(map_arr);
    ft_lstclear(&map_list, free);
    return (0);
}