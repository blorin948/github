/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   write_flags.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: blorin <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/19 23:14:13 by blorin       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/19 23:23:36 by blorin      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

void	write_space2(int *param, int preci, char *str, int i)
{
	int space;

	space = 0;
	if (param[0] > 0)
	{
		space = param[0] - preci;
		while (space > 0)
		{
			write(1, " ", 1);
			space--;
		}
	}
	else
	{
		space = ft_atoi(str, i);
		space = space - preci;
		while (space > 0)
		{
			write(1, " ", 1);
			space--;
		}
	}
}

void	write_space(char *str, int len, int *param, int i)
{
	int preci;

	preci = 0;
	if (is_string(str, i) > 0)
		preci = count_precision_string(str, len, param[1], i);
	else
		preci = count_precision(str, len, param[1], i);
	if (param[2] > 0)
		preci++;
	if (param[0] < 0)
		param[0] = param[0] * -1;
	write_space2(param, preci, str, i);
}

int		add_space_after(char *str, int len, int *param, int i)
{
	while (str[i] != '%')
		i++;
	i++;
	if (str[i] == '%')
	{
		i++;
	}
	while (str[i] != '\0' && str[i] != 'c' && str[i] != 's' &&
			str[i] != 'p' && str[i] != 'd' && str[i] != 'i' && str[i] != 'u'
			&& str[i] != 'x' && str[i] != 'X' && str[i] != '%')
		i++;
	while (str[i - 1] != '%')
		i--;
	if (is_valid_after(str, i, param[0]) > 0)
		return (1);
	if (is_space_after(str, i) > 0)
	{
		write_space(str, len, param, i);
		return (1);
	}
	return (0);
}

int		add_negative(int *param, int len)
{
	if (param[2] > 0)
	{
		write(1, "-", 1);
		len++;
	}
	return (len);
}
