/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfevrier <tfevrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 15:18:31 by tfevrier          #+#    #+#             */
/*   Updated: 2019/10/18 11:31:19 by tfevrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_strlen(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int		ft_indexof(char *str, char c)
{
	int	i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_strdup(char *str)
{
	char	*dup;
	int		i;

	if (!(dup = (char *)malloc((ft_strlen(str) + 1) * sizeof(char))))
		return (NULL);
	i = 0;
	while (str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!(str = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1)
								* sizeof(char))))
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

char	*ft_substr(char *str, int start, int len)
{
	int		size;
	char	*substr;
	int		i;

	size = (start + len > ft_strlen(str)) ? ft_strlen(str) - start : len;
	if (!(substr = (char *)malloc((size + 1) * sizeof(char))))
		return (NULL);
	i = 0;
	while (i < size)
	{
		substr[i] = str[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
