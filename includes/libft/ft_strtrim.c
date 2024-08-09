/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbansacc <sbansacc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 01:50:14 by sbansacc          #+#    #+#             */
/*   Updated: 2023/12/20 22:07:34 by sbansacc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	start;
	size_t	end;
	char	*strtrim;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	while (start < end && ft_strchr(set, s1[end - 1]))
		end--;
	strtrim = ft_calloc(end - start + 1, sizeof(char));
	if (!strtrim)
		return (NULL);
	i = 0;
	while (start < end)
	{
		strtrim[i] = s1[start];
		i++;
		start++;
	}
	return (strtrim);
}
