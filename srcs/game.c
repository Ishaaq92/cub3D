/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:08:45 by isahmed           #+#    #+#             */
/*   Updated: 2025/10/09 20:16:29 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double	get_diff_in_usec(struct timeval t0)
{
	struct timeval t;
	struct timeval t1;
	
	gettimeofday(&t1, NULL);
	t.tv_sec = t1.tv_sec - t0.tv_sec;
	t.tv_usec = t1.tv_usec - t0.tv_usec;
	return ((double)(t.tv_sec * 1000000 + t.tv_usec));
}

void	fixed_fps(t_data *data, double fps)
{
	static struct timeval	t0;
	double					diff;

	fps ++;
	diff = get_diff_in_usec(t0) ;
	if ((diff) > ((1.0 / fps) * 1000000.0))
	{
		// printf("fps = %d\n", (int)(1000000 / diff));
		gettimeofday(&t0, NULL);
		render(data);
	}
	else
		return ;
	render(data);
	return ;
}

static long int	get_time_in_ms(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

void	move(t_data *data)
{
	t_player	*player;
	double		pace;

	pace = 0.01;
	player = data->player;
	if (player->forward)
	 	walk(data, 'f', pace);
	if (player->back)
	 	walk(data, 'b', -pace);
	if (player->right)
	 	walk(data, 'r', -pace);
	if (player->left)
	 	walk(data, 'l', pace);
	if (player->rotate_right)
		rotate(data, -0.01);
	if (player->rotate_left)
		rotate(data, 0.01);

	// player->forward = false;
	// player->back = false;
	// player->right = false;
	// player->left = false;

	// player->rotate_right = false;
	// player->rotate_left = false;
}


int	game_loop(t_data *data)
{
	static long			frames = 0;
	static long int		t0;

	move(data);
	if (get_time_in_ms() - t0 > 1000)
	{
		t0 = get_time_in_ms();
		printf("%ld\n", frames);
		frames = 0;
	}
	render(data);
	frames ++;
	return (0);
}
