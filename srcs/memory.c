/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfevrier <tfevrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 15:24:55 by tfevrier          #+#    #+#             */
/*   Updated: 2019/12/04 15:24:56 by tfevrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*ft_calloc(int count, int size)
{
	unsigned char	*ptr;
	int				i;

	if (!(ptr = malloc(count * size)))
		return (NULL);
	i = 0;
	while (i < count * size)
		*(ptr + i++) = 0;
	return ((void *)ptr);
}

void	free_textures(t_world *world)
{
	t_side	side;

	side = N;
	while (side <= E)
	{
		if (world->textures[side].filename)
			free(world->textures[side].filename);
		if (world->textures[side].data)
			mlx_destroy_image(world->mlx.ptr, world->textures[side].ptr);
		side++;
	}
	if (world->texture_sprite.filename)
		free(world->texture_sprite.filename);
	if (world->texture_sprite.data)
		mlx_destroy_image(world->mlx.ptr, world->texture_sprite.ptr);
}

void	free_world(t_world *world)
{
	int		i;

	if (world->map)
	{
		i = 0;
		while (i < world->map_height)
			free(world->map[i++]);
		free(world->map);
	}
	if (world->sprites)
		free(world->sprites);
	if (world->depth_buffer)
		free(world->depth_buffer);
	if (world->screen.data)
		mlx_destroy_image(world->mlx.ptr, world->screen.ptr);
	free_textures(world);
	if (world->mlx.win)
		mlx_destroy_window(world->mlx.ptr, world->mlx.win);
	free(world);
}
