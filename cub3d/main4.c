 /* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: blorin <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/30 13:45:42 by blorin       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/28 19:10:36 by blorin      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "mlx/mlx.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include "cub3d.h"
#include <math.h>
#include "get_next_line.h"

int		error(t_storage *ptr, char *error)
{
	printf("error with %s\n", error);
	ptr->error = 1;
	return (0);
}

int		parsing(int linecount, t_storage *ptr)
{
	int nbrcount = 0;
	int i = 0;
	int tmp = 0;
	int tmp2 = 0;
	int x = 0;
	while (ptr->map[i] != '\0')
	{
		if (ptr->map[i] != '1' && ptr->map[i] != '3' &&  ptr->map[i] != '0' && ptr->map[i] != 'E' && ptr->map[i] != 'S' && ptr->map[i] != 'O' && ptr->map[i] != 'N' && ptr->map[i] != '2' &&  ptr->map[i] != '4')
		{
			return (error(ptr, "map"));
		}
		i++;
	}
	return (1);
}

int	position(t_storage *ptr)
{
	int i = 0;
	while (ptr->map[i] != 'N' && ptr->map[i] != 'O' && ptr->map[i] != 'S' && ptr->map[i] != 'E' && ptr->map[i] != '\0')
		i++;
	if (ptr->map[i] == '\0')
		return (error(ptr,"position"));
	ptr->dir = ptr->map[i];
	ptr->posY = ((i / (ptr->nbrcount)));
	ptr->posX = ((i % (ptr->nbrcount)));
	//	printf("%s\n", map);
	ptr->posX = ptr->posX + .5;
	ptr->posY = ptr->posY + .5;
	//	printf("y = %f x = %f\n", ptr->posY, ptr->posX);
	ptr->map[i] = '0';
	while (ptr->map[i] != '\0')
	{
		if (ptr->map[i] != '4' && ptr->map[i] != '3' && ptr->map[i] != '0' && ptr->map[i] != '1' && ptr->map[i] != '2')
			return (error(ptr,"map"));
		i++;
	}
	return (0);
}

int		create_tab(t_storage *ptr)
{
	int 	i;
	i = 0;
	int a = 0;
	int c = 0;
	int door = 0;
	ptr->spriteC = 0;
	ptr->doorC = 0;

	while (ptr->map[i] != '\0')
	{
		if (ptr->map[i] == '3')
			ptr->doorC++;
		if (ptr->map[i] == '2')
			ptr->spriteC++;
		i++;
	}
	i = 0;
	if (ptr->doorC > 0)
	{
		if (!(ptr->doorposX = malloc(sizeof(int) * ptr->doorC)))
			return (0);
		if (!(ptr->doorposY = malloc(sizeof(int) * ptr->doorC)))
			return (0);
	}
	if (ptr->spriteC > 0)
	{
		if (!(ptr->spriteposX = malloc(sizeof(double) * ptr->spriteC)))
			return (0);
		if (!(ptr->spriteposY = malloc(sizeof(double) * ptr->spriteC)))
			return (0);
	}
	int sprite = 0;
	door = 0;
	if (!(ptr->tab = malloc(sizeof(int *) * ptr->linecount)))
		return (0);
	i = 0;
	a = 0;
	c = 0;
	while (i < ptr->nbrcount)
	{
		if (!(ptr->tab[i] = malloc(sizeof(int) * ptr->nbrcount)))
			return (0);
		i++;
	}
	i  =0;
	while (i < ptr->linecount)
	{
		a = 0;
		while (a < ptr->nbrcount)
		{
			ptr->tab[i][a] = ptr->map[c] - 48;
			if (ptr->tab[i][a] == 3)
			{
				ptr->doorposX[door] = a;
				ptr->doorposY[door] = i;
				door++;
			}
			if (ptr->tab[i][a] == 2)
			{
				ptr->spriteposX[sprite] = a + 0.5;
				ptr->spriteposY[sprite] = i + 0.5;
				sprite++;
			}
			a++;
			c++;
		}
		i++;
	}
	return (0);
}

void	sort_sprite(t_storage *ptr)
{
	int tmp;
	int count = 0;
	int distance;
	double tmpY;
	double tmpX;
	int dist;
	while (count < ptr->spriteC - 1)
	{
		distance = ((ptr->posX - ptr->spriteposX[count]) * (ptr->posX - ptr->spriteposX[count]) + (ptr->posY - ptr->spriteposY[count]) * (ptr->posY - ptr->spriteposY[count]));
		dist = ((ptr->posX - ptr->spriteposX[count  +1]) * (ptr->posX - ptr->spriteposX[count +1]) + (ptr->posY - ptr->spriteposY[count +1]) * (ptr->posY - ptr->spriteposY[count + 1]));
		if (distance > dist)
		{
			tmpY = ptr->spriteposY[count + 1];
			tmpX = ptr->spriteposX[count + 1];
			ptr->spriteposX[count + 1] = ptr->spriteposX[count];
			ptr->spriteposY[count + 1] = ptr->spriteposY[count];
			ptr->spriteposX[count] = tmpX;
			ptr->spriteposY[count] = tmpY;
			count = 0;
		}
		count++;
	}
}

int	sprite(t_storage *ptr)
{
	if (ptr->spriteC == 0)
		return (0);
	int count = ptr->spriteC;
	sort_sprite(ptr);
	while (count >= 0)
	{
		double spriteX = ptr->spriteposX[count] - ptr->posX;
		double spriteY = ptr->spriteposY[count] - ptr->posY;
		int endian;
		int size_line;
		int bpp;
		double invdet = 1.0 / (ptr->planeX * ptr->dirY - ptr->dirX * ptr->planeY);
		double transfoX = invdet * (-ptr->dirY  * spriteX - -ptr->dirX * spriteY);
		double transfoY = invdet * (-ptr->planeY * spriteX + ptr->planeX * spriteY);
		int		spritescreenX = (int)((ptr->resoX / 2) * ( 1 + transfoX / transfoY));

		int spriteheight = abs((int)(ptr->resoY / (transfoY)));

		int		drawStartY = -spriteheight / 2 + ptr->resoY / 2;
		if (drawStartY < 0)
			drawStartY = 0;
		int drawEndY = spriteheight / 2 + ptr->resoY / 2;
		if (drawEndY >= ptr->resoY)
			drawEndY = ptr->resoY - 1;

		int spriteWidth = abs((int)(ptr->resoY / (transfoY))); 
		int drawStartX = (-spriteWidth / 2 + spritescreenX); 
		if (drawStartX <0) 
			drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spritescreenX;
		if (drawEndX>= ptr->resoX) 
			drawEndX = ptr->resoX - 1; 
		int stripe = drawStartX;
		int texX;
		int d;
		int color = 0;
		int texY;
		int y;
		while (stripe++ < drawEndX)
		{
			texX = (256 * (stripe - (-spriteWidth / 2 + spritescreenX)) * 490 / spriteWidth) / 256;
			if (transfoY > 0 && stripe > 0 && stripe < ptr->resoX && transfoY < ptr->buffer[stripe])
			{
				y = drawStartY;
				while (y < drawEndY)
				{
					d = (y) * 256 - ptr->resoY * 128 + spriteheight * 128;
					texY = ((d * 490) / spriteheight) / 256;
					if (ptr->text[5].data[490 * texY + texX] > 100000)
						ptr->t_img.image[y * ptr->resoX + stripe] = ptr->text[5].data[490 * texY + texX];
					y++;
				}
				//	stripe++;
			}
		}
		count--;
	}
	return (1);
}

void	dda(t_storage *ptr)
{
	ptr->ray.deltadistX = sqrt(1 + (ptr->ray.raydirY * ptr->ray.raydirY) / (ptr->ray.raydirX * ptr->ray.raydirX));
	ptr->ray.deltadistY = sqrt(1 + (ptr->ray.raydirX * ptr->ray.raydirX) / (ptr->ray.raydirY * ptr->ray.raydirY));
	if (ptr->ray.raydirX < 0)
	{
		ptr->ray.stepX = -1;
		ptr->ray.sidedistX = (ptr->ray.rayX - ptr->mapX) * ptr->ray.deltadistX;
	}
	else
	{
		ptr->ray.stepX = 1;
		ptr->ray.sidedistX = (ptr->mapX + 1.0 - ptr->ray.rayX) * ptr->ray.deltadistX;
	}
	if (ptr->ray.raydirY < 0)
	{
		ptr->ray.stepY = -1;
		ptr->ray.sidedistY = (ptr->ray.rayY - ptr->mapY) * ptr->ray.deltadistY;
	}
	else
	{
		ptr->ray.stepY = 1;
		ptr->ray.sidedistY = (ptr->mapY + 1.0 - ptr->ray.rayY) * ptr->ray.deltadistY;
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
		if (ptr->ray.sidedistX < ptr->ray.sidedistY)
		{
			ptr->ray.sidedistX += ptr->ray.deltadistX;
			ptr->mapX += ptr->ray.stepX;
			ptr->ray.side = 0;
		}
		else
		{
			ptr->ray.sidedistY += ptr->ray.deltadistY;
			ptr->mapY += ptr->ray.stepY;
			ptr->ray.side = 1;
		}
		/*if (ptr->tab[ptr->mapY][ptr->mapX] == )
		  {
		//&& ((ptr->tab[ptr->mapY - 1][ptr->mapX] == 1 && ptr->tab[ptr->mapY + 1][ptr->mapX] == 1) || (ptr->tab[ptr->mapY][ptr->mapX - 1] == 1 && ptr->tab[ptr->mapY][ptr->mapX + 1]  == 1)))
		ptr->isdoor = 1;
		//		ptr->ray.hit = 1;
		}*/
		if (ptr->tab[ptr->mapY][ptr->mapX] == 1 || ((ptr->tab[ptr->mapY][ptr->mapX] == 4 && ptr->move.door == 0) || (ptr->tab[ptr->mapY][ptr->mapX] == 3 && ptr->move.door == 0)))
		{
			ptr->ray.hit = 1;
		}
	}
}

void	ray_cast_init(t_storage *ptr, int x)
{
	ptr->ray.camX = 2 * x / (double)(ptr->resoX) - 1;
	ptr->ray.rayX = ptr->posX;
	ptr->ray.rayY = ptr->posY;
	ptr->ray.raydirX = ptr->dirX - ptr->planeX * ptr->ray.camX;
	ptr->ray.raydirY = ptr->dirY - ptr->planeY * ptr->ray.camX;
	ptr->mapX = (int)ptr->ray.rayX;
	ptr->mapY = (int)ptr->ray.rayY;
	dda(ptr);
	dda2(ptr);
	if (ptr->ray.side == 0)
		ptr->ray.walldist = (ptr->mapX - ptr->ray.rayX + (1 - ptr->ray.stepX) / 2) / ptr->ray.raydirX;
	else
		ptr->ray.walldist = (ptr->mapY - ptr->ray.rayY + (1 - ptr->ray.stepY) / 2) / ptr->ray.raydirY;
}

void	put_pixel(t_storage *ptr, int start, int lineheight)
{
	int id = 0;
	if (ptr->tab[ptr->mapY][ptr->mapX] == 3 && ptr->move.door == 0)
		id = 4;
	else if (ptr->ray.side == 0 && ptr->ray.raydirX < 0)
		id = 0;
	else if (ptr->ray.side == 0)
		id = 1;
	else if (ptr->ray.side == 1 && ptr->ray.raydirY < 0)
		id = 2;
	else if (ptr->ray.side == 1)
		id = 3;
	if (ptr->ray.x < ptr->resoX && start < ptr->resoY)
	{
		ptr->textY = abs((((start * 256 - ptr->resoY * 128 + lineheight * 128) * 64) / lineheight) / 256);
		ptr->t_img.image[start * ptr->resoX + ptr->ray.x] = ptr->text[id].data[(ptr->textY % 64 * ptr->text[id].sizeline + ptr->textX % 64 * ptr->text[id].bpp / 8) / 4];
	}

}
void	draw_wall(t_storage *ptr, int start, int end, int lineheight)
{
	if (ptr->ray.side == 0)
		ptr->wallX = ptr->ray.rayY + ptr->ray.walldist * ptr->ray.raydirY;
	else
		ptr->wallX = ptr->ray.rayX + ptr->ray.walldist * ptr->ray.raydirX;
	ptr->textX = (int)(ptr->wallX * (double)(64));
	if (ptr->ray.side == 0 && ptr->ray.raydirX > 0)
		ptr->textX = 64 - ptr->textX - 1;
	if (ptr->ray.side == 1 && ptr->ray.raydirY < 0)
		ptr->textX = 64 - ptr->textX - 1;
	ptr->textX = abs(ptr->textX);

	while (start++ < end)
		put_pixel(ptr, start, lineheight);
}

void	image(t_storage *ptr)
{
	int winX = ptr->resoX / 6;
	int winY = ptr->resoY / 6;
	ptr->mini_img = mlx_new_image(ptr->mlx_ptr, winX, winY);
	//mlx_put_image_to_window(ptr->mlx_ptr, ptr->win_ptr, ptr->mini_img, 0, 0);

	//ptr->t_img.size_x = ptr->nbrcount  * 10;
	//ptr->t_img.size_y = ptr->linecount * 10;

	ptr->t_img.image =  (int *)mlx_get_data_addr(ptr->mini_img, &ptr->t_img.bpp, &ptr->t_img.size_line, &ptr->t_img.endian);

//ptr->t_img.image[50 * winX + 5] = 0xfffffff;
	ptr->t_img.cubSizeY = winY / 6;
	ptr->t_img.cubSizeX = winX / 6;
	int y = 0;
	int x = 0;
	while (x < winX)
	{
		ptr->t_img.image[0 * winX + x] = 0xfffffff;
		x++;
	}
	while (y < winY)
	{
		ptr->t_img.image[y * winX + (x - 1)] = 0xfffffff;
		y++;
	}
	x = 0;
		while (x < winX)
		{
			ptr->t_img.image[(winY - 1) * winX + x] = 0xfffffff;
			x++;
		}
	y = 0;
	x = 0;
	while (y < winY)
	{
		ptr->t_img.image[y * winX + 0] = 0xfffffff;
		y++;
	}
		y = 0;
		x++;
	x = 1;
	y = 1;
	double tmpminX = ptr->posX - 5;
	double maxY = ptr->posY + 5;
	double minY = ptr->posY - 5;
	double maxX = ptr->posX + 5;
	double minX = ptr->posX - 5;
	double incrX = 10.0 / winX;
	double incrY = 10.0 / winY;
	
	while (y < winY)
	{
		while (x < winX)
		{
			if (minY >= 0 && minY <=(double)ptr->linecount && minX >= 0 && minX <= (double)ptr->nbrcount  && ptr->tab[(int)minY][(int)minX] == 1)
				ptr->t_img.image[y * winX + x]  = 0xfffffff;
			minX = minX + incrX;
			x++;
		}
		minY = minY + incrY;
		minX = tmpminX;
		x = 1;
		y++;
	}
	ptr->t_img.image[(winY / 2) * winX + (winX / 2)] = 0xFF0000;
	ptr->t_img.image[((winY / 2) +1)* winX + ((winX / 2)+1)] = 0xFF0000;
	ptr->t_img.image[(winY / 2) * winX + ((winX / 2) +1)] = 0xFF0000;
	ptr->t_img.image[((winY / 2) + 1) * winX + (winX / 2)] = 0xFF0000;
	ptr->t_img.image[((winY / 2) -1)* winX + ((winX / 2)-1)] = 0xFF0000;
	ptr->t_img.image[(winY / 2) * winX + ((winX / 2) -1)] = 0xFF0000;
	ptr->t_img.image[((winY / 2) - 1) * winX + (winX / 2)] = 0xFF0000;
	ptr->t_img.image[((winY / 2) +1)* winX + ((winX / 2)-1)] = 0xFF0000;
	ptr->t_img.image[((winY / 2) -1) * winX + (winX / 2) + 1] = 0xFF0000;

	mlx_put_image_to_window(ptr->mlx_ptr, ptr->win_ptr, ptr->mini_img, 0, 0);
}

void	ray_cast(t_storage *ptr)
{
	int bits_per_pixel;
	int	size_line;
	int endian;
	ptr->t_img.img_ptr = mlx_new_image(ptr->mlx_ptr, ptr->resoX, ptr->resoY);
	ptr->t_img.image = (int*)mlx_get_data_addr(ptr->t_img.img_ptr, &ptr->t_img.bpp, &size_line, &endian );
	int color = 60376;
	ptr->ray.x = -1;
	int	drawEnd = 0;
	int	drawStart = 0;
	int lineheight = 0;
	int i = 0;
	if (ptr->move.moveRight == 1)
		ptr->mv += 55;
	if (ptr->move.moveLeft == 1)
		ptr->mv -= 55;
	if (ptr->mv > ptr->t_img.imgX)
		ptr->mv = 0;
	if (ptr->mv < 0)
		ptr->mv = ptr->t_img.imgX;	

	if (ptr->move.moveUp == 1)
		ptr->mvfront += 45;
	if (ptr->move.moveDown == 1)
		ptr->mvfront -= 45;
	if (ptr->mvfront > ptr->t_img.imgSolY)
		ptr->mvfront = 0;
	if (ptr->mvfront < 0)
		ptr->mvfront = ptr->t_img.imgSolY;


	while (++ptr->ray.x < ptr->resoX)
	{
		ray_cast_init(ptr, ptr->ray.x);
		lineheight = (int)(ptr->resoY / ptr->ray.walldist);
		drawStart = -lineheight / 2 + ptr->resoY / 2;
		if (drawStart < 0)
			drawStart = 0;
		drawEnd = lineheight / 2 + ptr->resoY / 2;
		if (drawEnd >= ptr->resoY)
			drawEnd = ptr->resoY - 1;
		if (ptr->ray.side == 1)
			color = 0xdd8800;
		else
			color = 0xCD5C5C;
		while (i < drawStart)
		{
			if (ptr->che.sky > 0)
				ptr->t_img.image[i * ptr->resoX + ptr->ray.x] = ptr->t_img.text[i * ptr->t_img.imgX + (ptr->ray.x + ptr->mv)];
			else 
				ptr->t_img.image[i * ptr->resoX + ptr->ray.x] = ptr->plaf;
			i++;
		}
		draw_wall(ptr, drawStart, drawEnd, lineheight);
		while (drawEnd < ptr->resoY)
		{
			ptr->t_img.image[drawEnd * ptr->resoX + ptr->ray.x] = ptr->sol;
			drawEnd++;
		}
		i = 0;
		ptr->buffer[ptr->ray.x] = ptr->ray.walldist;
	}
	sprite(ptr);
	mlx_put_image_to_window(ptr->mlx_ptr, ptr->win_ptr, ptr->t_img.img_ptr, 0, 0);
	image(ptr);
	mlx_destroy_image(ptr->mlx_ptr, ptr->t_img.img_ptr );
}

int	move_side(t_storage *ptr)
{ 

	if (ptr->move.moveRight == 1)
	{
		ptr->move.olddirX = ptr->dirX;
		ptr->dirX = ptr->dirX * cos(ptr->move.rspeed) - ptr->dirY * sin(ptr->move.rspeed);
		ptr->dirY = ptr->move.olddirX * sin(ptr->move.rspeed) + ptr->dirY * cos(ptr->move.rspeed);
		ptr->move.oldplaneX = ptr->planeX;
		ptr->planeX = ptr->planeX * cos(ptr->move.rspeed) - ptr->planeY * sin(ptr->move.rspeed);
		ptr->planeY = ptr->move.oldplaneX * sin(ptr->move.rspeed) + ptr->planeY * cos(ptr->move.rspeed);
	}
	if (ptr->move.moveLeft == 1)
	{
		ptr->move.olddirX = ptr->dirX;
		ptr->dirX = ptr->dirX * cos(-ptr->move.rspeed) - ptr->dirY * sin(-ptr->move.rspeed);
		ptr->dirY = ptr->move.olddirX * sin(-ptr->move.rspeed) + ptr->dirY * cos(-ptr->move.rspeed);
		ptr->move.oldplaneX = ptr->planeX;
		ptr->planeX = ptr->planeX * cos(-ptr->move.rspeed) - ptr->planeY * sin(-ptr->move.rspeed);
		ptr->planeY = ptr->move.oldplaneX * sin(-ptr->move.rspeed) + ptr->planeY * cos(-ptr->move.rspeed);
	}
	if (ptr->move.moveUp == 1)
	{
		if (ptr->tab[(int)ptr->posY][(int)(ptr->posX + ptr->dirX * ptr->move.mspeed * 1.5)] == 0 || ptr->tab[(int)ptr->posY][(int)(ptr->posX + ptr->dirX * ptr->move.mspeed * 1.5)] == 0 ||  (ptr->tab[(int)ptr->posY][(int)(ptr->posX + ptr->dirX * (ptr->move.mspeed * 1.5))] == 3 && ptr->move.door == 1))
		{
			ptr->posX += ptr->dirX * ptr->move.mspeed;
		}
		if (ptr->tab[(int)(ptr->posY + ptr->dirY * ptr->move.mspeed * 1.5)][(int)(ptr->posX)] == 0 || ptr->tab[(int)(ptr->posY + ptr->dirY * ptr->move.mspeed * 1.5)][(int)(ptr->posX)] == 0 || (ptr->tab[(int)(ptr->posY + ptr->dirY * (ptr->move.mspeed * 1.5))][(int)(ptr->posX)] == 3 && ptr->move.door == 1))
		{
			ptr->posY += ptr->dirY * ptr->move.mspeed;
		}
	}
	if (ptr->move.moveDown == 1)
	{
		if (ptr->tab[(int)(ptr->posY)][(int)(ptr->posX - ptr->dirX * ptr->move.mspeed *1.5)] == 0 || (ptr->tab[(int)(ptr->posY)][(int)(ptr->posX - ptr->dirX * ptr->move.mspeed * 1.5)] == 3 && ptr->move.door == 1))
			ptr->posX -= ptr->dirX * ptr->move.mspeed;
		if (ptr->tab[(int)(ptr->posY - ptr->dirY * ptr->move.mspeed *1.5)][(int)(ptr->posX)] == 0 || (ptr->tab[(int)(ptr->posY - ptr->dirY * ptr->move.mspeed * 1.5)][(int)(ptr->posX)] == 3 && ptr->move.door == 1))
			ptr->posY -= ptr->dirY * ptr->move.mspeed;
	}
	ray_cast(ptr);
	return (0);
}

void	find_door(t_storage *ptr, int *a, int *o)
{
	double tmpY = 0;
	double tmpX = 0;
	int i = 0;
	ptr->realdoorY = 20;
	ptr->realdoorX = 20;
	while (i < ptr->doorC)
	{
		tmpX = ptr->posX - (double)ptr->doorposX[i];
		tmpY = ptr->posY - (double)ptr->doorposY[i];
		if (fabs(tmpY) < abs(ptr->realdoorY))
		{
			*a = *a + 1;
			ptr->realdoorY = tmpY;
		}
		if (fabs(tmpX) < abs(ptr->realdoorX))
		{
			*o = *o + 1;
			ptr->realdoorX = tmpX;
		}
		i++;
	}

}


int		key(int key,t_storage *ptr)
{
	int a = -1;
	int o = -1;
	double posX;
	double posY;
	find_door(ptr, &a, &o);
	posX = ptr->realdoorX;
	posY = ptr->realdoorY;

	if (key == 49 && ptr->tab[ptr->doorposY[a]][ptr->doorposX[o]] == 3 && (posY < 2 && posY > -2) && (posX < 2 && posX > -2))
		ptr->tab[ptr->doorposY[a]][ptr->doorposX[o]] = 0;
	else if (key == 49 && ptr->tab[ptr->doorposY[a]][ptr->doorposX[o]] == 0 && (int)ptr->posY != ptr->doorposY[a]  && (posY < 2 && posY > -2) && (posX < 2 && posX > -2))
		ptr->tab[ptr->doorposY[a]][ptr->doorposX[o]] = 3;
	if (key == 13)
		ptr->move.moveUp = 1;
	if (key == 0)
		ptr->move.moveLeft = 1;
	if (key == 2)
		ptr->move.moveRight = 1;
	if (key == 1)
		ptr->move.moveDown = 1;
	return (0);
}

int		key_release(int key, t_storage *ptr)
{
	if (key == 13)
		ptr->move.moveUp = 0;
	if (key == 0)
		ptr->move.moveLeft = 0;
	if (key == 2)
		ptr->move.moveRight = 0;
	if (key == 1)
		ptr->move.moveDown = 0;
	return (0);
}

void	set_val(t_storage *ptr)
{
	if (ptr->dir == 'E')
	{
		ptr->dirX = -1;
		ptr->dirY = 0;
		ptr->planeY = 0.66;
		ptr->planeX = 0;
	}
	if (ptr->dir == 'O')
	{
		ptr->dirX = 1;
		ptr->dirY = 0;
		ptr->planeY = -0.66;
		ptr->planeX = 0;
	}
	if (ptr->dir == 'N')
	{
		ptr->dirX = 0;
		ptr->dirY = -1;
		ptr->planeY = 0;
		ptr->planeX = -0.66;
	}
	if (ptr->dir == 'S')
	{
		ptr->dirX = 0;
		ptr->dirY = 1;
		ptr->planeY = 0;
		ptr->planeX = 0.66;
	}
}

int		ft_atoi(char *line, int *i)
{
	int count = 0;
	while (line[*i] >= '0' && line [*i] <= '9' && line[*i] != '\0')
	{
		count = count * 10 + line[*i] - 48;
		*i = *i + 1;;
	}
	return (count);
}

int		check_reso(char *line, t_storage *ptr, t_check *checkV)
{
	int i = 0;
	int count = 0;
	if (line[0] != 'R')
		return (0);
	while (((line[i] <= '0' || line[i] >= '9')) && line[i] != 45)
		i++;
	count = ft_atoi(line, &i);
	ptr->resoX = count;
	i++;
	count = ft_atoi(line, &i);
	ptr->resoY = count;
	if (ptr->resoX > 2560)
		ptr->resoX = 2560;
	if (ptr->resoY > 1395)
		ptr->resoY = 1395;
	checkV->R++;
	printf("lol\n");
	if (ptr->resoY <= 0 || ptr->resoX <= 0)
	{
		printf("error with resolution\n");
		ptr->error = 1;
		return (0);
	}
	return (1);
}

int		check_color_sol(char *line, t_storage *ptr, t_check *checkV)
{
	if (line[0] != 'F')
		return (0);
	char red;
	char blue;
	char green;
	int i = 0;
	int count;
	while (line[i] <= '0' || line[i] >= '9')
		i++;
	ptr->count_red = ft_atoi(line, &i);
	red = ptr->count_red;
	while (line[i] <= '0' || line[i] >= '9')
		i++;
	ptr->count_green = ft_atoi(line, &i);
	green = ptr->count_green;
	while (line[i] <= '0' || line[i] >= '9')
		i++;
	ptr->count_blue = ft_atoi(line, &i);
	blue = ptr->count_blue;
	if (ptr->count_red > 255 || ptr->count_green > 255 || ptr->count_blue > 255)
	{
		printf("error with color\n");
		ptr->error = 1;
		return (0);
	}
	ptr->sol = (red & 0xff) | (green & 0xff) << 8 | (blue & 0xff) << 16;
	checkV->F++;
	return (1);
}

int		check_color_plaf(char *line, t_storage *ptr, t_check *checkV)
{
	if (line[0] != 'C')
		return (0);
	char red;
	char blue;
	char green;
	int i = 0;
	int count;
	while (line[i] <= '0' || line[i] >= '9')
		i++;
	ptr->count_red = ft_atoi(line, &i);
	red = ptr->count_red;
	i++;
	ptr->count_green = ft_atoi(line, &i);
	green = ptr->count_green;
	i++;
	ptr->count_blue = ft_atoi(line, &i);
	blue = ptr->count_blue;
	if (ptr->count_red > 255 || ptr->count_green > 255 || ptr->count_blue > 255)
	{
		printf("error with color\n");
		ptr->error = 1;
		return (0);
	}
	ptr->plaf = (red & 0xff)  | (green & 0xff) << 8 | (blue & 0xff) << 16;
	checkV->C++;
	return (1);
}

int		check_text_E(char *line, t_storage *ptr, t_check *checkV)
{
	if (line[0] != 'E' || line[1] != 'A')
		return (0);
	checkV->ea++;
	int i = 3;
	int a = 0;
	ptr->texture.est = ft_strdup(line + i);
	
	return (1);
}

int		check_text_N(char *line, t_storage *ptr, t_check *checkV)
{
	if (line[0] != 'N' || line[1] != 'O')
		return (0);
		checkV->no++;
	int i = 3;
	int a = 0;
	ptr->texture.nord = ft_strdup(line + i);
	return (1);
}

int		check_text_W(char *line, t_storage *ptr, t_check *checkV)
{
	if (line[0] != 'W' ||line[1] != 'E')
		return (0);
	checkV->we++;
	int i = 3;
	int a = 0;
	ptr->texture.ouest = ft_strdup(line + i);
	return (1);
}

int		check_text_S(char *line, t_storage *ptr, t_check *checkV)
{
	if (line[0] != 'S' || line[1] != 'O')
		return (0);
		checkV->so++;
	int i = 3;
	int a = 0;
	ptr->texture.sud = ft_strdup(line + i);
	return (1);
}

int	check_sprite(char *line, t_storage *ptr, t_check *checkV)
{
if (line[0] != 'S' || line[1] != ' ')
	return (0);
	checkV->sprite++;
	int i = 2;
	int a = 0;
	ptr->texture.sprite = ft_strdup(line + i);
	return (1);
}

int	check_skybox(char *line, t_storage *ptr, t_check *checkV)
{
if (line[0] != 'C' || line[1] != 'T')
	return (0);
	checkV->sky++;
	int i = 3;
	int a = 0;
	ptr->texture.skybox = ft_strdup(line + i);
	return (1);
}

void	check2(char *line, t_storage *ptr, t_check *checkV)
{

	int i = 0;
	check_reso(line, ptr, checkV);
	check_color_sol(line ,ptr, checkV);
	check_color_plaf(line, ptr, checkV);
	check_text_E(line, ptr, checkV);
	check_text_N(line, ptr, checkV);
	check_text_W(line, ptr, checkV);
	check_text_S(line, ptr, checkV);
	check_sprite(line, ptr, checkV);
}

int	check(char *line, t_storage *ptr, t_check *checkV)
{
	int i = 0;
	static int a = 0;
	if (line[0] == '1')
		a++;
	if (a > 0 && line[0] != '1')
		return (error(ptr, "map"));
	if (line[0]  < '0' || line[0] > '9')
	{
		check2(line, ptr, checkV);
		return (0);
	}
	if (line[0] == '1')
	{
		return (1);
	}
	a = 0;
	return (0);
}

int		check_tab(t_storage *ptr)
{
	int i = 0;
	int a = 0;
	while (i < ptr->nbrcount - 1)
	{
		if (ptr->tab[0][i] != 1)
		{
			return (error(ptr, "map"));
		}
		i++;
	}
	i = 0;
	while (a < ptr->linecount)
	{
		if (ptr->tab[a][0] != 1)
		{
			return (error(ptr, "map"));
		}
		if (ptr->tab[a][ptr->nbrcount - 1] != 1)
		{
			return (error(ptr, "map"));
		}
		a++;
	}
i = 0;
	while (i < ptr->nbrcount)
	{	
		if (ptr->tab[ptr->linecount - 1][i] != 1)
		{
			return (error(ptr, "map"));
		}
		i++;
	}
	return (1);
}

int	load(t_storage *ptr)
{
	int a = 64;
	int b = 64;
	if (!(ptr->text[0].img = mlx_xpm_file_to_image(ptr->mlx_ptr, ptr->texture.nord, &a, &b)))
		return (error(ptr, "texture"));
	ptr->text[0].data = (int*)mlx_get_data_addr(ptr->text[0].img, &ptr->text[0].bpp, &ptr->text[0].sizeline, &ptr->text[0].endian);

	if (!(ptr->text[1].img = mlx_xpm_file_to_image(ptr->mlx_ptr, ptr->texture.est, &a, &b)))
		return (error(ptr, "texture"));
	ptr->text[1].data = (int*)mlx_get_data_addr(ptr->text[1].img, &ptr->text[1].bpp, &ptr->text[1].sizeline, &ptr->text[1].endian);

	if (!(ptr->text[2].img = mlx_xpm_file_to_image(ptr->mlx_ptr, ptr->texture.ouest, &a, &b)))
		return (error(ptr, "texture"));
	ptr->text[2].data = (int*)mlx_get_data_addr(ptr->text[2].img, &ptr->text[2].bpp, &ptr->text[2].sizeline, &ptr->text[2].endian);

	if (!(ptr->text[3].img = mlx_xpm_file_to_image(ptr->mlx_ptr, ptr->texture.sud, &a, &b)))
		return (error(ptr, "texture"));
	ptr->text[3].data = (int*)mlx_get_data_addr(ptr->text[3].img, &ptr->text[3].bpp, &ptr->text[3].sizeline, &ptr->text[3].endian);

	if (!(ptr->text[4].img = mlx_xpm_file_to_image(ptr->mlx_ptr, "woodporte.xpm", &a, &b)))
		return (error(ptr, "texture"));
	ptr->text[4].data = (int*)mlx_get_data_addr(ptr->text[4].img, &ptr->text[4].bpp, &ptr->text[4].sizeline, &ptr->text[4].endian);

	if (!(ptr->text[5].img = mlx_xpm_file_to_image(ptr->mlx_ptr, ptr->texture.sprite, &a, &b)))
		return (error(ptr, "texture"));
	ptr->text[5].data = (int*)mlx_get_data_addr(ptr->text[5].img, &ptr->text[5].bpp, &ptr->text[5].sizeline, &ptr->text[5].endian);

}

int		ecran(t_storage *ptr)
{
	mlx_hook(ptr->win_ptr, 2, 0, key, ptr);
	mlx_hook(ptr->win_ptr, 3, 0, key_release, ptr);
	ray_cast(ptr);
	mlx_loop_hook(ptr->mlx_ptr, move_side, ptr);
	mlx_loop(ptr->mlx_ptr);
return (1);
}

int		gnl(char *av, t_storage *ptr, t_check *checkV)
{
	int fd = 0;
	char *line;

	fd = open(av, O_RDONLY);

	while (get_next_line(fd, &line))
	{
		if ((check(line, ptr, checkV) > 0))
		{
			if (ptr->nbrcount == 0)
				ptr->nbrcount = ft_strlen(line);
			if (ptr->nbrcount != ft_strlen(line))
				return (error(ptr, "map"));
			ptr->map = ft_strjoin(ptr->map, line);
			ptr->linecount++;
		}
	}
	return (0);
}

int main(int ac, char **av)
{
	t_storage ptr = {0};
	ptr.time = 0;
	ptr.oldtime  = 0;
	int a = 0;
	int count = 0;
	ptr.nbrcount = 0;
	ptr.resoX = 1;
	ptr.resoY = 1;
	ptr.move.mspeed = 0.10;
	ptr.move.rspeed = 0.10;
	ptr.linecount = 0;
t_check checkV;
	gnl(av[1], &ptr, &checkV);
printf("%d\n", checkV.R);
if (checkV.ea != 1 || checkV.no != 1 || checkV.we != 1 || checkV.so != 1 || checkV.F != 1 || checkV.C != 1 || checkV.F != 1 || checkV.sprite != 1 || checkV.R != 1)
	return (error(&ptr, "parametres"));
	parsing(ptr.linecount, &ptr);
	position(&ptr);
	create_tab(&ptr);
	a = 0;
	if (check_tab(&ptr) < 0)
		return (0);
	set_val(&ptr);
	if (!(ptr.buffer = malloc(sizeof(double) * ptr.resoX)))
		return (0);
	if (!(ptr.mlx_ptr = mlx_init()))
		return (0);
		int i = 0;
	/*while (a < ptr.linecount)
	  {
	  while (i < ptr.nbrcount)
	  {
	  printf("%d", ptr.tab[a][i]);
	  i++;
	  }
	  printf("\n");
	  i = 0;
	  a++;
	  }*/
	int z;
	int ju;
	int f;
	int ok;
	int za;
	int uf;
	load(&ptr);
	if (ptr.error >0)
	return (0);
	printf("x = %d y = %d\n", ptr.resoX, ptr.resoY);
	if (!(ptr.win_ptr = mlx_new_window(ptr.mlx_ptr, ptr.resoX, ptr.resoY, "loool")))
		return (0);
	if (!(ptr.t_img.img_ptr = mlx_new_image(ptr.mlx_ptr, ptr.resoX, ptr.resoY)))
		return (0);
	if (!(ptr.t_img.img2  = mlx_xpm_file_to_image(ptr.mlx_ptr, ptr.texture.skybox, &ptr.t_img.imgX, &ptr.t_img.imgY)))
		return (0);
	if (!(ptr.t_img.text = (int*)mlx_get_data_addr(ptr.t_img.img2, &z, &f, &ju)))
		return (0);
	ecran(&ptr);
}
