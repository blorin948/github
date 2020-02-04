/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   key_gnl.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: blorin <blorin@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/03 00:59:46 by blorin       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/03 01:25:09 by blorin      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"

int		gnl(char *av, t_storage *ptr, t_check *checkv)
{
	int		fd;
	char	*line;
	int		t;

	fd = 0;
	t = 0;
	fd = open(av, O_RDONLY);
	if (fd <= 0)
		return (error(ptr, ".cub file"));
	while (get_next_line(fd, &line))
	{
		t = check(line, ptr, checkv);
		if (t == 1)
		{
			if (ptr->nbrcount == 0)
				ptr->nbrcount = ft_strlen(line);
			if (ptr->nbrcount != ft_strlen(line))
				return (error(ptr, "map"));
			ptr->map = ft_strjoin(ptr->map, line);
			ptr->linecount++;
		}
	}
	if (ptr->nbrcount == 0 || ptr->linecount == 0)
		return (error(ptr, "map"));
	return (0);
}

int		key2(int key, t_storage *ptr)
{
	if (key == 13)
		ptr->move.moveup = 1;
	if (key == 0)
		ptr->move.moveleft = 1;
	if (key == 2)
		ptr->move.moveright = 1;
	if (key == 1)
		ptr->move.movedown = 1;
	return (0);
}

int		key(int key, t_storage *ptr)
{
	int		a;
	int		o;
	double	posx;
	double	posy;

	a = -1;
	o = -1;
	find_door(ptr, &a, &o);
	posx = ptr->realdoorx;
	posy = ptr->realdoory;
	if (key == 49 && ptr->tab[ptr->doorposy[a]][ptr->doorposx[o]] == 3
	&& (posy < 2 && posy > -2) && (posx < 2 && posx > -2))
		ptr->tab[ptr->doorposy[a]][ptr->doorposx[o]] = 0;
	else if (key == 49 && ptr->tab[ptr->doorposy[a]][ptr->doorposx[o]] == 0 &&
	(int)ptr->posy != ptr->doorposy[a] && (posy < 2 && posy > -2) &&
	(posx < 2 && posx > -2))
		ptr->tab[ptr->doorposy[a]][ptr->doorposx[o]] = 3;
	key2(key, ptr);
	return (0);
}

int		key_release(int key, t_storage *ptr)
{
	if (key == 13)
		ptr->move.moveup = 0;
	if (key == 0)
		ptr->move.moveleft = 0;
	if (key == 2)
		ptr->move.moveright = 0;
	if (key == 1)
		ptr->move.movedown = 0;
	return (0);
}
