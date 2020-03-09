/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfevrier <tfevrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:34:02 by tfevrier          #+#    #+#             */
/*   Updated: 2019/12/17 16:34:07 by tfevrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_line_textured(t_world *world, int i, t_texdata data)
{
	int		j;
	int		start;
	int		end;
	t_img	texture;
	int		color;

	start = world->scr_height / 2 - data.line_height / 2;
	end = world->scr_height / 2 + data.line_height / 2;
	texture = world->textures[data.side];
	j = 0;
	while (j < (start < 0 ? 0 : start))
		set_screen_pixel(world->screen, i, j++, world->color_ceiling);
	while (j < (end >= world->scr_height ? world->scr_height - 1 : end))
	{
		color = get_tex_color(texture, data.wall_x,
			((j - start) * 1.0) / (end - start));
		set_screen_pixel(world->screen, i, j++, color);
	}
	while (j < world->scr_height)
		set_screen_pixel(world->screen, i, j++, world->color_floor);
}

t_dda	init_vars(t_world *world, double ray[2])
{
	t_dda	vars;

	vars.delta_dist[0] = fabs(1.0 / ray[0]);
	vars.delta_dist[1] = fabs(1.0 / ray[1]);
	vars.map_pos[0] = floor(world->pos[0]);
	vars.map_pos[1] = floor(world->pos[1]);
	vars.step[0] = (ray[0] < 0) ? -1 : 1;
	vars.step[1] = (ray[1] < 0) ? -1 : 1;
	vars.side_dist[0] = (ray[0] < 0)
		? (world->pos[0] - vars.map_pos[0]) * vars.delta_dist[0]
		: (vars.map_pos[0] + 1.0 - world->pos[0]) * vars.delta_dist[0];
	vars.side_dist[1] = (ray[1] < 0)
		? (world->pos[1] - vars.map_pos[1]) * vars.delta_dist[1]
		: (vars.map_pos[1] + 1.0 - world->pos[1]) * vars.delta_dist[1];
	return (vars);
}

t_bool	check_hit(t_world *world, t_dda *vars, t_texdata *data, double ray[2])
{
	if (vars->side_dist[0] < vars->side_dist[1])
	{
		vars->side_dist[0] += vars->delta_dist[0];
		vars->map_pos[0] += vars->step[0];
		data->side = ray[0] > 0 ? N : S;
	}
	else
	{
		vars->side_dist[1] += vars->delta_dist[1];
		vars->map_pos[1] += vars->step[1];
		data->side = ray[1] > 0 ? E : W;
	}
	return (world->map[vars->map_pos[0]][vars->map_pos[1]] == 1);
}

void	run_dda(t_world *world, int i, double ray[2])
{
	t_dda		vars;
	t_bool		hit;
	t_texdata	data;

	vars = init_vars(world, ray);
	hit = FALSE;
	while (!hit)
		hit = check_hit(world, &vars, &data, ray);
	data.wall_dist = (data.side == N || data.side == S)
		? (vars.map_pos[0] - world->pos[0] + (1 - vars.step[0]) / 2) / ray[0]
		: (vars.map_pos[1] - world->pos[1] + (1 - vars.step[1]) / 2) / ray[1];
	world->depth_buffer[i] = data.wall_dist;
	data.wall_x = (data.side == N || data.side == S)
		? world->pos[1] + data.wall_dist * ray[1]
		: world->pos[0] + data.wall_dist * ray[0];
	data.wall_x -= floor(data.wall_x);
	data.line_height = (data.wall_dist > 0)
		? world->scr_height / data.wall_dist
		: 2147483647;
	draw_line_textured(world, i, data);
}
