/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_strings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfevrier <tfevrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:34:02 by tfevrier          #+#    #+#             */
/*   Updated: 2019/12/17 16:34:07 by tfevrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_strcmp(char *s1, char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

int		ft_atoi_easy(char *str)
{
	int		nb;

	nb = 0;
	while (*str <= ' ')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		nb = nb * 10 + *str - '0';
		str++;
	}
	return (nb);
}

char	*ft_trim(char *str)
{
	int		i;

	i = ft_strlen(str) - 1;
	while (i >= 0 && str[i] <= ' ')
		i--;
	str[i + 1] = '\0';
	return (str);
}

char	*ft_remove_spaces(char *str)
{
	int		i;
	int		nb_spaces;
	char	*new_str;

	nb_spaces = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] <= ' ')
			nb_spaces++;
		i++;
	}
	if (!(new_str = malloc((ft_strlen(str) - nb_spaces + 1) * sizeof(char))))
		return (NULL);
	i = 0;
	while (*str)
	{
		if (*str > ' ')
			new_str[i++] = *str;
		str++;
	}
	new_str[i] = '\0';
	return (new_str);
}
