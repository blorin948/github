/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: blorin <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/19 16:33:52 by blorin       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/23 18:44:30 by blorin      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int		write_between(char *str, int i)
{
	int				c;

	c = 0;
	if (str[i] == '%')
	{
		i++;
		while (str[i] != 'c' && str[i] != 's' && str[i] != 'p' &&
			str[i] != 'd' && str[i] != 'i' && str[i] != 'u' &&
			str[i] != 'x' && str[i] != 'X' && str[i] != '%')
			i++;
		i++;
	}
	while (str[i] != '%' && str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
		c++;
	}
	return (c);
}

int		write_end(char *str, int par)
{
	int c;

	c = 0;
	while (str[par] != '\0')
	{
		write(1, &str[par], 1);
		par++;
		c++;
	}
	return (c);
}

int		parse_str2(char *str, int par)
{
	if (par > 0)
	{
		par++;
		while (str[par] != 'c' && str[par] != 's' && str[par] != 'p' &&
			str[par] != 'd' && str[par] != 'i' && str[par] != 'u' &&
			str[par] != 'x' && str[par] != 'X' && str[par] != '%')
			par++;
		par++;
		return (par);
	}
	return (0);
}

int		parse_str(char *str)
{
	static int	par = 0;
	static int	tmp = 0;
	int			tmp2;

	tmp2 = 0;
	while (str[par] != '\0')
	{
		if (str[par] == '%')
		{
			tmp = par;
			par++;
			while (str[par] != 'c' && str[par] != 's' && str[par] != 'p' &&
				str[par] != 'd' && str[par] != 'i' && str[par] != 'u' &&
				str[par] != 'x' && str[par] != 'X' && str[par] != '%')
				par++;
			if (str[par] == '%')
				par++;
			return (tmp);
		}
		par++;
	}
	tmp2 = parse_str2(str, tmp);
	par = 0;
	tmp = 0;
	return (tmp2);
}
