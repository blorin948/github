/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_cub.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: blorin <blorin@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/02 21:00:09 by blorin       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/08 20:04:49 by blorin      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"

int		check_text_s(char *line, t_storage *ptr, t_check *checkv)
{
	int i;
	int a;

	i = 3;
	a = 0;
	if (line[0] != 'S' || line[1] != 'O')
		return (0);
	checkv->so++;
	ptr->texture.sud = ft_strdup(line + i);
	return (1);
}

int		check_sprite(char *line, t_storage *ptr, t_check *checkv)
{
	int i;
	int a;

	i = 2;
	a = 0;
	if (line[0] != 'S' || line[1] == 'O')
		return (0);
	checkv->sprite++;
	ptr->texture.sprite = ft_strdup(line + i);
	return (1);
}

int		check_skybox(char *line, t_storage *ptr)
{
	int i;
	int a;

	i = 3;
	a = 0;
	if (line[0] == '\0')
		return (1);
	if (line[0] != 'C' || line[1] != 'T')
		return (0);
	ptr->che.sky++;
	ptr->texture.skybox = ft_strdup(line + i);
	return (1);
}

int		check2(char *line, t_storage *ptr, t_check *checkv)
{
	int i;

	i = 0;
	i = i + check_reso(line, ptr, checkv);
	i = i + check_color_sol(line, ptr, checkv);
	i = i + check_color_plaf(line, ptr, checkv);
	i = i + check_text_e(line, ptr, checkv);
	i = i + check_text_n(line, ptr, checkv);
	i = i + check_text_w(line, ptr, checkv);
	i = i + check_text_s(line, ptr, checkv);
	i = i + check_sprite(line, ptr, checkv);
	i = i + check_skybox(line, ptr);
	i = i + check_text_P(line, ptr, checkv);
	//printf("%s\n", line);
	if (i == 0)
		return (error(ptr, ".cub file"));
	return (1);
}

int		check(char *line, t_storage *ptr, t_check *checkv)
{
	int				i;
	static int		a = 0;

	i = 0;
	if (line[0] == '1')
		a++;
	if (a > 0 && line[0] != '1')
		return (error(ptr, "map"));
	if (line[0] != '1')
	{
		check2(line, ptr, checkv);
		return (0);
	}
	if (line[0] == '1')
		return (1);
	a = 0;
	return (0);
}
