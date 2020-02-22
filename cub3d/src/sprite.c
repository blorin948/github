/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blorin <blorin@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 23:58:34 by blorin            #+#    #+#             */
/*   Updated: 2020/02/22 15:14:52 by blorin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	sort_sprite(t_storage *ptr, int count, double tmpy)
{
	int		distance;
	double	tmpx;
	int		dist;

	count = 0;
	while (count < ptr->spritec - 1)
	{
		distance = ((ptr->posx - ptr->spritet[count].x) * (ptr->posx -
		ptr->spritet[count].x) + (ptr->posy -
		ptr->spritet[count].y) * (ptr->posy - ptr->spritet[count].y));
		dist = ((ptr->posx - ptr->spritet[count + 1].x) * (ptr->posx -
		ptr->spritet[count + 1].x) + (ptr->posy - ptr->spritet[count + 1].y)
		* (ptr->posy - ptr->spritet[count + 1].y));
		if (distance > dist)
		{
			tmpy = ptr->spritet[count + 1].y;
			tmpx = ptr->spritet[count + 1].x;
			ptr->spritet[count + 1].x = ptr->spritet[count].x;
			ptr->spritet[count + 1].y = ptr->spritet[count].y;
			ptr->spritet[count].x = tmpx;
			ptr->spritet[count].y = tmpy;
			count = 0;
		}
		count++;
	}
}

void	sprite2(t_storage *ptr)
{
	ptr->sprite.spritex = ptr->spritet[ptr->sprite.count].x - ptr->posx;
	ptr->sprite.spritey = ptr->spritet[ptr->sprite.count].y - ptr->posy;
	ptr->sprite.invdet = 1.0 / (ptr->planex * ptr->diry - ptr->dirx *
			ptr->planey);
	ptr->sprite.transfox = ptr->sprite.invdet * (-ptr->diry *
			ptr->sprite.spritex - -ptr->dirx * ptr->sprite.spritey);
	ptr->sprite.transfoy = ptr->sprite.invdet * (-ptr->planey *
			ptr->sprite.spritex + ptr->planex * ptr->sprite.spritey);
	ptr->sprite.spritescreenx = (int)((ptr->resox / 2) * (1 +
			ptr->sprite.transfox / ptr->sprite.transfoy));
	ptr->sprite.spriteheight = abs((int)(ptr->resoy / (ptr->sprite.transfoy)));
	ptr->sprite.drawstarty = -ptr->sprite.spriteheight / 2 + ptr->resoy / 2;
	if (ptr->sprite.drawstarty < 0)
		ptr->sprite.drawstarty = 0;
	ptr->sprite.drawendy = ptr->sprite.spriteheight / 2 + ptr->resoy / 2;
	if (ptr->sprite.drawendy >= ptr->resoy)
		ptr->sprite.drawendy = ptr->resoy - 1;
}

void	sprite3(t_storage *ptr)
{
	ptr->sprite.spritewidth = abs((int)(ptr->resoy / (ptr->sprite.transfoy)));
	ptr->sprite.drawstartx = (-ptr->sprite.spritewidth /
	2 + ptr->sprite.spritescreenx);
	if (ptr->sprite.drawstartx < 0)
		ptr->sprite.drawstartx = 0;
	ptr->sprite.drawendx = ptr->sprite.spritewidth /
		2 + ptr->sprite.spritescreenx;
	if (ptr->sprite.drawendx >= ptr->resox)
		ptr->sprite.drawendx = ptr->resox - 1;
	ptr->sprite.stripe = ptr->sprite.drawstartx;
}

int		*sprite4(t_storage *ptr, int *img)
{
	ptr->sprite.texx = (256 * (ptr->sprite.stripe - (-ptr->sprite.spritewidth /
	2 + ptr->sprite.spritescreenx)) * ptr->text[5].x /
	ptr->sprite.spritewidth) / 256;
	if (ptr->sprite.transfoy > 0 && ptr->sprite.stripe > 0 &&
	ptr->sprite.stripe <
	ptr->resox && ptr->sprite.transfoy < ptr->buffer[ptr->sprite.stripe])
	{
		ptr->sprite.y = ptr->sprite.drawstarty;
		while (ptr->sprite.y++ < ptr->sprite.drawendy)
		{
			ptr->sprite.size = (ptr->sprite.y) * 256 - ptr->resoy * 128
			+ ptr->sprite.spriteheight * 128;
			ptr->sprite.texy = ((ptr->sprite.size * ptr->text[5].y) /
			ptr->sprite.spriteheight) / 256;
			if (ptr->text[5].data[ptr->text[5].x * ptr->sprite.texy
			+ ptr->sprite.texx] > 1)
				img[ptr->sprite.y * ptr->resox + ptr->sprite.stripe] = ptr->
				text[5].data[ptr->text[5].x *
				ptr->sprite.texy + ptr->sprite.texx];
		}
	}
	return (img);
}

int		*sprite(t_storage *ptr, int *img)
{
	int		count;
	double	tmpy;

	tmpy = 0;
	count = 0;
	if (ptr->spritec == 0)
		return (img);
	ptr->sprite.count = ptr->spritec - 1;
	sort_sprite(ptr, count, tmpy);
	while (ptr->sprite.count >= 0)
	{
		sprite2(ptr);
		sprite3(ptr);
		while (ptr->sprite.stripe++ < ptr->sprite.drawendx)
			img = sprite4(ptr, img);
		ptr->sprite.count--;
	}
	return (img);
}
