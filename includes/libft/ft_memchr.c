/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbansacc <sbansacc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 03:23:32 by sbansacc          #+#    #+#             */
/*   Updated: 2023/11/23 01:02:22 by sbansacc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ucs;

	i = 0;
	ucs = (unsigned char *)s;
	while (i < n)
	{
		if (ucs[i] == (unsigned char)c)
			return ((void *)(ucs + i));
		i++;
	}
	return (NULL);
}
