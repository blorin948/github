/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blorin <blorin@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 15:36:38 by blorin            #+#    #+#             */
/*   Updated: 2020/02/22 15:50:30 by blorin           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*str;
	int		a;

	a = 0;
	if (s1 == NULL)
		i = ft_strlen(s2);
	else
		i = ft_strlen(s1) + ft_strlen(s2);
	if (!(str = malloc(sizeof(char) * i + 1)))
		return (0);
	i = 0;
	while (s1 && s1[a] != '\0')
		str[i++] = s1[a++];
	a = 0;
	while (s2[a] != '\0')
	{
		str[i] = s2[a];
		a++;
		i++;
	}
	str[i] = '\0';
	return (str);
}

void		*ft_memset(void *s, int c, size_t n)
{
	unsigned char *ptr;

	ptr = s;
	while (n > 0)
	{
		*ptr = c;
		ptr++;
		n--;
	}
	return (s);
}

char		*ft_strdup(const char *src)
{
	char	*dest;
	int		i;

	i = 0;
	while (src[i] != '\0')
		i++;
	if (!(dest = malloc(sizeof(char) * (i + 1))))
		return (0);
	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = (char)src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char		*ft_strchr(const char *s, int c)
{
	int i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	if (c == s[i])
		return ((char *)s + i);
	return (0);
}

size_t		ft_strlen(const char *s)
{
	int i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}
