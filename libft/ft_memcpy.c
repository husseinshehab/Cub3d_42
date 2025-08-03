/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshehab <hshehab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 11:53:40 by hshehab           #+#    #+#             */
/*   Updated: 2024/06/16 12:31:24 by hshehab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*p;
	unsigned char	*k;
	size_t			i;

	p = (unsigned char *)src;
	k = (unsigned char *)dest;
	i = 0;
	while (i < n)
	{
		k[i] = p[i];
		i++;
	}
	return (dest);
}
