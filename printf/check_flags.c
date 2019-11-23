/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_flags.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: blorin <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/19 23:02:46 by blorin       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/21 21:32:19 by blorin      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int		is_valid_after(char *str, int i, int param)
{
	if (param < 0)
		return (0);
	while (str[i] != 'c' && str[i] != 's' && str[i] != 'p' &&
			str[i] != 'd' && str[i] != 'i' && str[i] != 'u' &&
			str[i] != 'x' && str[i] != 'X' && str[i] != '%')
	{
		if (str[i] == '-')
			return (0);
		i++;
	}
	return (1);
}

int		is_valid_before(char *str, int i, int param)
{
	if (param < 0)
		return (1);
	while (str[i] != 'c' && str[i] != 's' && str[i] != 'p' && str[i] != 'd' &&
			str[i] != 'i' && str[i] != 'u' && str[i] != 'x' &&
			str[i] != 'X' && str[i] != '%')
	{
		if (str[i] == '-')
			return (1);
		i++;
	}
	return (0);
}

int		is_zero(char *str, int i)
{
	int a;

	a = i;
	while (str[a] == '0' && str[i] != '\0' && str[i] != '.')
	{
		if (str[i] == 'c' || str[i] == 's' || str[i] == 'p' || str[i] == 'd' ||
				str[i] == 'i' || str[i] == 'u' || str[i] == 'x' || str[i] == 'X'
				|| str[i] == '%')
			return (1);
		i++;
	}
	return (0);
}

int		write_zero(char *str, int len, int *param, int i)
{
	int zero;
	int c;

	c = 0;
	zero = 0;
	if (param[0] > 0)
	{
		zero = param[0] - len;
		while (zero-- > 0)
		{
			write(1, "0", 1);
			c++;
		}
	}
	else
	{
		zero = ft_atoi(str, i);
		zero = zero - len;
		while (zero-- > 0)
		{
			write(1, "0", 1);
			c++;
		}
	}
	return (c);
}

int		is_space_after(char *str, int i)
{
	int preci;

	preci = 0;
	while (str[i] == ' ' || str[i] == '0' || str[i] == '-' || str[i] == '%')
		i++;
	if ((str[i] == '*') || (str[i] >= '1' && str[i] <= '9'))
		return (1);
	while (str[i] != 'c' && str[i] != 's' && str[i] != 'p' && str[i] != 'd' &&
			str[i] != 'i' && str[i] != 'u' && str[i] != 'x' && str[i] != 'X')
	{
		if (str[i] == '.')
			preci++;
		i++;
	}
	return (0);
}
