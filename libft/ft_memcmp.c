/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshehab <hshehab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 14:59:43 by hshehab           #+#    #+#             */
/*   Updated: 2024/06/17 15:13:19 by hshehab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*p;
	unsigned char	*k;
	size_t			i;

	p = (unsigned char *)s1;
	k = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (p[i] != k[i])
		{
			return ((unsigned char)p[i] - (unsigned char)k[i]);
		}
		i++;
	}
	return (0);
}
