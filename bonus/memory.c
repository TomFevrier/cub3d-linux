/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfevrier <tfevrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 15:24:55 by tfevrier          #+#    #+#             */
/*   Updated: 2020/04/11 14:47:38 by user42           ###   ########.fr       */
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

void	free_textures2(t_world *world)
{
	if (world->texture_sprite.filename)
		free(world->texture_sprite.filename);
	if (world->texture_sprite.data)
		mlx_destroy_image(world->mlx.ptr, world->texture_sprite.ptr);
	if (world->texture_portal.filename)
		free(world->texture_portal.filename);
	if (world->texture_portal.data)
		mlx_destroy_image(world->mlx.ptr, world->texture_portal.ptr);
	if (world->textures_gun[0].filename)
		free(world->textures_gun[0].filename);
	if (world->textures_gun[0].data)
		mlx_destroy_image(world->mlx.ptr, world->textures_gun[0].ptr);
	if (world->textures_gun[1].filename)
		free(world->textures_gun[1].filename);
	if (world->textures_gun[1].data)
		mlx_destroy_image(world->mlx.ptr, world->textures_gun[1].ptr);
}

void	free_textures1(t_world *world)
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
	if (world->texture_floor.filename)
		free(world->texture_floor.filename);
	if (world->texture_floor.data)
		mlx_destroy_image(world->mlx.ptr, world->texture_floor.ptr);
	if (world->texture_sky.filename)
		free(world->texture_sky.filename);
	if (world->texture_sky.data)
		mlx_destroy_image(world->mlx.ptr, world->texture_sky.ptr);
}

void	free_map(t_world *world)
{
	int		i;

	if (world->map)
	{
		i = 0;
		while (i < world->map_height)
			free(world->map[i++]);
		free(world->map);
	}
}

void	free_world(t_world *world)
{
	system("killall ffplay");
	if (world->sprites)
		free(world->sprites);
	if (world->depth_buffer)
		free(world->depth_buffer);
	if (world->music_file)
		free(world->music_file);
	if (world->screen.data)
		mlx_destroy_image(world->mlx.ptr, world->screen.ptr);
	free_textures1(world);
	free_textures2(world);
	free_map(world);
	if (world->mlx.win)
		mlx_destroy_window(world->mlx.ptr, world->mlx.win);
	free(world);
}
