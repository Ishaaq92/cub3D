/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 21:36:45 by aaladeok          #+#    #+#             */
/*   Updated: 2025/10/09 16:23:21 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	create_player(t_player **player, int i, int j, char orientation)
{
	*player = malloc(sizeof(t_player));
	if (!*player)
	{
		printf("Malloc error.....exiting\n");
		return (1);
	}
	(*player)->x = i + 0.3;
	(*player)->y = j + 0.3;
	(*player)->orientation = orientation;
	printf("Player has been duly allocated.\n");
	return (0);
}

int	handle_player_char(int i, int j, t_data *data, int *pc)
{
	char	c;
	char	*pos;

	c = data->map.map[i][j];
	pos = "NSEW";
	if (ft_strchr(pos, c))
	{
		++(*pc);
		if (*pc != 1)
		{
			player_error("Multi-player error.....exiting\n", data->player);
			return (1);
		}
		if (create_player(&data->player, i, j, c) != 0)
			return (1);
	}
	return (0);
}

int	check_player_flow(t_data *data, int *pc)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map.map_size)
	{
		j = 0;
		while (data->map.map[i][j])
		{
			if (handle_player_char(i, j, data, pc) != 0)
				return (1);
			++j;
		}
		++i;
	}
	return (0);
}

int	check_player(t_data *data)
{
	int	player_count;

	printf("In check player \n");
	player_count = 0;
	if (check_player_flow(data, &player_count) != 0)
		return (1);
	if (player_count == 0)
	{
		player_error("error: no player in map..exiting\n", data->player);
		return (1);
	}
	return (0);
}

int	validate_map(t_data *data)
{
	if (check_allowed_chars(data->map.map, data->map.map_size) != 0)
		return (1);
	if (check_walls(data->map.map, data->map.map_size) != 0)
		return (1);
	if (check_player(data) != 0)
		return (1);
	printf("exiting validate map\n");
	return (0);
}
