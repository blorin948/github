/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memcpy.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: blorin <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/09 20:00:37 by blorin       #+#   ##    ##    #+#       */
/*   Updated: 2019/10/30 20:26:02 by blorin      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*str;
	const char	*s;

	str = dest;
	s = src;
	if (dest == 0 && src == 0)
		return (0);
	while (n > 0)
	{
		*str = *s;
		str++;
		s++;
		n--;
	}
	return (dest);
}
