#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "mlx.h"
# define WIDTH 800
# define HEIGHT 800

typedef struct t_img
{
	void	*img;
	char	*pxls;
	int		bpp;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_data_
{
	void		*mlx;
	void		*win;
	t_img		*img;
	double		zoom;
}	t_data;

#endif
