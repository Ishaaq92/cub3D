/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isahmed <isahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 21:36:25 by aaladeok          #+#    #+#             */
/*   Updated: 2025/10/09 20:35:44 by isahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_allowed_chars(char **map, int map_size)
{
	int			i;
	int			j;
	const char	*expected_chars = "10NSEW ";

	i = 0;
	while (i < map_size)
	{
		j = 0;
		while (map[i][j])
		{
			if ((map[i][j] != '\n') && !ft_strchr(expected_chars, map[i][j]))
			{
				printf("Map error at row %d, col %d.\n", i, j);
				return (1);
			}
			++j;
		}
		++i;
	}
	return (0);
}

int	get_row_len(char **map, int map_size, int *len)
{
	if (!map || !map[0])
		return (1);
	*len = 0;
	while (*len < map_size)
		++(*len);
	return (0);
}

int	check_cell(char **map, int row, int col, int max_rows,
		const char *exp_chars)
{
	if (row < 0 || row >= max_rows)
		return (1);
	if (col < 0 || (size_t) col >= ft_strlen(map[row]))
		return (1);
	if (map[row][col] == ' ' || !ft_strchr(exp_chars, map[row][col]))
		return (1);
	return (0);
}

int	is_valid(char **map, int i, int j, int len)
{
	static const char	*exp_chars = "01NEWS";

	if (check_cell(map, i - 1, j, len, exp_chars))
		return (1);
	if (check_cell(map, i + 1, j, len, exp_chars))
		return (1);
	if (check_cell(map, i, j - 1, len, exp_chars))
		return (1);
	if (check_cell(map, i, j + 1, len, exp_chars))
		return (1);
	return (0);
}

int	check_details(char **map, int map_size, int i, int j, int len)
{
	if (i < map_size && map[i][j] != '1' && map[i][j] != ' ' && map[i][j] != '\n')
	{
		if (is_valid(map, i, j, len) != 0)
		{
			printf("Map error at row %d, col %d.\n", i, j);
			return (1);
		}
	}
	return (0);
}

int	check_walls(char **map, int map_size)
{
	int	i;
	int	j;
	int	len;

	if (get_row_len(map, map_size, &len) != 0)
		return (1);
	i = 0;
	while (i < map_size)
	{
		j = 0;
		while (map[i][j])
		{
			if (check_details(map, map_size, i, j, len))
				return (1);
			++j;
		}
		i++;
	}
	return (0);
}
