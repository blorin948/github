/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ftc1.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: blorin <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/10 01:26:40 by blorin       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/11 06:24:35 by blorin      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

char what_type(char *str)
{
	static int i = 0;
	char c;

	if (!str)
		return (0);
	while (str[i] != '%' && str[i] != '\0')
		i++;
	while (str[i] != '\0')
	{
		c = str[i];
		i++;
		if (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i' ||
			c == 'u' || c == 'x' || c == 'X')
			break ;
	}
	return (c);
}
		
	



