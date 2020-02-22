/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blorin <blorin@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 17:09:06 by blorin            #+#    #+#             */
/*   Updated: 2020/02/22 16:03:00 by blorin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx/mlx.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include "get_next_line.h"

typedef struct	s_ray
{
	int			x;
	double		rayx;
	double		rayy;
	double		raydiry;
	double		raydirx;
	double		camx;
	int			hit;
	int			side;
	int			stepx;
	double		walldist;
	int			stepy;
	int			drawend;
	int			drawstart;
	int			lineheight;
	double		sidedistx;
	double		sidedisty;
	double		deltadistx;
	double		deltadisty;
}				t_ray;

typedef struct	s_minimap
{
	int			bpp;
	int			size_line;
	int			endian;
	double		tmpminx;
	double		maxy;
	double		miny;
	double		maxx;
	double		minx;
	double		incrx;
	double		incry;
}				t_minimap;

typedef struct	s_sprite_s
{
	double			x;
	double			y;
}				t_sprite_s;

typedef struct	s_sprite
{
	double		spritex;
	double		spritey;
	double		invdet;
	double		transfox;
	double		transfoy;
	int			spritescreenx;
	int			spriteheight;
	int			drawstarty;
	int			drawendy;
	int			spritewidth;
	int			count;
	int			drawstartx;
	int			drawendx;
	int			stripe;
	int			texx;
	int			texy;
	int			size;
	int			y;
}				t_sprite;

typedef struct	s_img
{
	void		*img_ptr;
	void		*img2;
	int			bpp;
	int			size_line;
	int			endian;
	int			imgsoly;
	int			size_y;
	int			imgy;
	int			imgx;
	int			*text;
	int			size_x;
	int			cubsizey;
	int			cubsizex;
}				t_imge;

typedef	struct	s_text
{
	void		*img;
	int			*data;
	int			bpp;
	int			sizeline;
	int			endian;
	int			y;
	int			x;
}				t_text;

typedef struct	s_move
{
	int			moveup;
	int			movedown;
	int			moveleft;
	int			movecamright;
	int			movecamleft;
	int			moveright;
	double		olddirx;
	double		olddiry;
	double		mspeed;
	int			door;
	double		rspeed;
	double		oldplanex;
	double		oldplaney;
}				t_move;

typedef struct	s_bmp
{
	int				size;
	char			*img;
	unsigned char	header[14];
	unsigned char	info[40];
	unsigned char	pad[3];
	int				color;
	int				fd;
}				t_bmp;

typedef struct	s_texture
{
	char		*est;
	char		*ouest;
	char		*nord;
	char		*sud;
	char		*porte;
	char		*sprite;
	char		*skybox;
}				t_texture;

typedef struct	s_check
{
	short int	no;
	short int	we;
	short int	p;
	short int	so;
	short int	ea;
	short int	sprite;
	short int	f;
	short int	c;
	short int	r;
	short int	door;
	short int	sky;
}				t_check;

typedef struct	s_storage
{
	double		wallx;
	double		wally;
	int			textx;
	int			texty;
	t_text		text[6];
	char		dir;
	void		*mlx_ptr;
	void		*win_ptr;
	int			resox;
	int			error;
	int			id;
	int			*image;
	int			resoy;
	double		dirx;
	double		diry;
	int			nbrcount;
	double		posy;
	double		posx;
	double		planex;
	double		planey;
	int			*doorposx;
	int			*doorposy;
	int			mapx;
	double		oldplanex;
	int			spritec;
	double		oldplaney;
	int			doorc;
	int			save;
	int			mvfront;
	double		*spriteposx;
	double		*spriteposy;
	double		*buffer;
	int			door;
	int			mv;
	int			sol;
	int			count_blue;
	int			count_red;
	int			count_green;
	int			plaf;
	int			linecount;
	int			mapy;
	int			**tab;
	int			texwidth;
	int			checkdoor;
	int			texheight;
	char		*map;
	t_imge		t_img;
	t_ray		ray;
	t_minimap	minimap;
	t_texture	texture;
	t_check		che;
	t_move		move;
	t_sprite	sprite;
	t_sprite_s	*spritet;
}				t_storage;

char			*ft_strdup(const char *str);
int				create_tab(t_storage *ptr);
int				check_reso(char *line, t_storage *ptr, t_check *checkv);
int				check_color_sol(char *line, t_storage *ptr, t_check *checkv);
int				check_color_plaf(char *line, t_storage *ptr, t_check *checkv);
int				check_text_e(char *line, t_storage *ptr, t_check *checkv);
int				check_text_n(char *line, t_storage *ptr, t_check *checkv);
int				check_text_w(char *line, t_storage *ptr, t_check *checkv);
int				error(t_storage *ptr, char *error);
int				check(char *line, t_storage *ptr, t_check *checkv);
void			ray_cast(t_storage *ptr);
void			ray_cast_init(t_storage *ptr, int x);
int				*draw_wall(t_storage *ptr, int start, int lineheight, int *img);
int				*put_pixel(t_storage *ptr, int start, int lineheight, int *img);
void			dda2(t_storage *ptr);
void			dda(t_storage *ptr);
int				*image(t_storage *ptr, int *img);
int				*sprite(t_storage *ptr, int *img);
void			ft_putstr(char *str);
void			save_bmp_file(t_storage *r, int *img);
int				screenshot(t_storage *ptr);
int				ft_atoi(char *line, int *i);
int				check_tab(t_storage *ptr);
int				position(t_storage *ptr);
void			set_val(t_storage *ptr);
int				move_side(t_storage *ptr);
void			sort_door(t_storage *ptr, double tmpx, double tmpy);
int				load(t_storage *ptr);
int				skybox(t_storage *ptr);
int				key(int key, t_storage *ptr);
int				gnl(char *av, t_storage *ptr, t_check *checkv);
int				key_release(int key, t_storage *ptr);
int				parsing(t_storage *ptr);
int				check_text_p(char *line, t_storage *ptr, t_check *checkv);
int				check_argue(t_storage *ptr, int ac, char **av);
int				open_win(t_storage *ptr);
int				ft_exit(t_storage *ptr);
char			*ft_strchr(const char *s, int c);
int				ft_strcpy_p(t_storage *ptr, int i, char	*line);
size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *src);
char			*ft_strchr(const char *s, int c);
void			*ft_memset(void *s, int c, size_t n);
char			*ft_strjoin(char const *s1, char const *s2);

#endif
