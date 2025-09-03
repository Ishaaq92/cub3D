/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaladeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 19:38:12 by aaladeok          #+#    #+#             */
/*   Updated: 2024/05/03 20:12:09 by aaladeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*buff;
	size_t	i;

	if (nmemb && (SIZE_MAX / nmemb) < size)
		return (NULL);
	buff = malloc(nmemb * size);
	if (!buff)
		return (NULL);
	i = 0;
	while (i < (nmemb * size))
	{
		((unsigned char *)buff)[i] = '\0';
		i++;
	}
	return (buff);
}

char	*append_buff(char *big_buff, char *new_line)
{
	char	*temp;

	temp = ft_strjoin(big_buff, new_line);
	free(big_buff);
	return (temp);
}

// size_t	ft_strlen(char *str)
// {
// 	size_t	i;

// 	i = 0;
// 	while (str[i] != '\0')
// 		i++;
// 	return (i);
// }
