/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbansacc <sbansacc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 01:50:56 by sbansacc          #+#    #+#             */
/*   Updated: 2023/12/27 19:55:19 by sbansacc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_itoalen(int n)
{
	int			itoalen;

	itoalen = 1;
	if (n < 0)
	{
		itoalen++;
		n *= (-1);
	}
	while (n > 9)
	{
		n /= 10;
		itoalen++;
	}
	return (itoalen);
}

char	*ft_itoa(int n)
{
	char	*itoa;
	int		itoalen;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	itoalen = ft_itoalen(n);
	itoa = ft_calloc(itoalen + 1, sizeof(char));
	if (!itoa)
		return (NULL);
	if (n < 0)
	{
		itoa[0] = '-';
		n *= (-1);
	}
	itoalen--;
	while (n > 0)
	{
		itoa[itoalen] = '0' + (n % 10);
		itoalen--;
		n /= 10;
	}
	return (itoa);
}
