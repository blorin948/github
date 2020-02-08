/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line_utils.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: blorin <blorin@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/07 23:32:01 by blorin       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/08 19:42:42 by blorin      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	char	*str;
	int		a;
	char	*tmp;

	a = 0;
	if (s1 == NULL)
		i = ft_strlen(s2);
	else
		i = ft_strlen(s1) + ft_strlen(s2);
	if (!(str = malloc(sizeof(char) * (i + 1))))
	{
		ft_free(s1);
		ft_free(s2);
		return (0);
	}
	i = 0;
	while (s1 && s1[a] != '\0')
		str[i++] = s1[a++];
	a = 0;
	while (s2 && s2[a] != '\0')
		str[i++] = s2[a++];
	str[i] = '\0';
	tmp = s2;
	ft_free(s1);
	return (str);
}

void	ft_free(void *s)
{
	if (s)
	{
		free(s);
		s = NULL;
	}
}

char	*ft_strdup_n(char *src)
{
	char	*dest;
	int		i;

	i = 0;
	while (src && src[i] != '\0' && src[i] != '\n')
		i++;
	if (!(dest = malloc(sizeof(char) * (i + 1))))
	{
		ft_free(src);
		return (0);
	}
	i = 0;
	while (src && src[i] != '\n' && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int		get_n(char *save)
{
	int i;
	int a;

	a = 0;
	i = 0;
	if (save == NULL)
		return (0);
	while (save[i] != '\0')
	{
		if (save[i] == '\n' && save[i] != '\0')
			return (1);
		i++;
	}
	return (0);
}
