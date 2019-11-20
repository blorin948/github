/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   convert_s.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: blorin <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/19 19:43:48 by blorin       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/19 19:55:12 by blorin      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int		parse_string(int *c, char *s, int par, int k)
{
	while (s[par] != 's')
	{
		if (s[par] == '*' && s[par - 1] != '.')
			k++;
		par++;
		if (s[par] == '*' && s[par - 1] == '.')
			*c = 1;
	}
	return (k);
}

void	convert_type_string(char *s, va_list argue, int par)
{
	char	*str;
	int		i;
	int		k[3];
	int		c;
	int		tmp;

	assign_tab(k);
	tmp = par;
	c = 0;
	i = 0;
	k[1] = is_precision(s, par);
	k[0] = parse_string(&c, s, par, k[0]);
	if (k[0] > 0)
		k[0] = va_arg(argue, int);
	if (c > 0)
		k[1] = va_arg(argue, int);
	str = va_arg(argue, char*);
	i = ft_strlen(str);
	add_space_before(s, i, k, tmp);
	str = is_str_valid(str);
	write_string(str, k[1]);
	add_space_after(s, i, k, tmp);
}

int		is_precision(char *str, int i)
{
	int a;
	int k;
	int tmp;

	tmp = 0;
	k = 0;
	a = 0;
	while (str[i] != 'c' && str[i] != 's' && str[i] != 'p' && str[i] != 'd'
			&& str[i] != 'i' && str[i] != 'u' && str[i] != 'x' && str[i] != 'X')
	{
		if (str[i] == '.')
		{
			k++;
			tmp = i;
		}
		i++;
		if (k > 0 && str[i] == '*')
			k--;
	}
	if (k > 0)
	{
		a = ft_atoi(str, tmp);
		return (a);
	}
	return (-1);
}

void	write_string(char *str, int len)
{
	int i;

	i = 0;
	if (len == -1)
		ft_putstr(str);
	else if (str)
	{
		while (str[i] != '\0' && i < len)
		{
			write(1, &str[i], 1);
			i++;
		}
	}
}
