/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blorin <blorin@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 15:04:35 by blorin            #+#    #+#             */
/*   Updated: 2020/02/22 15:16:58 by blorin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		*put_pixel(t_storage *ptr, int start, int lineheight, int *img)
{
	int id;

	id = 0;
	if (ptr->tab[ptr->mapy][ptr->mapx] == 3 && ptr->move.door == 0)
		id = 4;
	else if (ptr->ray.side == 0 && ptr->ray.raydirx < 0)
		id = 0;
	else if (ptr->ray.side == 0)
		id = 1;
	else if (ptr->ray.side == 1 && ptr->ray.raydiry < 0)
		id = 2;
	else if (ptr->ray.side == 1)
		id = 3;
	if (ptr->ray.x < ptr->resox && start < ptr->resoy)
	{
		ptr->texty = abs((((start * 256 - ptr->resoy * 128 + lineheight *
		128) * ptr->text[id].y) / lineheight) / 256);
		img[start * ptr->resox + ptr->ray.x] = ptr->text[id].data
		[(ptr->texty % 64 * ptr->text[id].sizeline + ptr->textx %
		ptr->text[id].x * ptr->text[id].bpp / 8) / 4];
	}
	return (img);
}

int		*draw_wall(t_storage *ptr, int start, int lineheight, int *img)
{
	if (ptr->ray.side == 0)
		ptr->wallx = ptr->ray.rayy + ptr->ray.walldist * ptr->ray.raydiry;
	else
		ptr->wallx = ptr->ray.rayx + ptr->ray.walldist * ptr->ray.raydirx;
	ptr->textx = (int)(ptr->wallx * (double)(64));
	if (ptr->ray.side == 0 && ptr->ray.raydirx > 0)
		ptr->textx = 64 - ptr->textx - 1;
	if (ptr->ray.side == 1 && ptr->ray.raydiry < 0)
		ptr->textx = 64 - ptr->textx - 1;
	ptr->textx = abs(ptr->textx);
	while (start++ < ptr->ray.drawend)
		img = put_pixel(ptr, start, lineheight, img);
	return (img);
}

int		ft_strcpy_p(t_storage *ptr, int i, char *line)
{
	int k;

	k = 0;
	while (line[k])
	{
		ptr->map[i] = line[k];
		i++;
		k++;
	}
	ptr->map[i] = '\0';
	return (i);
}
