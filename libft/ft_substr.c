/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaladeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:09:30 by aaladeok          #+#    #+#             */
/*   Updated: 2024/04/11 15:47:04 by aaladeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	char	*src;
	size_t	substr_len;

	if (!s)
		return (NULL);
	if (ft_strlen((char *)s) < (size_t)start)
		return (ft_strdup(""));
	src = (char *)s + start;
	if (ft_strlen(src) < len)
		substr_len = ft_strlen(src) + 1;
	else
		substr_len = len + 1;
	substr = malloc(substr_len * sizeof(char));
	if (!substr)
		return (NULL);
	ft_strlcpy(substr, src, substr_len);
	return (substr);
}
