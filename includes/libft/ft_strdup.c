/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbansacc <sbansacc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 23:18:51 by sbansacc          #+#    #+#             */
/*   Updated: 2023/12/15 12:47:33 by sbansacc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*strdup;
	size_t	i;

	i = 0;
	strdup = ft_calloc((ft_strlen(s1) + 1), sizeof(char));
	if (!strdup)
		return (NULL);
	while (s1[i])
	{
		strdup[i] = s1[i];
		i++;
	}
	return (strdup);
}
