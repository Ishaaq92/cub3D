/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 14:52:04 by isahmed           #+#    #+#             */
/*   Updated: 2025/10/09 20:23:13 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIDTH 800
# define HEIGHT 800

# include <sys/time.h>
# include <math.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"
# include "mlx.h"
# include <stdbool.h>

/*Movement speeds*/
# define MOVE_SPEED 0.1
# define ROT_SPEED 0.05
# define MOUSE_SENSITIVITY 0.002

//Minimap
#define MMAP_SCALE 6
#define MINIMAP_RADIUS 6 
#define MMAP_MARGIN 10
#define MMAP_WALL_COLOR 0x444444
#define MMAP_DOOR_COLOR 0xAA8800
#define MMAP_PLAYER_COLOR 0xFF0000
#define MINIMAP_SIZE (MINIMAP_RADIUS * 2 + 1)
#define MINIMAP_CENTER (MINIMAP_RADIUS * MMAP_SCALE)
#define MINIMAP_ARROW_LEN 8
#define MINIMAP_ARROW_COLOR 0xFF0000 

//door
#define MAX_DOORS 50
#define DOOR_SPEED 0.8
#define	DOOR_HOLD_TIME 3.0
#define DOOR_CLOSE_SPEED 0.5
#define DOOR_FRAMES 32

//Set texture H and W
# define TEX_HEIGHT 64
# define TEX_WIDTH 64

//Sprite
#define MAX_SPRITE 50

typedef struct s_sprite
{
    double  x;
    double  y;
    int     tex_id;
    double  distance;
}   t_sprite;

//Img struct
typedef struct t_img
{
	void	*img;
	char	*pxls;
	int		bpp;
	int		width;
	int		height;
	int		line_length;
	int		endian;
} t_img;


// Door texture structure
typedef struct s_door_textures {
    t_img   frames[DOOR_FRAMES];  // Array of door frames
    int     frame_count;           // Actual number of loaded frames
} t_door_tex;

//Door struct
typedef struct s_door
{
	int			x;
	int			y;
	int			current_frame;
	double		open_width; // 0.0 = closed, 1.0 = fully open
	int			state; // 0 = closed, 1 = opening, 2 = open, 3 = closing
	double		timer; // time since last interaction
	// int			is_vertical;
}		t_door;

typedef struct s_player
{
	double		x;
	double		y;
	char		orientation;
	// movement
	bool		right;
	bool		left;
	bool		forward;
	bool		back;
	bool		rotate_right;
	bool		rotate_left;

} t_player;

typedef struct s_map
{
	char		**map;
	t_list		*map_list;
	int			map_size;
	int			floor_rgb;
	int			ceiling_rgb;
	char		*path_to_NO;
	char		*path_to_SO;
	char		*path_to_WE;
	char		*path_to_EA;
} t_map;

typedef struct s_ray
{
	double		ray_dir_x;
	double		ray_dir_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	//added features;
	char			tile;
	int			side;
	int			draw_start;
	int			draw_end;
	int			tex_x;
	int			tex_y;
	float		floor_x;
	float		floor_y;
	float		row_dist;
	float		rdy1;
	double		wall_x;
	double		tex_pos;
	double		step;
	double		distance;
	int			line_height;
	int			is_door_visible;
	t_door		*door;
} t_ray;

//struct for calculation to prevent lots of variable use (norminette)
typedef struct s_tex_calc
{
	int				x;
	float			fx;
	float			fy;
	float			frac_x;
	float			frac_y;
	unsigned int	fcol;
	unsigned int	ccol;
	int				cell_x;
	int				cell_y;
	float			world_x;
	float			world_y;
	float			tex_scale;
}	t_tex_calc;

typedef struct s_game
{
	t_map		*map;
	// t_player *player;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		camera_x;
	int			key_down;
	int			key_up;
	int			key_right;
	int			key_left;
} t_game;

typedef struct s_textures
{
	t_img		west;
	t_img		east;
	t_img		door;
	t_img		floor;
	t_img		north;
	t_img		south;
	t_img		roof;
	t_img		gun;
	t_img		sprite;
	t_door_tex	door_arr;
}	t_tex;

typedef struct s_data
{
	t_map		map;
	t_ray		*ray;
	t_game		*game;
	void		*mlx;
	void		*win;
	t_img		img;
	double		zoom;
	t_player	*player;
	//mouse
	int			mouse_x;
    int			mouse_y;
    int			mouse_locked;
	//Textures
	t_tex		textures;
	//door
	int			door_count;
	int			sprite_count;
	double		prev_time;
	double		*zbuffer;
	int			sprite_x_tex;
	t_door		doors[DOOR_FRAMES];
	t_sprite	sprites[MAX_SPRITE];
} t_data;

//new functions
unsigned int	apply_alpha(unsigned int color, double alpha);
int				get_door_frame(t_door *door, int total_frames);
void			render_sprites(t_data *data);
void			check_auto_doors(t_data *data);
int				load_door_frames(t_data *data);
void			sort_sprites(t_data *data);
void    		project_sprites(t_data *data);
void			update_sprite_distances(t_data *data);
void			init_sprites(t_data *data);
void    		draw_minimap(t_data *data);
double 			ease_in_out_cubic(double t);
t_door			*find_door(t_data *data, int x, int y);
void    		check_doors(t_data *data);
void			init_doors(t_data *data);
void			count_doors(t_data *data);
void			draw_gun(t_data *data);
void    		update_doors(t_data *data, double delta_time);
void			generate_floor_texture(t_data *data);
void			draw_floor_and_ceiling(t_data *data);
void			pixel_put(int x, int y, t_img *img, int colour);
unsigned int	get_pixel_img(t_img *img, int x, int y);
void			update_doors_with_frame(t_data *data, double delta_time);
void			draw_floor_row(t_data *d, int y, float rdx0, float rdy0, float rdx1, float rdy1);


//load xpm to image
void	load_textures(t_data *data);
t_img   load_xpm_to_img(void *mlx, char *path);

// parser.c
int		parser(t_data *data, char *file);

//mouse control
int mouse_move(int x, int y, t_data *data);
int mouse_click(int button, int x, int y, t_data *data);

// utils.c
int		ft_quit(t_data *data);
int		set_rgb(char *line);

// render.c
void	render(t_data *data);
// void	pixel_put(int x, int y, t_img *img, int colour);

// init.c
int		initialise_data(t_data *data);

// hooks.c
int		key_press_hold(int keycode, t_data *data);
void	walk(t_data *data, char dir, double scale);
void	rotate(t_data *data, double rot_speed);
int		key_release(int keycode, t_data *data);

// Validation functions
int		check_player(t_data *data);
int		check_allowed_chars(char **map, int map_size);
int		validate_map(t_data *data);
int		create_player(t_data *data, int i, int j, char orientation);
int		check_player_flow(t_data *data, int *pc);
int		handle_player_char(int i, int j, t_data *data, int *pc);
int		validate_input(t_data *data, char *file_name);

// Utils
int		check_walls(char **map, int map_size);
char	*dup_line(char *src);
void	free_array(char **arr);
void	print_map(char **map, int map_size);
int		clean_up(char **map, t_list **map_list);
void	free_list_and_exit(t_list **map_list);
int		player_error(const char *msg, t_player *player);

char	*dup_line(char *src);
void	free_array(char **arr);
int		file_extension_valid(char *filepath);
void	free_list_and_exit(t_list **map_list);

// dda.c
void	dda(t_data *data, int x);
void	initialise_ray(t_data *data);
void	set_side_dist(t_ray *ray, t_data *data);

// double	dda(t_data *data, int x);

// game.c
int		game_loop(t_data *data);

#endif
