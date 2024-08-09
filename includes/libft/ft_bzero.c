/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbansacc <sbansacc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 04:16:31 by sabansac          #+#    #+#             */
/*   Updated: 2023/12/10 21:51:48 by sbansacc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*inters;

	i = 0;
	inters = (unsigned char *)s;
	while (i < n)
	{
		inters[i] = 0;
		i++;
	}
}
