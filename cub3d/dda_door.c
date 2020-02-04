/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   dda_door.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: blorin <blorin@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/03 00:19:30 by blorin       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/03 00:25:30 by blorin      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"

void	find_door(t_storage *ptr, int *a, int *o)
{
	double tmpy = 0;
	double tmpx = 0;
	int i = 0;
	ptr->realdoory = 20;
	ptr->realdoorx = 20;
	while (i < ptr->doorc)
	{
		tmpx = ptr->posx - (double)ptr->doorposx[i];
		tmpy = ptr->posy - (double)ptr->doorposy[i];
		if (fabs(tmpy) < abs(ptr->realdoory))
		{
			*a = *a + 1;
			ptr->realdoory = tmpy;
		}
		if (fabs(tmpx) < abs(ptr->realdoorx))
		{
			*o = *o + 1;
			ptr->realdoorx = tmpx;
		}
		i++;
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
		ptr->ray.sidedisty = (ptr->ray.rayy - ptr->mapY) *
        ptr->ray.deltadisty;
	}
	else
	{
		ptr->ray.stepy = 1;
		ptr->ray.sidedisty = (ptr->mapY + 1.0 - ptr->ray.rayy) *
        ptr->ray.deltadisty;
	}
}

void	dda2(t_storage *ptr)
{
	ptr->isdoor = 0;
	ptr->ray.hit = 0;
	double distX =0;
	static int i = 0;
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
			ptr->mapY += ptr->ray.stepy;
			ptr->ray.side = 1;
		}
		if (ptr->tab[ptr->mapY][ptr->mapx] == 1 || ((ptr->tab[ptr->mapY][ptr->
        mapx]== 4 && ptr->move.door == 0) || (ptr->tab[ptr->mapY][ptr->mapx] == 3 &&
        ptr->move.door == 0)))
		{
			ptr->ray.hit = 1;
		}
	}
}