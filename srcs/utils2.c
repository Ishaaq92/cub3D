/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaladeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 21:35:28 by aaladeok          #+#    #+#             */
/*   Updated: 2025/09/10 21:35:34 by aaladeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	player_error(const char *msg, t_player *player)
{
	if (player)
	{
		free(player);
		player = NULL;
	}
	printf("%s\n", msg);
	return (1);
}

void	free_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	print_map(char **map, int map_size)
{
	int	i;

	i = 0;
	if (!map)
		printf("No map here?\n");
	while (i < map_size)
	{
		printf("line[%d]: %s", i, map[i]);
		i++;
	}
	printf("\n");
}

char	*dup_line(char *src)
{
	char	*dup;
	int		str_len;

	str_len = ft_strlen(src);
	dup = malloc(sizeof(char) * (str_len + 1));
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, src, (str_len + 1));
	return (dup);
}
