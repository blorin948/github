/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: blorin <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/23 17:39:20 by blorin       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/02 22:53:02 by blorin      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"

char *out_slash(char *save)
{
	int i;
	char *str;
	int a;

	i = 0;
	a = 0;
	while (save[i] != '\n' && save[i] != '\0')
	{
		i++;
		a++;
	}
	while (save[a] != '\0')
		a++;
	if (!(str = malloc(sizeof(char) * a + 1)))
		return (0);
	i++;
	a = 0;
	while (save[i] != '\0')
	{
		str[a] = save[i];
		i++;
		a++;
	}
	return (str);
}

char	*ft_strdup(char *src)
{
	char	*dest;
	int		i;

	i = 0;
	while (src[i] != '\n')
		i++;
	if (!(dest = malloc(sizeof(char) * (i + 1))))
		return (0);
	i = 0;
	while (src[i] != '\n')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}


int get_next_line(int fd, char **line)
{
	static char *save;
	int ret;
	char buf[BUFFER_SIZE + 1];

	ret = 0;
	while (ret >= 0)
	{
		if (get_slash(save) == 0)
		{
			ret = read(fd, buf, BUFFER_SIZE);
			buf[BUFFER_SIZE] = '\0';
			save = ft_strjoin(save, buf);
		}
		if (get_slash(save) == 1)
		{
			*line = ft_strdup(save);
			save = out_slash(save);
			return (1);
		}
		if (ret == 0 || ret != BUFFER_SIZE)
		{
			free(save);
			return (0);
		}
		ret = 0;
	}
	return (-1);
}
