/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_lines_utils.c                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: blorin <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/23 18:28:53 by blorin       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/06 23:28:42 by blorin      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"

int			get_slash(char *buf)
{
	int i;

	i = 0;
	if (buf == NULL)
		return (0);
	while (buf[i] != '\0')
	{
		if (buf[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int			ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char		*ft_strjoin(char *s1, char *s2)
{
	int		i;
	char	*str;
	int		a;

	str = NULL;
	a = 0;
	i = 0;
	if (s1 == NULL)
		return (s2);
	else
		i = ft_strlen(s1) + ft_strlen(s2);
	if (!(str = malloc(sizeof(char) * (i + 1))))
		return (0);
	i = 0;
	if (!(s1 == NULL))
	{
		while (s1[a] != '\0')
			str[i++] = s1[a++];
		a = 0;
	}
	while (s2[a] != '\0')
		str[i++] = s2[a++];
	str[i] = '\0';
	return (str);
}

char		*ft_strdup(char *src)
{
	char	*dest;
	int		i;

	dest = NULL;
	i = 0;
	if (src != NULL)
	{
		while (src[i] != '\n' && src[i] != '\0')
			i++;
	}
	if (!(dest = malloc(sizeof(char) * (i + 1))))
		return (0);
	i = 0;
	if (src != NULL)
	{
		while (src[i] != '\n' && src[i] != '\0')
		{
			dest[i] = src[i];
			i++;
		}
	}
	dest[i] = '\0';
	return (dest);
}
