/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbansacc <sbansacc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 00:20:25 by sbansacc          #+#    #+#             */
/*   Updated: 2023/11/15 07:32:20 by sbansacc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*interdst;
	unsigned char	*intersrc;

	if (!dst && !src)
		return (NULL);
	i = 0;
	interdst = (unsigned char *)dst;
	intersrc = (unsigned char *)src;
	while (i < n)
	{
		interdst[i] = intersrc[i];
		i++;
	}
	return (dst);
}
