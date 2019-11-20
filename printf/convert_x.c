/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   convert_x.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: blorin <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/19 18:30:55 by blorin       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/19 19:33:15 by blorin      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

char	*convert_x(unsigned int n)
{
	unsigned int	tmp;
	char			*str;
	int				i;
	char			c;

	tmp = 0;
	i = hexa_len(n);
	if (!(str = malloc(sizeof(i + 1))))
		return (0);
	i = 0;
	while (n >= 16)
	{
		tmp = n % 16;
		c = convert_hexa(tmp);
		str[i] = c;
		i++;
		n = n / 16;
	}
	c = convert_hexa(n);
	str[i] = c;
	str[i + 1] = '\0';
	str = ft_strrev(str);
	return (str);
}

char	*ft_capitalize(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 97 && str[i] <= 122)
			str[i] = str[i] - 32;
		i++;
	}
	return (str);
}

int		parse_hexa_m(int *c, char *s, int par, int k)
{
	while (s[par] != 'X')
	{
		if (s[par] == '*' && s[par - 1] != '.')
			k++;
		par++;
		if (s[par] == '*' && s[par - 1] == '.')
			*c = 1;
	}
	return (k);
}

void	convert_type_hexa_m(char *s, va_list argue, int par)
{
	unsigned int	n;
	int				i;
	int				k[3];
	int				c;
	int				tmp;

	assign_tab(k);
	tmp = par;
	i = 0;
	c = 0;
	if (is_precision(s, par) >= 0)
		k[1] = is_precision(s, par);
	k[0] = parse_hexa_m(&c, s, par, k[0]);
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
		ft_putstr(ft_capitalize(convert_x(n)));
	add_space_after(s, i, k, tmp);
}