/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbansacc <sbansacc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 01:29:31 by sbansacc          #+#    #+#             */
/*   Updated: 2023/12/27 20:02:35 by sbansacc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*buffdst;
	unsigned char	*buffsrc;

	if (!dst && !src)
		return (NULL);
	buffsrc = (unsigned char *)src;
	buffdst = (unsigned char *)dst;
	i = 0;
	if (src < dst)
		while (len--)
			buffdst[len] = buffsrc[len];
	else
	{
		while (i < len)
		{
			buffdst[i] = buffsrc[i];
			i++;
		}
	}
	return (dst);
}
