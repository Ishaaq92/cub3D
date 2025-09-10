#include "cub3D.h"

int create_player(t_player** player, int i, int j, char orientation)
{
    *player = malloc(sizeof(t_player));
    if (!*player)
    {
        printf("Malloc error.....exiting\n");
        return (1);
    }
    (*player)->row = i;
    (*player)->column = j;
    (*player)->orientation = orientation;
    printf("Player has been duly allocated.\n");
    return (0);
}

int handle_player_char(char c, int i, int j, t_player* player, int* pc, char* pos)
{
    // printf("In handle player char \n");
    if (ft_strchr(pos, c))
    {
        ++(*pc);
        if (*pc > 1)
        {
            player_error("Multi-player error.....exiting\n", player);
            return (1);
        }
        if (create_player(&player, i, j, c) != 0)
            return (1);
    }  
    return (0);
}

int   check_player_flow(char** map, int map_size, char *positions, t_player* player, int* pc)
{
    int i;
    int j;
    
    i = 0;
    // printf("In check player_flow \n");
    while (i < map_size)
    {
        j = 0;
        while (map[i][j])
        {
            if (handle_player_char(map[i][j], i, j, player, pc, positions) != 0)
                return (1);
            ++j;
        }
        ++i;            
    }
    return (0);
}

int check_player(char** map, int map_size, t_player *player)
{
    int player_count;
    char* exp_player_pos = "NSEW";

    printf("In check player \n");
    player_count = 0;
    if (check_player_flow(map, map_size, exp_player_pos, player, &player_count) != 0)
        return (1);
    if (player_count == 0)
    {
        player_error("error: no player in map..exiting\n", player);
        return (1);
    }
    return (0);
}

int validate_map(t_data *data)
{
    // printf("opening door to validate map\n");
    if (check_allowed_chars(data->map.map, data->map.map_size) != 0)
        return (1);
    if (check_walls(data->map.map, data->map.map_size) != 0)
        return (1);
    if (check_player(data->map.map,data->map.map_size, data->player) != 0)
        return (1);
    printf("exiting validate map\n");
    return (0);
}