/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ftc2.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: blorin <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/19 22:57:06 by blorin       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/19 23:02:22 by blorin      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_atoi(char *str, int i)
{
	int n;

	n = 0;
	while (str[i] == ' ' || str[i] == '.' ||
			str[i] == '-' || str[i] == '%' || str[i] == '0')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + (str[i] - 48);
		i++;
	}
	return (n);
}

void	add_precision(int len, int param)
{
	while (len < param)
	{
		write(1, "0", 1);
		len++;
	}
}

int		ft_intlen(int n)
{
	int len;

	len = 1;
	if (n < 0)
		n = n * -1;
	while (n >= 10)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str && str[i] != '\0')
		i++;
	if (!str)
		i = 6;
	return (i);
}

void	ft_putstr(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
	}
}