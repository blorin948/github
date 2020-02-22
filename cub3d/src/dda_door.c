/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_door.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blorin <blorin@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 23:28:06 by blorin            #+#    #+#             */
/*   Updated: 2020/02/22 15:16:53 by blorin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	sort_door(t_storage *ptr, double tmpx, double tmpy)
{
	int		distance;
	int		dist;
	int		count;

	count = 0;
	while (count < ptr->doorc - 1)
	{
		distance = ((ptr->posx - ptr->doorposx[count]) * (ptr->posx -
		ptr->doorposx[count]) + (ptr->posy -
		ptr->doorposy[count]) * (ptr->posy - ptr->doorposy[count]));
		dist = ((ptr->posx - ptr->doorposx[count + 1]) * (ptr->posx -
		ptr->doorposx[count + 1]) + (ptr->posy - ptr->doorposy[count + 1])
		* (ptr->posy - ptr->doorposy[count + 1]));
		if (distance > dist)
		{
			tmpy = ptr->doorposy[count + 1];
			tmpx = ptr->doorposx[count + 1];
			ptr->doorposx[count + 1] = ptr->doorposx[count];
			ptr->doorposy[count + 1] = ptr->doorposy[count];
			ptr->doorposx[count] = tmpx;
			ptr->doorposy[count] = tmpy;
			count = 0;
		}
		count++;
	}
}

void	dda(t_storage *ptr)
{
	ptr->ray.deltadistx = sqrt(1 + (ptr->ray.raydiry * ptr->ray.raydiry) /
	(ptr->ray.raydirx * ptr->ray.raydirx));
	ptr->ray.deltadisty = sqrt(1 + (ptr->ray.raydirx * ptr->ray.raydirx) /
	(ptr->ray.raydiry * ptr->ray.raydiry));
	if (ptr->ray.raydirx < 0 && (ptr->ray.stepx = -1))
		ptr->ray.sidedistx = (ptr->ray.rayx - ptr->mapx) * ptr->ray.deltadistx;
	else
	{
		ptr->ray.stepx = 1;
		ptr->ray.sidedistx = (ptr->mapx + 1.0 - ptr->ray.rayx) *
		ptr->ray.deltadistx;
	}
	if (ptr->ray.raydiry < 0)
	{
		ptr->ray.stepy = -1;
		ptr->ray.sidedisty = (ptr->ray.rayy - ptr->mapy) *
		ptr->ray.deltadisty;
	}
	else
	{
		ptr->ray.stepy = 1;
		ptr->ray.sidedisty = (ptr->mapy + 1.0 - ptr->ray.rayy) *
		ptr->ray.deltadisty;
	}
}

void	dda2(t_storage *ptr)
{
	ptr->ray.hit = 0;
	while (ptr->ray.hit == 0)
	{
		if (ptr->ray.sidedistx < ptr->ray.sidedisty)
		{
			ptr->ray.sidedistx += ptr->ray.deltadistx;
			ptr->mapx += ptr->ray.stepx;
			ptr->ray.side = 0;
		}
		else
		{
			ptr->ray.sidedisty += ptr->ray.deltadisty;
			ptr->mapy += ptr->ray.stepy;
			ptr->ray.side = 1;
		}
		if (ptr->tab[ptr->mapy][ptr->mapx] == 1 || ((ptr->tab[ptr->mapy][ptr->
		mapx] == 4 && ptr->move.door == 0) || (ptr->tab[ptr->mapy][ptr->mapx]
		== 3 && ptr->move.door == 0)))
		{
			ptr->ray.hit = 1;
		}
	}
}
