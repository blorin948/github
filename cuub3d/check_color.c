/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_color.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: blorin <blorin@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/02 21:16:33 by blorin       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/08 19:13:46 by blorin      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"

int		check_color_sol2(char *line, t_storage *ptr, char red, int i)
{
	char blue;
	char green;

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
	return (1);
}

int		check_color_sol(char *line, t_storage *ptr, t_check *checkv)
{
	char	red;
	int		i;

	if (line[0] != 'F')
		return (0);
	i = 0;
	while (line[i] <= '0' || line[i] >= '9')
		i++;
	ptr->count_red = ft_atoi(line, &i);
	red = ptr->count_red;
	check_color_sol2(line, ptr, red, i);
	checkv->f++;
	return (1);
}

int		check_color_plaf2(char *line, t_storage *ptr, char red, int i)
{
	char blue;
	char green;

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
	ptr->plaf = (red & 0xff) | (green & 0xff) << 8 | (blue & 0xff) << 16;
	return (1);
}

int		check_color_plaf(char *line, t_storage *ptr, t_check *checkv)
{
	char	red;
	int		i;

	if (line[0] != 'C' || line[1] != ' ')
		return (0);
	i = 0;
	while (line[i] <= '0' || line[i] >= '9')
		i++;
	ptr->count_red = ft_atoi(line, &i);
	red = ptr->count_red;
	check_color_plaf2(line, ptr, red, i);
	checkv->c++;
	return (1);
}
