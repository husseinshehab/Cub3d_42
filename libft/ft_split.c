/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshehab <hshehab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 15:52:39 by hshehab           #+#    #+#             */
/*   Updated: 2024/06/17 10:38:58 by hshehab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_str(char const *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != '\0')
		{
			count++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
	}
	return (count);
}

int	count_letters(char const *s, char c, int *i)
{
	int	count;

	count = 0;
	while (s[*i] != c && s[*i] != '\0')
	{
		(*i)++;
		count++;
	}
	return (count);
}

void	fill_matrix(char **matrix, char const *s, char c)
{
	int	i;
	int	k;
	int	m;

	i = 0;
	k = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != '\0')
		{
			m = 0;
			while (s[i] != c && s[i] != '\0')
			{
				matrix[k][m] = s[i];
				m++;
				i++;
			}
			matrix[k][m] = '\0';
			k++;
		}
	}
	matrix[k] = '\0';
}

char	**ft_split(char const *s, char c)
{
	char	**matrix;
	int		i;
	int		j;
	int		count_letters1;

	matrix = (char **)malloc(sizeof(char *) * (count_str(s, c) + 1));
	if (!matrix)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && s[i] == c)
			i++;
		if (s[i] != '\0')
		{
			count_letters1 = count_letters(s, c, &i);
			matrix[j] = malloc(sizeof(char) * (count_letters1 + 1));
			if (!matrix[j])
				return (NULL);
			j++;
		}
	}
	fill_matrix(matrix, s, c);
	return (matrix);
}
