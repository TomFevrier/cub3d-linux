/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pixels.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfevrier <tfevrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:34:02 by tfevrier          #+#    #+#             */
/*   Updated: 2019/12/17 16:34:07 by tfevrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	load_texture(t_world *world, t_img *texture, char *filename)
{
	if (!(texture->ptr = mlx_xpm_file_to_image(world->mlx.ptr,
		filename, &texture->width, &texture->height)))
		return (FALSE);
	if (!(texture->data = mlx_get_data_addr(texture->ptr, &texture->bpp,
		&texture->size_line, &texture->endian)))
		return (FALSE);
	return (TRUE);
}

void	load_textures(t_world *world)
{
	t_side	side;

	side = N;
	while (side <= E)
	{
		load_texture(world, &(world->textures[side]),
			world->textures[side].filename);
		side++;
	}
	load_texture(world, &(world->texture_sprite),
		world->texture_sprite.filename);
	load_texture(world, &(world->texture_sky), world->texture_sky.filename);
	load_texture(world, &(world->texture_floor), world->texture_floor.filename);
	load_texture(world, &(world->texture_portal),
		world->texture_portal.filename);
	load_texture(world, &(world->textures_gun[0]), "./sprites/gun.xpm");
	load_texture(world, &(world->textures_gun[1]), "./sprites/gun_shoot.xpm");
	if (world->error)
		quit(world, ERROR);
}

void	set_screen_pixel(t_img screen, int i, int j, int color)
{
	char			*ptr;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	r = (unsigned char)(color >> 16);
	g = (unsigned char)((color % 65536) >> 8);
	b = (unsigned char)(color % 256);
	ptr = screen.data + j * screen.size_line + i * (screen.bpp >> 3);
	*ptr = (screen.endian ? r : b);
	*(ptr + 1) = g;
	*(ptr + 2) = (screen.endian ? b : r);
}

int		get_screen_pixel(t_img screen, int i, int j)
{
	char			*ptr;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	ptr = screen.data + j * screen.size_line + i * (screen.bpp >> 3);
	r = (unsigned char)(screen.endian ? *ptr : *(ptr + 2));
	g = (unsigned char)(*(ptr + 1));
	b = (unsigned char)(screen.endian ? *(ptr + 2) : *ptr);
	return ((r << 16) + (g << 8) + b);
}

int		get_tex_color(t_img tex, double u, double v, double darken)
{
	char			*ptr;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	darken = (darken > 1) ? 1 : darken;
	darken = (darken < 0.4) ? 0.4 : darken;
	ptr = tex.data + (int)(v * tex.height) * tex.size_line
		+ (int)(u * tex.width) * (tex.bpp >> 3);
	r = darken * (unsigned char)(tex.endian ? *ptr : *(ptr + 2));
	g = darken * (unsigned char)(*(ptr + 1));
	b = darken * (unsigned char)(tex.endian ? *(ptr + 2) : *ptr);
	return ((r << 16) + (g << 8) + b);
}
