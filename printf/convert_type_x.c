/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   convert_type_x.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: blorin <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/19 19:24:48 by blorin       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/19 19:42:47 by blorin      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int		parse_hexa(int *c, char *s, int par, int k)
{
	while (s[par] != 'x')
	{
		if (s[par] == '*' && s[par - 1] != '.')
			k++;
		par++;
		if (s[par] == '*' && s[par - 1] == '.')
			*c = 1;
	}
	return (k);
}

int		parse_adress(int *c, char *s, int par, int k)
{
	while (s[par] != 'p')
	{
		if (s[par] == '*' && s[par - 1] != '.')
			k++;
		par++;
		if (s[par] == '*' && s[par - 1] == '.')
			*c = 1;
	}
	return (k);
}

void	convert_type_hexa(char *s, va_list argue, int par)
{
	unsigned int	n;
	int				i;
	int				k[3];
	int				c;
	int				tmp;

	tmp = par;
	c = 0;
	assign_tab(k);
	i = 0;
	if (is_precision(s, par) >= 0)
		k[1] = is_precision(s, par);
	k[0] = parse_hexa(&c, s, par, k[0]);
	if (k[0] > 0)
		k[0] = va_arg(argue, int);
	if (c > 0)
		k[1] = va_arg(argue, int);
	n = va_arg(argue, unsigned int);
	if (!(((is_precision(s, tmp) == 0) || (k[1] == 0 && c > 0)) && (n == 0)))
		i = hexa_len_hexa(n);
	add_space_before(s, i, k, tmp);
	add_precision(i, k[1]);
	if (!(((is_precision(s, tmp) == 0) || (k[1] == 0 && c > 0)) && (n == 0)))
		ft_putstr(convert_x(n));
	add_space_after(s, i, k, tmp);
}

void	convert_type_adress(char *s, va_list argue, int par)
{
	unsigned long	n;
	int				i;
	int				k[3];
	int				c;
	int				tmp;

	tmp = par;
	c = 0;
	assign_tab(k);
	i = 0;
	if (is_precision(s, par) >= 0)
		k[1] = is_precision(s, par);
	k[0] = parse_adress(&c, s, par, k[0]);
	if (k[0] > 0)
		k[0] = va_arg(argue, int);
	if (c > 0)
		k[1] = va_arg(argue, int);
	n = va_arg(argue, unsigned long);
	i = hexa_len(n) + 3;
	if (i > 13)
		i--;
	add_space_before(s, (int)i, k, tmp);
	add_precision(i, k[1]);
	ft_putstr(convert_p(n));
	add_space_after(s, i, k, tmp);
}

char	*is_str_valid(char *str)
{
	char	*s;
	int		i;

	if (str)
		return (str);
	i = 7;
	if (!(s = malloc(sizeof(char) * 7)))
		return (0);
	s = "(null)";
	s[i] = '\0';
	return (s);
}
