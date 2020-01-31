/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: blorin <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/08 15:14:10 by blorin       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/15 23:14:10 by blorin      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "mlx/mlx.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "cub3d.h"
#include <math.h>
#include "get_next_line.h"

/*
int		trace_rayon(t_storage *ptr, int diry, int xf)
{
	int yi = ptr->posY;
	int xi = ptr->posX;
	//	int xf = ptr->posX;
	int yf = diry;

	int dx;
	int dy;
	int xinc;
	int yinc;
	int cumul;
	int x;
	int y;
	int i;

	x = xi;
	y = yi;
	dx = xf-xi;
	dy = yf - yi;
	xinc = (dx > 0) ? 1 : -1;
	yinc = (dy > 0) ? 1 : -1;
	dx = abs(dx);
	dy = abs(dy);
	ptr->t_img.image[y * ptr->t_img.size_x + x] = 0;
	if (dx > dy)
	{
		cumul = dx / 2 ;
		i = 1;
		while(i++ <= dx  && ptr->t_img.image[y * ptr->t_img.size_x + x] != 60376) 
		{
			x += xinc ;
			cumul += dy ;
			if (cumul >= dx)
			{
				cumul -= dx ;
				y += yinc ; 
			}
			if (ptr->t_img.image[y * ptr->t_img.size_x + x] != 60376)
				ptr->t_img.image[y * ptr->t_img.size_x + x] = 0;
		}
	}
	else 
	{
		cumul = dy / 2 ;
		i = 1;
		while (i++ <= dy && ptr->t_img.image[y * ptr->t_img.size_x + x] != 60376) 
		{
			y += yinc ;
			cumul += dx ;
			if ( cumul >= dy ) 
			{
				cumul -= dy;
				x += xinc;
			}
			if (ptr->t_img.image[y * ptr->t_img.size_x + x] != 60376)
				ptr->t_img.image[y * ptr->t_img.size_x + x] = 0;  
		} 
	}
}
*/
int		parsing(int nbr, char *map)
{
	int nbrcount = 0;
	int i = 0;
	i = ft_strlen(map);
	nbrcount = i / nbr;
	return (nbrcount);

}

int		ft_atoi_char(char c)
{
	int i = 0;

	i = c - 48;
	return (i);
}
/*
void		array(t_storage *ptr)
{
	int	diry = ptr->posY;
	double pi = 3.1416;
	double	tourne;
	double dirX = 0;
	double dirY = -1;
	double angle = 90;
	double planeX = 0;
	double planeY = 0.60;
	int	dirx = ptr->posX;
	int i = 0;
	float ku = 1.0;
	while (ptr->t_img.image[diry *  (int)ptr->t_img.size_x + (int)ptr->posX] != 60376)
	{
		i++;
		diry--;

	}

double old;
	old = dirX;
	dirX = cos(angle * pi / 180) * dirX - sin(angle * pi / 180) * dirY;
	dirY = sin(angle * pi / 180) * old + cos(angle * pi / 180) * dirY;
	old = planeX;
	planeX = cos(angle * pi / 180) * planeX - sin(angle * pi / 180) * planeY;
	planeY = sin(angle * pi / 180) * old + cos(angle * pi / 180) * planeY;

	printf("dirX = %f\n dirY = %f\n planeX = %f\n planeY = %f\n", dirX, dirY, planeX, planeY);

	int x = ptr->posX;
	int y = ptr->posY;
	trace_rayon(ptr, diry, ptr->posX);
	diry = ptr->posY - 20;
	trace_rayon(ptr, diry + 10, ptr->posX - 10);

	
	   while (i < tmpi)
	   {
	   trace_rayon(ptr, 0, ptr->posX + i);
	   i++;
	   }
	   i = 1000;
	   while (i < tmpi)
	   {
	   i++;
	   }


	printf("lol\n");

	printf("%d\n", i);
	mlx_put_image_to_window(ptr->mlx_ptr, ptr->t_img.win_ptr2, ptr->t_img.img_ptr, 0, 0);
}
*/
char	*position(char *map, t_storage *ptr, int linecount, int nbrcount)
{
	int i = 0;

	while (map[i] != 'N' && map[i] != 'W' && map[i] != 'S' && map[i] != 'E' && map[i] != '\0')
		i++;
	ptr->posY = (((i / nbrcount) + 1) * 10) - 5;
	ptr->posX = (((i % nbrcount) + 1) * 10) - 5;
	map[i] = '0';
	return (map);


}

int image(t_storage *ptr, char *map, int linecount, int nbrcount)
{

	ptr->t_img.size_x = nbrcount * 10;
	ptr->t_img.size_y = linecount * 10;

	ptr->t_img.img_ptr = mlx_new_image(ptr->mlx_ptr, ptr->t_img.size_x, ptr->t_img.size_y);
	ptr->t_img.image =  (int *)mlx_get_data_addr(ptr->t_img.img_ptr, &ptr->t_img.bpp, &ptr->t_img.size_line, &ptr->t_img.endian);
	ptr->t_img.cubSizeY = 10;
	ptr->t_img.cubSizeX = 10;

	int i =0;
	int tmpx = 0;
	int tmpy = 0;
	int y = 0;
	int x = 0;
//	ptr->win_ptr = mlx_new_window(ptr->mlx_ptr, ptr->t_img.size_x,ptr->t_img.size_y, "ok");
	while (map[i] != '\0')
	{
		y = (((i / nbrcount) + 1) * ptr->t_img.cubSizeY) - ptr->t_img.cubSizeY;
		x = (((i % nbrcount) + 1) * ptr->t_img.cubSizeX) - ptr->t_img.cubSizeX;
		tmpx = x + ptr->t_img.cubSizeX;
		tmpy = y + ptr->t_img.cubSizeY;
		while (y < tmpy)
		{
			while (x < tmpx)
			{
				if (map[i] == '1')
					ptr->t_img.image[y * ptr->t_img.size_x + x]  = 60376;
				if (map[i] == '0')
					ptr->t_img.image[y * ptr->t_img.size_x + x] = 255;
				x++;
			}
			y++;
			x = tmpx - ptr->t_img.cubSizeX;
		}
		i++;
	}
	return (1);
}
int main(int ac, char **av)
{
	t_storage ptr;
	int y;
	int x;

	int tmp;
	x = 100;
	y = 100;
	int k = 0;
	int color = 255;
	char	*line;
	line = NULL;
	char	*str = NULL;
	int fd = 0;
	int ret = 1;
	int i = 0;
	int **tab;
	int end[1];
	ptr.resoY = 1500;
	ptr.resoX = 1500;


	ptr.mlx_ptr = mlx_init();

	ptr.win_ptr = mlx_new_window(ptr.mlx_ptr, ptr.resoX,ptr.resoY, "Bonjour les amis");

	/*ptr.img_ptr = mlx_new_image(ptr.mlx_ptr,  200, 200);
	  ptr.image = mlx_get_data_addr(ptr.img_ptr, &tab, &tob, end);
	  mlx_get_color_value(ptr.mlx_ptr, 255);
	  printf("%s", "salut\n");
	  ptr.image[3] = 'c';

	  mlx_put_image_to_window(ptr.mlx_ptr, ptr.win_ptr, ptr.img_ptr, 200, 200 );
	  mlx_loop(ptr.mlx_ptr);*/

	fd = open(av[1], O_RDONLY);
	int linecount = 0;
	while (get_next_line(fd, &line))
	{
		str = ft_strjoin(str, line);
		linecount++;
	}
	str = position(str,&ptr, linecount, parsing(linecount, str));

	//minimap(str, &ptr, linecount, parsing(linecount, str));
	image(&ptr, str, linecount, parsing(linecount, str));
	mlx_put_image_to_window(ptr.mlx_ptr, ptr.win_ptr, ptr.t_img.img_ptr, 0, 0);
	//tab = 	create_tab(str, linecount, parsing(i, str), &ptr);
	mlx_loop(ptr.mlx_ptr);
}
