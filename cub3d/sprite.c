/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sprite.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: blorin <blorin@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/31 22:54:04 by blorin       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/02 17:46:31 by blorin      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"

void	sort_sprite(t_storage *ptr, int count, double tmpy)
{
	int		distance;
	double	tmpx;
	int		dist;
	
	count = 0;
	while (count < ptr->spritec - 1)
	{
		distance = ((ptr->posx - ptr->spriteposx[count]) * (ptr->posx -
		ptr->spriteposx[count]) + (ptr->posy -
		ptr->spriteposy[count]) * (ptr->posy - ptr->spriteposy[count]));
		dist = ((ptr->posx - ptr->spriteposx[count + 1]) * (ptr->posx -
		ptr->spriteposx[count + 1]) + (ptr->posy - ptr->spriteposy[count + 1])
		* (ptr->posy - ptr->spriteposy[count + 1]));
		if (distance > dist)
		{
			tmpy = ptr->spriteposy[count + 1];
			tmpx = ptr->spriteposx[count + 1];
			ptr->spriteposx[count + 1] = ptr->spriteposx[count];
			ptr->spriteposy[count + 1] = ptr->spriteposy[count];
			ptr->spriteposx[count] = tmpx;
			ptr->spriteposy[count] = tmpy;
			count = 0;
		}
		count++;
	}
}
int		sprite2(t_storage *ptr)
{
	ptr->sprite.spritex = ptr->spriteposx[ptr->sprite.count] - ptr->posx;
	ptr->sprite.spritey = ptr->spriteposy[ptr->sprite.count] - ptr->posy;
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

void	sprite4(t_storage *ptr)
{
	while (ptr->sprite.stripe++ < ptr->sprite.drawendx)
	{
		ptr->sprite.texx = (256 * (ptr->sprite.stripe -
		(-ptr->sprite.spritewidth / 2
		+ ptr->sprite.spritescreenx)) * ptr->texwidth /
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
				ptr->sprite.texy = ((ptr->sprite.size * ptr->texheight) /
				ptr->sprite.spriteheight) / 256;
				if (ptr->text[5].data[ptr->texwidth * ptr->sprite.texy
				+ ptr->sprite.texx] > 100000)
					ptr->t_img.image[ptr->sprite.y * ptr->resox +
					ptr->sprite.stripe] = ptr->text[5].data[ptr->texwidth *
					ptr->sprite.texy + ptr->sprite.texx];
			}
		}
	}
}

int		sprite(t_storage *ptr)
{
	int count;
	double tmpy;
	
	count = 0;
	if (ptr->spritec == 0)
		return (0);
	ptr->sprite.count = ptr->spritec;
	sort_sprite(ptr, count, tmpy);
	while (ptr->sprite.count >= 0)
	{
		sprite2(ptr);
		sprite3(ptr);
		sprite4(ptr);
		ptr->sprite.count--;
	}
	return (1);
}
