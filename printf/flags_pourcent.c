/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   flags_pourcent.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: blorin <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/19 17:29:26 by blorin       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/19 17:36:29 by blorin      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int		is_space_pourcent(char *str, int i, int *param)
{
	int preci;

	preci = 0;
	if (param[0] < 0)
		return (0);
	while ((str[i] == ' ' || str[i] == '-' || str[i] == '%'))
		i++;
	if ((str[i] == '*') || (str[i] >= '1' && str[i] <= '9'))
		return (1);
	return (0);
}

int		is_zero_pourcent(char *str, int i)
{
	int a;

	a = i;
	while (str[a] == '0' && str[i] != '\0' && str[i] != '.')
	{
		if (str[i] == '%')
			return (1);
		i++;
	}
	return (0);
}

void	write_space_pourcent(char *str, int i, int *param)
{
	int space;

	space = 0;
	if (param[0] < 0)
		param[0] = param[0] * -1;
	if (param[0] > 0)
	{
		while (param[0] > 1)
		{
			write(1, " ", 1);
			param[0]--;
		}
	}
	else
	{
		space = ft_atoi(str, i) - 1;
		while (space > 0)
		{
			write(1, " ", 1);
			space--;
		}
	}
}

void	write_zero_pourcent(char *str, int i, int *param)
{
	int zero;

	zero = 0;
	if (param[0] > 0)
	{
		zero = param[0];
		while (zero > 1)
		{
			write(1, "0", 1);
			zero--;
		}
	}
	else
	{
		zero = ft_atoi(str, i);
		while (zero > 1)
		{
			write(1, "0", 1);
			zero--;
		}
	}
}

int		add_space_before_pourcent(char *str, int i, int *param)
{
	if (str[i] == '%')
	{
		i++;
		return (0);
	}
	while (str[i] != '%')
	{
		if (str[i] == '-')
			return (0);
		i++;
	}
	while (str[i - 1] != '%')
		i--;
	if (is_space_pourcent(str, i, param) > 0)
	{
		write_space_pourcent(str, i, param);
		return (1);
	}
	if (is_zero_pourcent(str, i) > 0)
	{
		write_zero_pourcent(str, i, param);
		return (2);
	}
	return (0);
}
