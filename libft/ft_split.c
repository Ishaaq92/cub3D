/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaladeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 21:00:35 by aaladeok          #+#    #+#             */
/*   Updated: 2024/04/18 10:05:51 by aaladeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_w(char const *s, char sep)
{
	int	word_count;

	word_count = 0;
	while (*s)
	{
		while (*s == sep)
			s++;
		if (*s)
			word_count++;
		while (*s && *s != sep)
			s++;
	}
	return (word_count);
}

void	write_arr(const char *s, char **dest, char c, int len)
{
	int		i;
	int		j;
	int		start;	

	i = 0;
	j = 0;
	while (i < len)
	{
		while (s[j] && s[j] == c)
			j++;
		start = j;
		while (s[j] && s[j] != c)
			j++;
		dest[i++] = ft_substr(s, start, j - start);
	}
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		size;

	if (!s)
		return (NULL);
	size = ft_count_w(s, c);
	str = (char **)malloc(sizeof(char *) * (size + 1));
	if (str == NULL)
		return (NULL);
	str[size] = NULL;
	write_arr(s, str, c, size);
	return (str);
}
