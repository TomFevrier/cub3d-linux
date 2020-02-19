/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfevrier <tfevrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 15:17:58 by tfevrier          #+#    #+#             */
/*   Updated: 2019/12/17 15:18:10 by tfevrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	move(t_world *world)
{
	double	dx;
	double	dy;
	double	speed;

	speed = 0.15;
	if (!(world->ctrls.w || world->ctrls.s || world->ctrls.a || world->ctrls.d))
		return (FALSE);
	if (world->ctrls.w || world->ctrls.s)
	{
		dx = world->dir[0] * (world->ctrls.w ? speed : -speed);
		dy = world->dir[1] * (world->ctrls.w ? speed : -speed);
	}
	else
	{
		dx = world->cam_plane[0] * (world->ctrls.d ? speed : -speed);
		dy = world->cam_plane[1] * (world->ctrls.d ? speed : -speed);
	}
	if (world->map[(int)(world->pos[0] + dx)][(int)(world->pos[1] + dy)] != 1)
	{
		world->pos[0] += dx;
		world->pos[1] += dy;
	}
	return (TRUE);
}

t_bool	rotate(t_world *world)
{
	double	tmp;
	double	angle;

	if (!world->ctrls.right && !world->ctrls.left)
		return (FALSE);
	angle = (world->ctrls.left) ? M_PI / 100 : -M_PI / 100;
	tmp = world->dir[0];
	world->dir[0] = tmp * cos(angle) - world->dir[1] * sin(angle);
	world->dir[1] = tmp * sin(angle) + world->dir[1] * cos(angle);
	tmp = world->cam_plane[0];
	world->cam_plane[0] = tmp * cos(angle) - world->cam_plane[1] * sin(angle);
	world->cam_plane[1] = tmp * sin(angle) + world->cam_plane[1] * cos(angle);
	return (TRUE);
}
