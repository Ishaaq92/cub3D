/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaladeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:28:36 by aaladeok          #+#    #+#             */
/*   Updated: 2024/04/20 18:44:30 by aaladeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*n_str;
	size_t	i;

	i = 0;
	n_str = (char *)malloc(sizeof(char) * (ft_strlen((char *)s1) + \
				ft_strlen((char *)s2) + 1));
	if (n_str == NULL)
		return (NULL);
	while (*s1)
	{
		n_str[i] = *s1;
		i++;
		s1++;
	}
	while (*s2)
	{
		n_str[i] = *s2;
		i++;
		s2++;
	}
	n_str[i] = 0;
	return (n_str);
}
