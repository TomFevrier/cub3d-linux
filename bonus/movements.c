/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfevrier <tfevrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 15:17:58 by tfevrier          #+#    #+#             */
/*   Updated: 2020/04/11 14:54:21 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_collisions(t_world *world, double dx, double dy)
{
	int		alea;

	if (world->map[(int)(world->pos[0] + dx)][(int)(world->pos[1] + dy)] != 1)
	{
		world->pos[0] += dx;
		world->pos[1] += dy;
		if (world->map[(int)world->pos[0]][(int)world->pos[1]] == 0)
			world->is_teleporting = FALSE;
		else if (world->map[(int)world->pos[0]][(int)world->pos[1]] == 2)
			world->life--;
		else if (world->map[(int)world->pos[0]][(int)world->pos[1]] == 3
			&& !world->is_teleporting)
		{
			world->is_teleporting = TRUE;
			alea = rand() % world->nb_sprites;
			while (!world->sprites[alea].is_portal
				|| (world->sprites[alea].pos[0] == (int)world->pos[0]
				&& world->sprites[alea].pos[1] == (int)world->pos[1]))
				alea = rand() % world->nb_sprites;
			world->pos[0] = world->sprites[alea].pos[0];
			world->pos[1] = world->sprites[alea].pos[1];
		}
	}
}

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
	handle_collisions(world, dx, dy);
	return (TRUE);
}

t_bool	rotate(t_world *world)
{
	double	tmp;
	double	angle;

	if (!world->ctrls.right && !world->ctrls.left)
		return (FALSE);
	angle = (world->ctrls.left) ? M_PI / 50 : -M_PI / 50;
	tmp = world->dir[0];
	world->dir[0] = tmp * cos(angle) - world->dir[1] * sin(angle);
	world->dir[1] = tmp * sin(angle) + world->dir[1] * cos(angle);
	tmp = world->cam_plane[0];
	world->cam_plane[0] = tmp * cos(angle) - world->cam_plane[1] * sin(angle);
	world->cam_plane[1] = tmp * sin(angle) + world->cam_plane[1] * cos(angle);
	return (TRUE);
}

t_bool	jump(t_world *world)
{
	static double gravity = -0.0225;

	if (!world->ctrls.up && world->jump_coeff == 0)
		return (FALSE);
	if (world->ctrls.up && world->jump_coeff == 0)
		world->jump_speed = 0.2;
	world->jump_coeff += world->jump_speed;
	world->jump_speed += gravity;
	if (world->jump_coeff < 0)
		world->jump_coeff = 0;
	return (TRUE);
}

t_bool	shoot(t_world *world)
{
	int		i;

	if (!world->ctrls.space)
		return (FALSE);
	i = world->nb_sprites - 1;
	while (i >= 0)
	{
		if (world->sprites[i].killable)
		{
			world->sprites[i].destroyed = TRUE;
			world->map[world->sprites[i].pos[0]][world->sprites[i].pos[1]] = 0;
			break ;
		}
		i--;
	}
	system("ffplay ./music/gunshot.mp3 -nodisp -loglevel quiet &");
	return (TRUE);
}
