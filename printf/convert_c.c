/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   convert_c_s_d.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: blorin <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/11 04:07:38 by blorin       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/19 23:32:38 by blorin      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

void	convert_type_char(char *s, va_list argue, int par)
{
	char z;
	int i;
	int k[3];
	int tmp;

	tmp = par;
	k[0] = 0;
	k[1] = 0;
	k[2] = 0;
	i = 1;
	while (s[par] != 'c')
	{
		if (s[par] == '*')
			k[0]++;
		par++;
	}
	if (k[0] > 0)
		k[0] = va_arg(argue, int);
	z = va_arg(argue, int);
	add_space_before(s, i, k, tmp);
	write(1, &z, 1);
	add_space_after(s, i, k, tmp);
}

int		add_space_before2(char *str, int i)
{
	while (str[i] != '%')
		i++;
	i++;
	if (str[i] == '%')
	{
		i++;
		return (0);
	}
	while (str[i] != '\0' && str[i] != 'c' && str[i] != 's' &&
			str[i] != 'p' && str[i] != 'd' && str[i] != 'i' &&
			str[i] != 'u' && str[i] != 'x' && str[i] != 'X' && str[i] != '%')
		i++;
	while (str[i - 1] != '%')
		i--;
	return (i);
}

int		add_space_before(char *str, int len, int *param, int i)
{	
	i = add_space_before2(str, i);
	if (i == 0)
		return (0);
	if (is_valid_before(str, i, param[0]) > 0)
	{
		add_negative(param, len);
		return (1);
	}
	if (is_space(str, i) > 0)
	{
	  write_space(str, len, param, i);
	  add_negative(param, len);
	  return (1);
	}
	len = add_negative(param, len);
	if (is_zero(str, i) > 0)
	{
		write_zero(str, len, param, i);
		return (2);
	}
	return (0);
}
