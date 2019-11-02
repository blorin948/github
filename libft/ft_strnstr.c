/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strnstr.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: blorin <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/11 11:13:06 by blorin       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/02 17:41:09 by blorin      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t n)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (to_find[0] == '\0')
		return ((char *)str);
	while (str[i] != '\0' && n > 0)
	{
		n = n + j;
		j = 0;
		while (str[i + j] == to_find[j] && n > 0)
		{
			j++;
			n--;
			if (to_find[j] == '\0')
				return ((char *)str + i);
		}
		i++;
		n--;
	}
	return (0);
}
