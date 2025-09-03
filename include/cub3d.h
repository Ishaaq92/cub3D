#ifndef CUB3D_H
# define CUB3D_H

#include "../libft/libft.h"
#include <fcntl.h>
#include <stdio.h>

/*These are all test structs*/
typedef struct  s_player {
    // double  x;
    // double  y;
    // double  dir_x;
    // double  dir_y;
    // double  plane_x;
    // double  plane_y;
    int row;
    int column;
    char    orientation;
}   t_player;

typedef struct s_config {
    char* tex_no;
    char* tex_so;
    char* tex_we;
    char* tex_ea;
    int floor_color;
    int ceiling_color;
}   t_config;

typedef struct s_map {
    char** grid;
    int width;
    int height;
}   t_map;

typedef struct s_window {
    void*   mlx;
    void*   window;
    int width;
    int height;
}   t_window;

typedef struct s_game {
    t_config    *config;
    t_map       *map;
    t_player    *player;
    t_window    *window;
}   t_game;


//Utils
int check_walls(char** map);
char*    dup_line(char* src);
void    free_array(char** arr);
void    print_map(char** map);
int clean_up(char** map, t_list** map_list);
void    free_list_and_exit(t_list** map_list);
int player_error(const char *msg, t_game* game);

char*    dup_line(char* src);
void    free_array(char** arr);
char** list_to_array(t_list* list);
int file_extension_valid(char* filepath);
void    free_list_and_exit(t_list** map_list);
t_list* read_file_to_list(const char* path);


//Validation functions
int check_player(char** map, t_game* game);
int check_allowed_chars(char** map);
int validate_map(char** map, t_game** game);
int create_player(t_player** player, int i, int j, char orientation);
int   check_player_flow(char** map, char *positions, t_game* game, int* pc);
int handle_player_char(char c, int i, int j, t_game* game, int* pc, char* pos);
int validate_input(char*** map, t_list** map_list, char* file_name, t_game** game);


#endif