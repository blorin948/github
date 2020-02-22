/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blorin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 23:29:33 by blorin            #+#    #+#             */
/*   Updated: 2020/02/21 23:58:23 by blorin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	move_up_down(t_storage *ptr)
{
	if (ptr->move.moveup == 1)
	{
		if (ptr->tab[(int)ptr->posy][(int)(ptr->posx + ptr->dirx * ptr->move.
		mspeed * 1.5)] == 0 || (ptr->tab[(int)ptr->posy][(int)(ptr->posx +
		ptr->dirx * (ptr->move.mspeed * 1.5))] == 3 && ptr->move.door == 1))
			ptr->posx += ptr->dirx * ptr->move.mspeed;
		if (ptr->tab[(int)(ptr->posy + ptr->diry * ptr->move.mspeed *
		1.5)][(int)(ptr->posx)] == 0 || (ptr->tab[(int)(ptr->posy +
		ptr->diry * (ptr->move.mspeed * 1.5))][(int)(ptr->posx)]
		== 3 && ptr->move.door == 1))
			ptr->posy += ptr->diry * ptr->move.mspeed;
	}
	if (ptr->move.movedown == 1)
	{
		if (ptr->tab[(int)(ptr->posy)][(int)(ptr->posx - ptr->dirx *
		ptr->move.mspeed * 1.5)] == 0 || (ptr->tab[(int)(ptr->posy)]
		[(int)(ptr->posx - ptr->dirx * ptr->move.mspeed * 1.5)] == 3
		&& ptr->move.door == 1))
			ptr->posx -= ptr->dirx * ptr->move.mspeed;
		if (ptr->tab[(int)(ptr->posy - ptr->diry * ptr->move.mspeed *
		1.5)][(int)(ptr->posx)] == 0 || (ptr->tab[(int)(ptr->posy -
		ptr->diry * ptr->move.mspeed * 1.5)][(int)(ptr->posx)] == 3
		&& ptr->move.door == 1))
			ptr->posy -= ptr->diry * ptr->move.mspeed;
	}
}

void	move_left(t_storage *ptr)
{
	if (ptr->move.moveleft == 1)
	{
		ptr->move.olddirx = ptr->dirx;
		ptr->dirx = ptr->dirx * cos(-ptr->move.rspeed) - ptr->diry
		* sin(-ptr->move.rspeed);
		ptr->diry = ptr->move.olddirx * sin(-ptr->move.rspeed) +
		ptr->diry * cos(-ptr->move.rspeed);
		ptr->move.oldplanex = ptr->planex;
		ptr->planex = ptr->planex * cos(-ptr->move.rspeed) - ptr->planey
		* sin(-ptr->move.rspeed);
		ptr->planey = ptr->move.oldplanex * sin(-ptr->move.rspeed) +
		ptr->planey * cos(-ptr->move.rspeed);
	}
}

void	move_cam_side2(t_storage *ptr, double vx, double vy)
{
	if (ptr->move.movecamleft == 1)
	{
		if (ptr->tab[(int)(ptr->posy)][(int)(ptr->posx - vx * ptr->move.mspeed
		* 1.5)] == 0 || (ptr->tab[(int)(ptr->posy)][(int)(ptr->posx - vx *
		ptr->move.mspeed * 1.5)] == 3 && ptr->move.door == 1))
			ptr->posx -= vx * ptr->move.mspeed;
		if (ptr->tab[(int)(ptr->posy - vy * ptr->move.mspeed * 1.5)][(int)(ptr->
		posx)] == 0 || (ptr->tab[(int)(ptr->posy - vy * ptr->move.mspeed * 1.5)]
		[(int)(ptr->posx)] == 3 && ptr->move.door == 1))
			ptr->posy -= vy * ptr->move.mspeed;
	}
}

void	move_cam_side(t_storage *ptr)
{
	double vx;
	double vy;

	vx = (cos(M_PI_2) * ptr->dirx - sin(M_PI_2) * ptr->diry);
	vy = (cos(M_PI_2) * ptr->diry + sin(M_PI_2) * ptr->dirx);
	if (ptr->move.movecamright == 1)
	{
		if (ptr->tab[(int)(ptr->posy)][(int)(ptr->posx + vx * ptr->move.mspeed
		* 1.5)] == 0 || (ptr->tab[(int)(ptr->posy)][(int)(ptr->posx + vx *
		ptr->move.mspeed * 1.5)] == 3 && ptr->move.door == 1))
			ptr->posx += vx * ptr->move.mspeed;
		if (ptr->tab[(int)(ptr->posy + vy * ptr->move.mspeed * 1.5)][(int)(ptr->
		posx)] == 0 || (ptr->tab[(int)(ptr->posy + vy * ptr->move.mspeed *
		1.5)][(int)(ptr->posx)] == 3 && ptr->move.door == 1))
			ptr->posy += vy * ptr->move.mspeed;
	}
	move_cam_side2(ptr, vx, vy);
}

int		move_side(t_storage *ptr)
{
	if (ptr->move.moveright == 1)
	{
		ptr->move.olddirx = ptr->dirx;
		ptr->dirx = ptr->dirx * cos(ptr->move.rspeed) -
		ptr->diry * sin(ptr->move.rspeed);
		ptr->diry = ptr->move.olddirx * sin(ptr->move.rspeed) +
		ptr->diry * cos(ptr->move.rspeed);
		ptr->move.oldplanex = ptr->planex;
		ptr->planex = ptr->planex * cos(ptr->move.rspeed) - ptr->planey
		* sin(ptr->move.rspeed);
		ptr->planey = ptr->move.oldplanex * sin(ptr->move.rspeed) +
		ptr->planey * cos(ptr->move.rspeed);
	}
	move_cam_side(ptr);
	move_left(ptr);
	move_up_down(ptr);
	ray_cast(ptr);
	return (0);
}
