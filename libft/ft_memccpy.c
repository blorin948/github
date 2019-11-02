/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memccpy.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: blorin <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/11 11:43:16 by blorin       #+#   ##    ##    #+#       */
/*   Updated: 2019/10/30 20:49:54 by blorin      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	int					i;
	unsigned char		*str;
	const unsigned char	*s;

	i = 0;
	str = dest;
	s = src;
	while (n--)
	{
		*str = *s;
		if (*s == (unsigned char)c)
		{
			i++;
			return (dest + i);
		}
		str++;
		s++;
		i++;
	}
	return (0);
}
