/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshehab <hshehab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:53:46 by hshehab           #+#    #+#             */
/*   Updated: 2024/06/18 15:02:51 by hshehab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	length;

	length = ft_strlen((char *)s);
	if (c == 0)
	{
		return ((char *) &s[length]);
	}
	while (length > 0)
	{
		if (s[length] == (unsigned char)c)
			return ((char *) &s[length]);
		length--;
	}
	if (s[length] == (unsigned char)c)
		return ((char *) &s[length]);
	return (NULL);
}
