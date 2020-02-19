/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfevrier <tfevrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 18:14:09 by tfevrier          #+#    #+#             */
/*   Updated: 2019/10/30 12:06:48 by tfevrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		read_line(int fd, char **str)
{
	int		ret;
	char	*buf;
	char	*tmp;

	if (!(buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char))))
		return (-1);
	while ((ret = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (*str)
		{
			tmp = *str;
			*str = ft_strjoin(*str, buf);
			free(tmp);
		}
		else
			*str = ft_strdup(buf);
		if (ft_indexof(*str, '\n') > 0)
			break ;
	}
	free(buf);
	return (ret);
}

int		get_next_line(int fd, char **line)
{
	static char		*str;
	int				i;
	char			*tmp;

	if (fd < 0 || !line || read(fd, str, 0) < 0)
		return (-1);
	if (!(ft_indexof(str, '\n') > 0))
		read_line(fd, &str);
	if (!str)
	{
		*line = ft_strdup("");
		return (0);
	}
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	*line = ft_substr(str, 0, i);
	tmp = (str[i] == '\n') ? ft_strdup(str + i + 1) : NULL;
	free(str);
	str = tmp;
	if (!str)
		return (0);
	return (1);
}
