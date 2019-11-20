/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: blorin <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/19 16:33:52 by blorin       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/19 16:57:26 by blorin      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

void	write_between(char *str)
{
	static int i = 0;

	while (str[i] != '%' && str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
	}
	if (str[i] == '%')
	{
		i++;
		while (str[i] != 'c' && str[i] != 's' && str[i] != 'p' &&
			str[i] != 'd' && str[i] != 'i' && str[i] != 'u' &&
			str[i] != 'x' && str[i] != 'X' && str[i] != '%')
			i++;
		i++;
	}
}

void	write_end(char *str, int par)
{
	while (str[par] != '\0')
	{
		write(1, &str[par], 1);
		par++;
	}
}

int		parse_str2(char *str, int par, int c)
{
	while (str[par - 1] != '%' && par > 0)
		par--;
	if (c > 0)
		return (par);
	if (str[par - 1] == '%')
	{
		while (str[par] != 'c' && str[par] != 's' && str[par] != 'p' &&
			str[par] != 'd' && str[par] != 'i' && str[par] != 'u' &&
			str[par] != 'x' && str[par] != 'X')
			par++;
		par++;
	}
	return (par);
}

int		parse_str(char *str, int c)
{
	static int	par = 0;
	int			tmp;

	tmp = 0;
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
	par = parse_str2(str, par, c);
	if (c > 0)
		return (par);
	return (par);
}
