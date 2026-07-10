/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wgolbert <wgolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 20:26:40 by wgolbert          #+#    #+#             */
/*   Updated: 2026/07/09 20:26:40 by wgolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
    size_t	i;

    i = 0;
    while (s[i])
        i++;
    return (i);
}

int	ft_strchr(const char *s, int i)
{
	while (s[i])
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	if (s[i] == '\n')
		return (i);
	return (-1);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while (src[i] && i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (!s)
		return (NULL);
	str = malloc(len * (sizeof(char)) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len && s[i + start])
	{
		str[i] = s[i + start];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t			i;
	size_t			max;
	unsigned char	*r_pointer;

	max = 2147483647;
	if (size != 0 && nmemb > max / size)
		return (NULL);
	r_pointer = (malloc (size * nmemb));
	if (!r_pointer)
		return (NULL);
	i = 0;
	while (i < nmemb * size)
	{
		r_pointer[i] = '\0';
		i++;
	}
	return ((void *)r_pointer);
}
