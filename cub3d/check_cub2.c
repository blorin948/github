/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_cub2.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: blorin <blorin@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/02 22:10:13 by blorin       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/02 22:17:41 by blorin      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"

int		check_reso(char *line, t_storage *ptr, t_check *checkv)
{
	int i;
	int count;

	i = 0;
	count = 0;
	if (line[0] != 'R')
		return (0);
	while (((line[i] <= '0' || line[i] >= '9')) && line[i] != 45)
		i++;
	count = ft_atoi(line, &i);
	ptr->resox = count;
	i++;
	count = ft_atoi(line, &i);
	ptr->resoy = count;
	if (ptr->resox > 2560)
		ptr->resox = 2560;
	if (ptr->resoy > 1395)
		ptr->resoy = 1395;
	checkv->r++;
	if (ptr->resoy <= 0 || ptr->resox <= 0)
		return (error(ptr, "resolution"));
	return (1);
}

int		check_text_e(char *line, t_storage *ptr, t_check *checkv)
{
	int i;
	int a;

	i = 3;
	a = 0;
	if (line[0] != 'E' || line[1] != 'A')
		return (0);
	checkv->ea++;
	ptr->texture.est = ft_strdup(line + i);
	return (1);
}

int		check_text_n(char *line, t_storage *ptr, t_check *checkv)
{
	int i;
	int a;

	i = 3;
	a = 0;
	if (line[0] != 'N' || line[1] != 'O')
		return (0);
	checkv->no++;
	ptr->texture.nord = ft_strdup(line + i);
	return (1);
}

int		check_text_w(char *line, t_storage *ptr, t_check *checkv)
{
	int i;
	int a;

	i = 3;
	a = 0;
	if (line[0] != 'W' || line[1] != 'E')
		return (0);
	checkv->we++;
	ptr->texture.ouest = ft_strdup(line + i);
	return (1);
}
