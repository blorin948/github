/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   convert_p.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: blorin <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/19 18:19:30 by blorin       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/19 18:30:29 by blorin      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int		write_p(int n)
{
	char *str;

	str = convert_p(n);
	ft_putstr(str);
	return (1);
}

void	ft_free(char *str)
{
	if (str)
	{
		free(str);
		str = NULL;
	}
}

char	*add_0x(char *str)
{
	int		i;
	char	*new;
	int		a;

	a = 0;
	i = 0;
	a = ft_strlen(str);
	if (!(new = malloc(sizeof(a + 3))))
		return (0);
	new[i] = '0';
	i++;
	new[i] = 'x';
	i++;
	if (a < 9)
		new[i] = '1';
	a = 0;
	while (str[a])
	{
		new[i] = str[a];
		i++;
		a++;
	}
	new[i] = '\0';
	ft_free(str);
	return (new);
}

char	*convert_p(unsigned long n)
{
	unsigned long	tmp;
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
		c = convert_hexa_p(tmp);
		str[i] = c;
		i++;
		n = n / 16;
	}
	c = convert_hexa_p(n);
	str[i] = c;
	str[i + 1] = '\0';
	str = ft_strrev(str);
	str = add_0x(str);
	return (str);
}
