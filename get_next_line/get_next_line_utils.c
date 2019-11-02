/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_lines_utils.c                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: blorin <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/23 18:28:53 by blorin       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/02 22:45:16 by blorin      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_slash(char *buf)
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

/*int	count_words(char *buf)
{
	static int i = 0;
	static int a = 0;
	int words;

	words = 0;
	while(buf)
	{
		while (buf[a][i] != '\0')
		{
			if (buf[a][i] == '\n')
			{
				i++;
				return (words + 1);
			}
			i++;
			words++;
		}
		a++;
		i = 0;
	}
	return (1);
}

char	*ft_strcpy(char **line, char *buf)
{
	static int a = 0;
	static int i = 0;	
	int k;

	k = 0;
	while (buf)
	{
		while (buf[a][i] != '\0')
		{	
			line[k] = &buf[a][i];
			k++;
			i++;
			if (buf[a][i] == '\n')
				return (*line);
		}
		a++;
		i = 0;
	}
	return (*line);
}*/

int	ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char		*ft_strjoin(char *s1, char *s2)
{
	int		i;
	char	*str;
	int		a;

	a = 0;
	if (s1)
		i = ft_strlen(s1) + ft_strlen(s2);
	else
		i = ft_strlen(s2);
	if (!(str = malloc(sizeof(char) * i + 1)))
		return (0);
	i = 0;
	while (s1 && s1[a] != '\0')
	{
		str[i] = s1[a];
		a++;
		i++;
	}
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
