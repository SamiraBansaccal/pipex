/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbansacc <sbansacc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 01:50:49 by sbansacc          #+#    #+#             */
/*   Updated: 2023/12/27 19:58:06 by sbansacc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	getac(char const *s, char c, size_t *s_index, size_t *substart)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	*s_index = 0;
	*substart = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			count++;
		i++;
	}
	return (count);
}

static void	free_them_all(char **ptr, size_t i_max)
{
	size_t	i;

	i = 0;
	while (i < i_max)
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

static char	*subscpy(size_t *substart, char const *s, char c)
{
	char	*substr;
	size_t	sublen;
	size_t	i;

	if (ft_strchr(s + *substart, c) == NULL)
		sublen = ft_strlen(s + *substart);
	else
		sublen = ft_strchr(s + *substart, c) - (s + *substart);
	if (sublen == 0)
		return (NULL);
	substr = ft_calloc(sublen + 1, sizeof(char));
	if (!substr)
		return (NULL);
	i = 0;
	while (s[*substart] && i < sublen)
	{
		substr[i] = s[*substart];
		(*substart)++;
		i++;
	}
	return (substr);
}

char	**ft_split(char const *s, char c)
{
	size_t	count;
	size_t	i;
	size_t	substart;
	char	**split;

	if (!s)
		return (NULL);
	count = getac(s, c, &i, &substart);
	split = ft_calloc(count + 1, sizeof(char *));
	if (!split)
		return (NULL);
	while (count > i)
	{
		while (s[substart] == c)
			substart++;
		split[i] = subscpy(&substart, s, c);
		if (!split[i])
		{
			free_them_all(split, i);
			return (NULL);
		}
		i++;
	}
	return (split);
}
