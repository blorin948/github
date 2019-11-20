/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   convert_u_d.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: blorin <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/19 19:55:49 by blorin       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/19 23:01:25 by blorin      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int		parse_unsigned(int *c, char *s, int par, int k)
{
	while (s[par] != 'u')
	{
		if (s[par] == '*' && s[par - 1] != '.')
			k++;
		par++;
		if (s[par] == '*' && s[par - 1] == '.')
			*c = 1;
	}
	return (k);
}

void	convert_type_unsigned(char *s, va_list argue, int par)
{
	int n;
	int i;
	int k[3];
	int c;
	int tmp;

	assign_tab(k);
	tmp = par;
	c = 0;
	i = 0;
	if (is_precision(s, par) >= 0)
		k[1] = is_precision(s, par);
	k[0] = parse_unsigned(&c, s, par, k[0]);
	if (k[0] > 0)
		k[0] = va_arg(argue, int);
	if (c > 0)
		k[1] = va_arg(argue, int);
	n = va_arg(argue, int);
	if (!(((is_precision(s, tmp) == 0) || (k[1] == 0 && c > 0)) && (n == 0)))
		i = ft_intlen(n);
	add_space_before(s, i, k, tmp);
	add_precision(i, k[1]);
	if (!(((is_precision(s, tmp) == 0) || (k[1] == 0 && c > 0)) && (n == 0)))
		ft_putnbr_unsigned(n);
	add_space_after(s, i, k, tmp);
}

void	add_precision_int(int len, int param)
{
	while (len < param)
	{
		write(1, "0", 1);
		len++;
	}
}

int		parse_int(int *c, char *s, int par, int k)
{
	while (s[par] != 'd' && s[par] != 'i')
	{
		if (s[par] == '*' && s[par - 1] != '.')
			k++;
		par++;
		if (s[par] == '*' && s[par - 1] == '.')
			*c = 1;
	}
	return (k);
}

void	convert_type_int2(int n)
{
	if (n < 0)
		n = n * -1;
	ft_putnbr(n);
}

void	convert_type_int(char *s, va_list argue, int par)
{
	int n;
	int i;
	int k[3];
	int c;

	assign_tab(k);
	c = 0;
	i = 0;
	if (is_precision(s, par) >= 0)
		k[1] = is_precision(s, par);
	k[0] = parse_int(&c, s, par, k[0]);
	if (k[0] > 0)
		k[0] = va_arg(argue, int);
	if (c > 0)
		k[1] = va_arg(argue, int);
	n = va_arg(argue, int);
	if (!(((is_precision(s, par) == 0) || (k[1] == 0 && c > 0)) && (n == 0)))
		i = ft_intlen(n);
	if (n < 0)
		k[2] = 1;
	add_space_before(s, i, k, par);
	add_precision_int(i, k[1]);
	if (!(((is_precision(s, par) == 0) || (k[1] == 0 && c > 0)) && (n == 0)))
		convert_type_int2(n);
	add_space_after(s, i, k, par);
}
