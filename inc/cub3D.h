/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 14:52:04 by isahmed           #+#    #+#             */
/*   Updated: 2025/09/08 15:06:35 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include "mlx.h"
# include "libft.h"
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
	t_img		img;
	double		zoom;
}	t_data;

// utils.c
int	ft_quit(t_data *data);

// render.c
void	render(t_data *data);
void	pixel_put(int x, int y, t_img *img, int colour);

// init.c
int	initialise_data(t_data *data);

// hooks.c
int	key_hook(int keycode, t_data *data);

#endif
