/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   convert_type_x.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: blorin <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/19 19:24:48 by blorin       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/23 18:41:02 by blorin      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int		*parse_hexa(int *c, char *s, int par, int *k)
{
	if (is_precision(s, par) >= 0)
		k[1] = is_precision(s, par);
	while (s[par] != 'x')
	{
		if (s[par] == '*' && s[par - 1] != '.')
			k[0]++;
		par++;
		if (s[par] == '*' && s[par - 1] == '.')
			*c = 1;
	}
	return (k);
}

int		*parse_adress(int *c, char *s, int par, int *k)
{
	if (is_precision(s, par) >= 0)
		k[1] = is_precision(s, par);
	while (s[par] != 'p')
	{
		if (s[par] == '*' && s[par - 1] != '.')
			k[0]++;
		par++;
		if (s[par] == '*' && s[par - 1] == '.')
			*c = 1;
	}
	return (k);
}

int		convert_type_hexa(char *s, va_list argue, int par)
{
	unsigned int	n;
	int				i;
	int				k[3];
	int				c;
	char			*del;

	assign_tab(k);
	i = 0;
	parse_hexa(&k[2], s, par, k);
	if (k[0] > 0)
		k[0] = va_arg(argue, int);
	if (k[2] > 0)
		k[1] = va_arg(argue, int);
	n = va_arg(argue, unsigned int);
	if (!(((is_precision(s, par) == 0) || (k[1] == 0 && k[2] > 0)) && (n == 0)))
		i = hexa_len_hexa(n);
	c = add_space_before(s, i, k, par);
	c = c + add_precision(i, k[1]);
	del = convert_x(n);
	if (!(((is_precision(s, par) == 0) || (k[1] == 0 && k[2] > 0)) && (n == 0)))
		c = c + ft_putstr(del);
	c = c + add_space_after(s, i, k, par);
	ft_free(del);
	k[2] = 0;
	return (c);
}

int		convert_type_adress(char *s, va_list argue, int par)
{
	unsigned long	n;
	int				i;
	int				k[3];
	int				c;
	char			*del;

	c = 0;
	assign_tab(k);
	i = 0;
	parse_adress(&c, s, par, k);
	if (k[0] > 0)
		k[0] = va_arg(argue, int);
	if (c > 0)
		k[1] = va_arg(argue, int);
	n = va_arg(argue, unsigned long);
	i = hexa_len(n) + 3;
	if (i > 13)
		i--;
	c = add_space_before(s, (int)i, k, par) - c;
	c = c + add_precision(i, k[1]);
	del = convert_p(n);
	c = c + ft_putstr(del);
	c = c + add_space_after(s, i, k, par);
	ft_free(del);
	return (c);
}

char	*is_str_valid(char *str)
{
	char	*s;
	int		i;

	if (str)
		return (str);
	i = 7;
	s = "(null)";
	return (s);
}
