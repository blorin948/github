/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fct.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: blorin <blorin@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/03 01:34:49 by blorin       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/11 20:21:31 by blorin      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../cub3d.h"

int		parsing(t_storage *ptr)
{
	int i;

	i = 0;
	while (ptr->map[i] != '\0')
	{
		if (ptr->map[i] != '1' && ptr->map[i] != '3' && ptr->map[i] !=
		'0' && ptr->map[i] != 'E' && ptr->map[i] != 'S' && ptr->map[i] != 'W'
		&& ptr->map[i] != 'N' && ptr->map[i] != '2')
			return (error(ptr, "map"));
		if (ptr->map[i] == '3')
			ptr->checkdoor++;
		i++;
	}
	return (1);
}

int		ft_atoi(char *line, int *i)
{
	int count;

	count = 0;
	while (line[*i] >= '0' && line[*i] <= '9' && line[*i] != '\0')
	{
		count = count * 10 + line[*i] - 48;
		*i = *i + 1;
	}
	return (count);
}

int		ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && (s1[i] != '\0' || s2[i] != '\0'))
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

int		check_argue(t_storage *ptr, int ac, char **av)
{
	if (ac != 2)
	{
		if (ac == 3)
		{
			if (ft_strcmp(av[2], "-save") != 0)
				return (error(ptr, "arguements"));
			else
			{
				ptr->save++;
				return (1);
			}
		}
		return (error(ptr, "arguements"));
	}
	return (1);
}

void	ft_putstr(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}
