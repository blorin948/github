/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   set_variables.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: blorin <blorin@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/03 00:10:22 by blorin       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/11 22:58:51 by blorin      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../cub3d.h"

int		position(t_storage *ptr)
{
	int i;

	i = 0;
	while (ptr->map[i] != 'N' && ptr->map[i] != 'W' && ptr->map[i] != 'S'
	&& ptr->map[i] != 'E' && ptr->map[i] != '\0')
		i++;
	if (ptr->map[i] == '\0')
		return (error(ptr, "position"));
	ptr->dir = ptr->map[i];
	ptr->posy = ((i / (ptr->nbrcount)));
	ptr->posx = ((i % (ptr->nbrcount)));
	ptr->posx = ptr->posx + .5;
	ptr->posy = ptr->posy + .5;
	ptr->map[i] = '0';
	while (ptr->map[i] != '\0')
	{
		if (ptr->map[i] != '4' && ptr->map[i] != '3' && ptr->map[i] != '0' &&
		ptr->map[i] != '1' && ptr->map[i] != '2')
			return (error(ptr, "map"));
		i++;
	}
	return (0);
}

void	set_val2(t_storage *ptr)
{
	if (ptr->dir == 'N')
	{
		ptr->dirx = 0;
		ptr->diry = -1;
		ptr->planey = 0;
		ptr->planex = -0.66;
	}
	if (ptr->dir == 'S')
	{
		ptr->dirx = 0;
		ptr->diry = 1;
		ptr->planey = 0;
		ptr->planex = 0.66;
	}
}

void	set_val(t_storage *ptr)
{
	if (ptr->dir == 'E')
	{
		ptr->dirx = 1;
		ptr->diry = 0;
		ptr->planey = -0.66;
		ptr->planex = 0;
	}
	if (ptr->dir == 'W')
	{
		ptr->dirx = -1;
		ptr->diry = 0;
		ptr->planey = 0.66;
		ptr->planex = 0;
	}
	ptr->move.mspeed = 0.10;
	ptr->move.rspeed = 0.10;
}

int		error(t_storage *ptr, char *error)
{
	printf("error with %s\n", error);
	ft_exit(ptr);
	return (0);
}

int		ft_exit(t_storage *ptr)
{
	int i;

	i = 0;
	ft_free(ptr->map);
	ft_free(ptr->texture.nord);
	ft_free(ptr->texture.sud);
	ft_free(ptr->texture.ouest);
	ft_free(ptr->texture.est);
	ft_free(ptr->buffer);
	ft_free(ptr->doorposx);
	ft_free(ptr->doorposy);
	ft_free(ptr->spriteposx);
	ft_free(ptr->spriteposy);
	while (i < ptr->linecount)
	{
		if (ptr->tab)
			ft_free(ptr->tab[i]);
		i++;
	}
	exit(0);
	return (0);
}
