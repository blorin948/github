/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_gnl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blorin <blorin@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 23:28:34 by blorin            #+#    #+#             */
/*   Updated: 2020/02/22 15:18:33 by blorin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		gnl2(t_storage *ptr, char *av)
{
	int		fd;
	char	*ok;
	int		i;

	if (ptr->nbrcount == 0 || ptr->linecount == 0)
		return (error(ptr, "map"));
	i = 0;
	fd = open(av, O_RDONLY);
	ok = NULL;
	if (!(ptr->map = malloc(sizeof(char) * (ptr->linecount *
	ptr->nbrcount + 1))))
		return (error(ptr, "malloc"));
	while (get_next_line(fd, &ok))
	{
		if (ok[0] == '1')
			i = ft_strcpy_p(ptr, i, ok);
		ft_free(ok);
	}
	ft_free(ok);
	close(fd);
	return (0);
}

int		gnl(char *av, t_storage *ptr, t_check *checkv)
{
	int		fd;
	char	*line;
	int		t;
	char	*tmp;

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
			if (ptr->nbrcount != (int)ft_strlen(line))
				return (error(ptr, "map"));
			ptr->linecount++;
		}
		ft_free(line);
	}
	ft_free(line);
	close(fd);
	gnl2(ptr, av);
	return (0);
}

int		key2(int key, t_storage *ptr)
{
	if (key == 13)
		ptr->move.moveup = 1;
	if (key == 0)
		ptr->move.movecamleft = 1;
	if (key == 2)
		ptr->move.movecamright = 1;
	if (key == 1)
		ptr->move.movedown = 1;
	if (key == 123)
		ptr->move.moveleft = 1;
	if (key == 124)
		ptr->move.moveright = 1;
	if (key == 53)
		ft_exit(ptr);
	return (0);
}

int		key(int key, t_storage *ptr)
{
	double	tmpy;
	double	tmpx;
	double	posx;
	double	posy;

	tmpy = 0;
	tmpx = 0;
	sort_door(ptr, tmpx, tmpy);
	if (ptr->doorc)
	{
		posx = fabs(ptr->doorposx[0] - ptr->posx);
		posy = fabs(ptr->doorposy[0] - ptr->posy);
		if (key == 49 && (posy < 2 && posy > -2) && (posx < 2 && posx > -2) &&
		ptr->tab[ptr->doorposy[0]][ptr->doorposx[0]] == 3)
			ptr->tab[ptr->doorposy[0]][ptr->doorposx[0]] = 0;
		else if (key == 49 && ptr->tab[ptr->doorposy[0]][ptr->doorposx[0]] == 0
		&& (abs(ptr->doorposy[0] + ptr->doorposx[0]) != abs(((int)ptr->posx +
		(int)ptr->posy))) && (posy < 2 && posy > -2) && (posx < 2 && posx > -2))
			ptr->tab[ptr->doorposy[0]][ptr->doorposx[0]] = 3;
	}
	key2(key, ptr);
	return (0);
}

int		key_release(int key, t_storage *ptr)
{
	if (key == 13)
		ptr->move.moveup = 0;
	if (key == 0)
		ptr->move.movecamleft = 0;
	if (key == 2)
		ptr->move.movecamright = 0;
	if (key == 1)
		ptr->move.movedown = 0;
	if (key == 123)
		ptr->move.moveleft = 0;
	if (key == 124)
		ptr->move.moveright = 0;
	return (0);
}
