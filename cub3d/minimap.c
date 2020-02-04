/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   minimap.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: blorin <blorin@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/02 19:46:25 by blorin       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/04 19:29:06 by blorin      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"

void	white_edge(t_storage *ptr, int winx, int winy)
{
	int y;
	int x;

	y = 0;
	x = 0;
	while (x < winx)
		ptr->t_img.image[0 * winx + x++] = 0xfffffff;
	while (y < winy)
	{
		ptr->t_img.image[y * winx + (x - 1)] = 0xfffffff;
		y++;
	}
	x = 0;
	while (x < winx)
	{
		ptr->t_img.image[(winy - 1) * winx + x] = 0xfffffff;
		x++;
	}
	y = 0;
	while (y < winy)
	{
		ptr->t_img.image[y * winx + 0] = 0xfffffff;
		y++;
	}
}

void	set_map(t_storage *ptr, int winx, int winy)
{
	ptr->minimap.tmpminx = ptr->posx - 5;
	ptr->minimap.maxy = ptr->posy + 5;
	ptr->minimap.miny = ptr->posy - 5;
	ptr->minimap.maxx = ptr->posx + 5;
	ptr->minimap.minx = ptr->posx - 5;
	ptr->minimap.incrx = 10.0 / winx;
	ptr->minimap.incry = 10.0 / winy;
}

void	create_minimap(t_storage *ptr, int winx, int winy)
{
	int y;
	int x;

	x = 0;
	y = 0;
	set_map(ptr, winx, winy);
	while (y < winy)
	{
		while (x < winx)
		{
			if (ptr->minimap.miny > 0.0 && ptr->minimap.miny <
			(double)ptr->linecount && ptr->minimap.minx > 0.
			&& ptr->minimap.minx < (double)ptr->nbrcount &&
			ptr->tab[(int)ptr->minimap.miny][(int)ptr->minimap.minx] == 1)
				ptr->t_img.image[y * winx + x] = 0xfffffff;
			ptr->minimap.minx = ptr->minimap.minx + ptr->minimap.incrx;
			x++;
		}
		ptr->minimap.miny = ptr->minimap.miny + ptr->minimap.incry;
		ptr->minimap.minx = ptr->minimap.tmpminx;
		x = 1;
		y++;
	}
}

void	image(t_storage *ptr)
{
	int winx;
	int winy;

	winy = ptr->resoy / 6;
	winx = ptr->resox / 6;
	ptr->mini_img = mlx_new_image(ptr->mlx_ptr, winx, winy);
	ptr->t_img.image = (int *)mlx_get_data_addr(ptr->mini_img, &ptr->t_img.bpp,
	&ptr->minimap.size_line, &ptr->minimap.endian);
	ptr->t_img.cubSizey = winy / 6;
	ptr->t_img.cubSizex = winx / 6;
	white_edge(ptr, winx, winy);
	create_minimap(ptr, winx, winy);
	ptr->t_img.image[(winy / 2) * winx + (winx / 2)] = 0xFF0000;
	ptr->t_img.image[((winy / 2) + 1) * winx + ((winx / 2) + 1)] = 0xFF0000;
	ptr->t_img.image[(winy / 2) * winx + ((winx / 2) + 1)] = 0xFF0000;
	ptr->t_img.image[((winy / 2) + 1) * winx + (winx / 2)] = 0xFF0000;
	ptr->t_img.image[((winy / 2) - 1) * winx + ((winx / 2) - 1)] = 0xFF0000;
	ptr->t_img.image[(winy / 2) * winx + ((winx / 2) - 1)] = 0xFF0000;
	ptr->t_img.image[((winy / 2) - 1) * winx + (winx / 2)] = 0xFF0000;
	ptr->t_img.image[((winy / 2) + 1) * winx + ((winx / 2) - 1)] = 0xFF0000;
	ptr->t_img.image[((winy / 2) - 1) * winx + (winx / 2) + 1] = 0xFF0000;
	mlx_put_image_to_window(ptr->mlx_ptr, ptr->win_ptr, ptr->mini_img, 0, 0);
}
