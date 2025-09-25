/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:08:45 by isahmed           #+#    #+#             */
/*   Updated: 2025/09/25 14:42:21 by isahmed          ###   ########.fr       */
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
	static int				start = 1;
	double					diff;

	fps ++;
	if (start == 1)
	{
		gettimeofday(&t0, NULL);
		render(data);
		start = 0;
		return ;
	}
	diff = get_diff_in_usec(t0) ;
	if ((diff) > ((1.0 / fps) * 1000000.0))
	{
		printf("fps = %d\n", (int)(1000000 / diff));
		gettimeofday(&t0, NULL);
		render(data);
		start = 1;
	}
	else
		return ;
	render(data);
	return ;
}

int	game_loop(t_data *data)
{
	// static long			frames = 0;
	// static int			start = 1;
	// static long int		t0;

	fixed_fps(data, 60);
	return (0);
	// if (start == 1)
	// {
	// 	t0 = get_time_in_ms();
	// 	render(data);
	// 	start = 0;
	// 	return (0);
	// }
	// if (get_time_in_ms() - t0 > 1000)
	// {
	// 	t0 = get_time_in_ms();
	// 	printf("%ld\n", frames);
	// 	start = 1;
	// 	frames = 0;
	// }
	// render(data);
	// frames ++;
	// return (0);
}