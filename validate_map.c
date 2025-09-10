#include "cub3d.h"

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

int handle_player_char(char c, int i, int j, t_game* game, int* pc, char* pos)
{
    // printf("In handle player char \n");
    if (ft_strchr(pos, c))
    {
        ++(*pc);
        if (*pc > 1)
        {
            player_error("Multi-player error.....exiting\n", game);
            return (1);
        }
        if (create_player(&game->player, i, j, c) != 0)
            return (1);
    }  
    return (0);
}

int   check_player_flow(char** map, char *positions, t_game* game, int* pc)
{
    int i;
    int j;
    
    i = 0;
    // printf("In check player_flow \n");
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (handle_player_char(map[i][j], i, j, game, pc, positions) != 0)
                return (1);
            ++j;
        }
        ++i;            
    }
    return (0);
}

int check_player(char** map, t_game *game)
{
    int player_count;
    char* exp_player_pos = "NSEW";

    printf("In check player \n");
    player_count = 0;
    if (check_player_flow(map, exp_player_pos, game, &player_count) != 0)
        return (1);
    if (player_count == 0)
    {
        player_error("error: no player in map..exiting\n", game);
        return (1);
    }
    return (0);
}

int validate_map(char** map, t_game** game)
{
    // printf("opening door to validate map\n");
    if (check_allowed_chars(map) != 0)
        return (1);
    if (check_walls(map) != 0)
        return (1);
    if (check_player(map, *game) != 0)
        return (1);
    printf("exiting validate map\n");
    return (0);
}