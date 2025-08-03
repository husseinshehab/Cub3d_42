/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshehab <hshehab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 10:39:34 by hshehab           #+#    #+#             */
/*   Updated: 2024/06/18 15:02:08 by hshehab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_number(int n)
{
	int	count;

	if (n == 0)
		return (1);
	count = 0;
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

void	fill(char *str, int n, int count)
{
	str[count--] = '\0';
	while (count >= 0)
	{
		str[count--] = n % 10 + '0';
		n = n / 10;
	}
}

void	fill2(char *str, int n, int count)
{
	n = -n;
	str[count--] = '\0';
	while (count >= 1)
	{
		str[count--] = n % 10 + '0';
		n = n / 10;
	}
	str[0] = '-';
}

char	*ft_itoa(int n)
{
	char	*str;
	int		count;

	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	else if (n > 0)
	{
		count = count_number(n);
		str = malloc(sizeof(char) * (count + 1));
		if (!str)
			return (NULL);
		fill(str, n, count);
	}
	else
	{
		count = count_number(n) + 1;
		str = malloc(sizeof(char) * (count + 1));
		if (!str)
			return (NULL);
		fill2(str, n, count);
	}
	return (str);
}
