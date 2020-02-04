/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ray_casting.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: blorin <blorin@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/31 21:30:21 by blorin       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/04 19:29:43 by blorin      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"

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
	if (ptr->mvfront > ptr->t_img.imgSoly)
		ptr->mvfront = 0;
	if (ptr->mvfront < 0)
		ptr->mvfront = ptr->t_img.imgSoly;
}

int		ray_cast2(t_storage *ptr, int i)
{
	if (ptr->ray.drawstart < 0)
		ptr->ray.drawstart = 0;
	ptr->ray.drawend = ptr->ray.lineheight / 2 + ptr->resoy / 2;
	if (ptr->ray.drawend >= ptr->resoy)
		ptr->ray.drawend = ptr->resoy - 1;
	while (i < ptr->ray.drawstart)
	{
		if (ptr->che.sky > 0)
			ptr->t_img.image[i * ptr->resox + ptr->ray.x] =
			ptr->t_img.text[i * ptr->t_img.imgx + (ptr->ray.x + ptr->mv)];
		else
			ptr->t_img.image[i * ptr->resox + ptr->ray.x] = ptr->plaf;
		i++;
	}
	draw_wall(ptr, ptr->ray.drawstart, ptr->ray.drawend, ptr->ray.lineheight);
	return (i);
}

void	ray_cast3(t_storage *ptr)
{
    sprite(ptr);
	mlx_put_image_to_window(ptr->mlx_ptr,
	ptr->win_ptr, ptr->t_img.img_ptr, 0, 0);
	image(ptr);
	mlx_destroy_image(ptr->mlx_ptr, ptr->t_img.img_ptr);
}

void	ray_cast(t_storage *ptr)
{
	int i = 0;

	i = 0;
	ptr->t_img.img_ptr = mlx_new_image(ptr->mlx_ptr, ptr->resox, ptr->resoy);
	ptr->t_img.image = (int*)mlx_get_data_addr(ptr->t_img.img_ptr,
	&ptr->t_img.bpp, &ptr->t_img.size_line, &ptr->t_img.endian);
	ptr->ray.x = -1;
	ray_cast_skybox(ptr);
	while (++ptr->ray.x < ptr->resox)
	{
		ray_cast_init(ptr, ptr->ray.x);
		ptr->ray.lineheight = (int)(ptr->resoy / ptr->ray.walldist);
		ptr->ray.drawstart = -ptr->ray.lineheight / 2 + ptr->resoy / 2;
		i = ray_cast2(ptr, i);
		while (ptr->ray.drawend < ptr->resoy)
		{
			ptr->t_img.image[ptr->ray.drawend * ptr->resox +
			ptr->ray.x] = ptr->sol;
			ptr->ray.drawend++;
		}
		i = 0;
		ptr->buffer[ptr->ray.x] = ptr->ray.walldist;
	}
	ray_cast3(ptr);
}

void	ray_cast_init(t_storage *ptr, int x)
{
	ptr->ray.camx = 2 * x / (double)(ptr->resox) - 1;
	ptr->ray.rayx = ptr->posx;
	ptr->ray.rayy = ptr->posy;
	ptr->ray.raydirx = ptr->dirx - ptr->planex * ptr->ray.camx;
	ptr->ray.raydiry = ptr->diry - ptr->planey * ptr->ray.camx;
	ptr->mapx = (int)ptr->ray.rayx;
	ptr->mapY = (int)ptr->ray.rayy;
	dda(ptr);
	dda2(ptr);
	if (ptr->ray.side == 0)
		ptr->ray.walldist = (ptr->mapx - ptr->ray.rayx +
		(1 - ptr->ray.stepx) / 2) / ptr->ray.raydirx;
	else
		ptr->ray.walldist = (ptr->mapY - ptr->ray.rayy +
		(1 - ptr->ray.stepy) / 2) / ptr->ray.raydiry;
}
