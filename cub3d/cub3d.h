/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cub3d.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: blorin <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/10 18:50:11 by blorin       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/26 21:01:47 by blorin      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "mlx/mlx.h"
#include "math.h"

typedef struct s_ray
{
	int x;
	double rayX;
	double rayY;
	double raydirY;
	double raydirX;
	double	camX;
	int hit;
	int side;
	int	stepX;
	double walldist;
	int	stepY;
	double	sidedistX;
	double	sidedistY;
	double	deltadistX;
	double	deltadistY;
}t_ray;

typedef struct s_img
{
	int		*image;
	void	*img_ptr;
	void	*img4;
	char	*image3;
	void	*img2;
	char		*image2;
	int		bpp;
	int		size_line;
	int		endian;
	void	*img3;
	int		*textSol;
	void	*imgSol;
	int		imgSolY;
	int		imgSolX;
	int		size_y;
	int		imgY;
	int		imgX;
	int 	*text;
	int		size_x;
	int		cubSizeY;
	int		cubSizeX;
}t_img;

typedef	struct	s_text
{
	void	*img;
int	*data;
	int		bpp;
	int		sizeline;
	int		endian;
}	t_text;

typedef struct s_move
{
	int	moveUp;
	int	moveDown;
	int	moveLeft;
	int moveRight;
	double olddirX;
	double olddirY;
	double mspeed;
	int 	door;
	double rspeed;
	double oldplaneX;
	double oldplaneY;
}s_move;

typedef struct s_texture
{
	char	*est;
	char	*ouest;
	char	*nord;
	char	*sud;
	char 	*sprite;
	char	*skybox;
}t_texture;

typedef struct s_check
{
	short int no;
	short int we;
	short int so;
	short int ea;
	short int sprite;
	short int F;
	short int C;
	short int R;
	short int door;	
	short int sky;
}t_check;

typedef struct s_storage
{
	double	wallX;
	void	*mini_img;
	int		*mini_tab;
	double	wallY;
	int		textX;
	int		textY;
	t_text	text[6];
	char	dir;
	void	*mlx_ptr;
	void	*win_ptr;
	int		resoX;
	int error;
	int		id;
	int		resoY;
	double	dirX;
	int		rev;
	int	realdoorX;
	int realdoorY;
	double dirY;
	int		nbrcount;
	double		posY;
double			posX;
int isdoor;
	double		planeX;
	double		planeY;
	int		*doorposX;
	double olddirX;
	double olddirY;
	int		*doorposY;
	double time;
	int		mapX;
	int		mvleft;
	double oldplaneX;
	int spriteC;
	double oldplaneY;
	int doorC;
	int 	mvright;
	int		mvfront;
	double		*spriteposX;
double *spriteposY;
	double *buffer;
	int		mvback;
	int mv;
	unsigned int sol;
	int	count_blue;
	int count_red;
	int	count_green;
	unsigned int plaf;
	int		linecount;
	int mapY;
	double oldtime;
	int		**tab;
	t_img	t_img;
	char	*map;
	t_ray	ray;
	t_texture texture;
	t_check che;
	s_move move;
	}t_storage;

char	*ft_strdup(const char *str);
#endif
