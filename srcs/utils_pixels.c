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

void	set_screen_pixel(t_img screen, int i, int j, int color)
{
	char	*ptr;
	char	r;
	char	g;
	char	b;

	r = color >> 16;
	g = (color % 65536) >> 8;
	b = color % 256;
	ptr = screen.data + j * screen.size_line + i * (screen.bpp >> 3);
	*ptr = (screen.endian) ? r : b;
	*(ptr + 1) = g;
	*(ptr + 2) = (screen.endian) ? b : r;
}

int		get_screen_pixel(t_img screen, int i, int j)
{
	char	*ptr;
	char	r;
	char	g;
	char	b;

	ptr = screen.data + i * screen.size_line + j * (screen.bpp >> 3);
	r = (screen.endian) ? *ptr : *(ptr + 2);
	g = (*ptr + 1);
	b = (screen.endian) ? *(ptr + 2) : *ptr;
	return ((r << 16) + (g << 8) + b);
}

int		get_tex_color(t_img tex, double u, double v)
{
	char	*ptr;
	char	r;
	char	g;
	char	b;

	ptr = tex.data + (int)(v * tex.height) * tex.size_line
		+ (int)(u * tex.width) * (tex.bpp >> 3);
	r = tex.endian ? *ptr : *(ptr + 2);
	g = *(ptr + 1);
	b = tex.endian ? *(ptr + 2) : *ptr;
	return ((r << 16) + (g << 8) + b);
}
