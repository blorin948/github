/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blorin <blorin@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 23:59:12 by blorin            #+#    #+#             */
/*   Updated: 2020/02/22 15:19:20 by blorin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ray_cast_skybox(t_storage *ptr)
{
	if (ptr->move.moveright == 1)
		ptr->mv += 55;
	if (ptr->move.moveleft == 1)
		ptr->mv -= 55;
	if (ptr->mv > ptr->t_img.imgx)
		ptr->mv = 0;
	if (ptr->mv < 0)
		ptr->mv = ptr->t_img.imgx;
	if (ptr->move.moveup == 1)
		ptr->mvfront += 45;
	if (ptr->move.movedown == 1)
		ptr->mvfront -= 45;
	if (ptr->mvfront > ptr->t_img.imgsoly)
		ptr->mvfront = 0;
	if (ptr->mvfront < 0)
		ptr->mvfront = ptr->t_img.imgsoly;
}

int		*ray_cast2(t_storage *ptr, int *img)
{
	int i;

	i = 0;
	if (ptr->ray.drawstart < 0)
		ptr->ray.drawstart = 0;
	ptr->ray.drawend = ptr->ray.lineheight / 2 + ptr->resoy / 2;
	if (ptr->ray.drawend >= ptr->resoy)
		ptr->ray.drawend = ptr->resoy - 1;
	while (i < ptr->ray.drawstart)
	{
		if (ptr->che.sky > 0)
			img[i * ptr->resox + ptr->ray.x] =
			ptr->t_img.text[i * ptr->t_img.imgx + (ptr->ray.x + ptr->mv)];
		else
			img[i * ptr->resox + ptr->ray.x] = ptr->plaf;
		i++;
	}
	img = draw_wall(ptr, ptr->ray.drawstart, ptr->ray.lineheight, img);
	return (img);
}

void	ray_cast3(t_storage *ptr, int *img)
{
	int *tmp;

	img = sprite(ptr, img);
	if (!(ptr->resox < 15 || ptr->resoy < 15))
		img = image(ptr, img);
	mlx_put_image_to_window(ptr->mlx_ptr, ptr->win_ptr, ptr->t_img.img_ptr,
	0, 0);
	if (ptr->save > 0)
	{
		save_bmp_file(ptr, img);
		ft_exit(ptr);
	}
	tmp = img;
	mlx_destroy_image(ptr->mlx_ptr, ptr->t_img.img_ptr);
}

void	ray_cast(t_storage *ptr)
{
	int *img;

	ptr->t_img.img_ptr = mlx_new_image(ptr->mlx_ptr, ptr->resox, ptr->resoy);
	img = (int*)mlx_get_data_addr(ptr->t_img.img_ptr,
	&ptr->t_img.bpp, &ptr->t_img.size_line, &ptr->t_img.endian);
	ptr->ray.x = -1;
	ray_cast_skybox(ptr);
	while (++ptr->ray.x < ptr->resox)
	{
		ray_cast_init(ptr, ptr->ray.x);
		ptr->ray.lineheight = (int)(ptr->resoy / ptr->ray.walldist);
		ptr->ray.drawstart = -ptr->ray.lineheight / 2 + ptr->resoy / 2;
		img = ray_cast2(ptr, img);
		while (ptr->ray.drawend < ptr->resoy)
		{
			img[ptr->ray.drawend * ptr->resox +
			ptr->ray.x] = ptr->sol;
			ptr->ray.drawend++;
		}
		ptr->buffer[ptr->ray.x] = ptr->ray.walldist;
	}
	ray_cast3(ptr, img);
}

void	ray_cast_init(t_storage *ptr, int x)
{
	ptr->ray.camx = 2 * x / (double)(ptr->resox) - 1;
	ptr->ray.rayx = ptr->posx;
	ptr->ray.rayy = ptr->posy;
	ptr->ray.raydirx = ptr->dirx - ptr->planex * ptr->ray.camx;
	ptr->ray.raydiry = ptr->diry - ptr->planey * ptr->ray.camx;
	ptr->mapx = (int)ptr->ray.rayx;
	ptr->mapy = (int)ptr->ray.rayy;
	dda(ptr);
	dda2(ptr);
	if (ptr->ray.side == 0)
		ptr->ray.walldist = (ptr->mapx - ptr->ray.rayx +
		(1 - ptr->ray.stepx) / 2) / ptr->ray.raydirx;
	else
		ptr->ray.walldist = (ptr->mapy - ptr->ray.rayy +
		(1 - ptr->ray.stepy) / 2) / ptr->ray.raydiry;
}
