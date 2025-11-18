/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaladeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 15:12:10 by aaladeok          #+#    #+#             */
/*   Updated: 2025/11/05 15:12:14 by aaladeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	texture_path_complete(t_tex_flags *flags)
{
	if (!flags->has_north)
		return (1);
	if (!flags->has_south)
		return (1);
	if (!flags->has_west)
		return (1);
	if (!flags->has_east)
		return (1);
	return (0);
}

int	starts_with(const char *str, const char *prefix)
{
	int	i;

	i = 0;
	while (*str == ' ' || *str == '\t')
		str++;
	while (prefix[i])
	{
		if (str[i] != prefix[i])
			return (0);
		i++;
	}
	return (1);
}

// Skip whitespace and tabs
char	*skip_whitespace(char *str)
{
	while (*str && (*str == ' ' || *str == '\t'))
		str++;
	return (str);
}
