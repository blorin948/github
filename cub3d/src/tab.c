/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blorin <blorin@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 23:59:20 by blorin            #+#    #+#             */
/*   Updated: 2020/02/22 15:20:03 by blorin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		sprite_door(t_storage *ptr)
{
	int i;

	i = 0;
	while (ptr->map[i++] != '\0')
	{
		if (ptr->map[i] == '3')
			ptr->doorc++;
		if (ptr->map[i] == '2')
			ptr->spritec++;
	}
	if (ptr->doorc > 0)
	{
		if (!(ptr->doorposx = malloc(sizeof(int) * ptr->doorc)))
			return (0);
		if (!(ptr->doorposy = malloc(sizeof(int) * ptr->doorc)))
			return (0);
	}
	if (ptr->spritec > 0)
	{
		if (!(ptr->spritet = malloc(sizeof(t_sprite_s) * ptr->spritec)))
			return (0);
	}
	return (1);
}

int		malloc_tab(t_storage *ptr)
{
	int i;

	i = 0;
	if (!(ptr->tab = malloc(sizeof(int *) * ptr->linecount)))
		return (0);
	while (i < ptr->linecount)
	{
		if (!(ptr->tab[i] = malloc(sizeof(int) * ptr->nbrcount)))
			return (0);
		i++;
	}
	return (1);
}

void	create_tab2(t_storage *ptr, int i, int *sprite, int *c)
{
	int a;

	a = 0;
	while (a < ptr->nbrcount)
	{
		ptr->tab[i][a] = ptr->map[*c] - 48;
		if (ptr->tab[i][a] == 3)
		{
			ptr->doorposx[ptr->door] = a;
			ptr->doorposy[ptr->door] = i;
			ptr->door++;
		}
		if (ptr->tab[i][a] == 2)
		{
			ptr->spritet[*sprite].x = (double)a + 0.5;
			ptr->spritet[*sprite].y = (double)i + 0.5;
			*sprite = *sprite + 1;
		}
		a++;
		*c = *c + 1;
	}
}

int		create_tab(t_storage *ptr)
{
	int i;
	int a;
	int sprite;
	int c;

	sprite_door(ptr);
	malloc_tab(ptr);
	a = 0;
	c = 0;
	i = 0;
	sprite = 0;
	while (i < ptr->linecount)
	{
		create_tab2(ptr, i, &sprite, &c);
		i++;
	}
	return (0);
}

int		check_tab(t_storage *ptr)
{
	int i;
	int a;

	a = 0;
	i = 0;
	while (i++ < ptr->nbrcount - 2)
	{
		if (ptr->tab[0][i] != 1)
			return (error(ptr, "map"));
	}
	i = 0;
	while (a++ < ptr->linecount - 1)
	{
		if (ptr->tab[a][0] != 1)
			return (error(ptr, "map"));
		if (ptr->tab[a][ptr->nbrcount - 1] != 1)
			return (error(ptr, "map"));
	}
	i = 0;
	while (i++ < ptr->nbrcount - 1)
	{
		if (ptr->tab[ptr->linecount - 1][i] != 1)
			return (error(ptr, "map"));
	}
	return (1);
}
