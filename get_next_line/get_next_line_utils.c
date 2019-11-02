/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_lines_utils.c                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: blorin <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/23 18:28:53 by blorin       #+#   ##    ##    #+#       */
/*   Updated: 2019/10/31 22:48:20 by blorin      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_slash(char **buf)
{
	static int i = 0;
	static int a = 0;
	while (buf)
	{
		while (buf[a][i] != '\0')
		{
			if (buf[a][i] == '\n')
			{
				i++;
				return (1);
			}
			i++;
		}
		i = 0;
		a++;
	}
	return (0);
}

int	count_words(char **buf)
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

char	*ft_strcpy(char **line, char **buf)
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
}
