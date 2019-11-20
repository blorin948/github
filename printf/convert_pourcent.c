/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   convert_pourcent.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: blorin <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/19 17:38:33 by blorin       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/19 18:00:01 by blorin      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int		is_space_after_pourcent(char *str, int i)
{
	int preci;

	preci = 0;
	while (str[i] == ' ' || str[i] == '0' || str[i] == '-')
		i++;
	if ((str[i] == '*') || (str[i] >= '1' && str[i] <= '9'))
		return (1);
	return (0);
}

int		add_space_after_pourcent(char *str, int i, int *param)
{
	if (is_valid_after(str, i, param[0]) > 0)
		return (1);
	if (is_space_after_pourcent(str, i) > 0)
	{
		write_space_pourcent(str, i, param);
		return (1);
	}
	return (0);
}

int		*assign_tab(int *tab)
{
	tab[0] = 0;
	tab[1] = 0;
	tab[2] = 0;
	return (tab);
}

int		convert_type_pourcent(char *s, va_list argue, int par)
{
	int i;
	int k[3];
	int c;

	c = 0;
	assign_tab(k);
	par++;
	i = par;
	while (s[par] != '%')
	{
		if (s[par] == '*' && s[par - 1] != '.')
			k[0]++;
		par++;
		if (s[par] == '*' && s[par - 1] == '.')
			c++;
	}
	if (k[0] > 0)
		k[0] = va_arg(argue, int);
	if (c > 0)
		k[1] = va_arg(argue, int);
	k[1] = 0;
	add_space_before_pourcent(s, i, k);
	write(1, "%", 1);
	add_space_after_pourcent(s, i, k);
	return (1);
}
