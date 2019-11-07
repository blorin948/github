/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: blorin <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/23 17:39:20 by blorin       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/07 02:04:30 by blorin      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"

char	*out_slash(char *save)
{
	int		i;
	char	*str;
	int		a;

	str = NULL;
	i = 0;
	a = 0;
	while (save[i] != '\n' && save[i] != '\0')
	{
		i++;
		a++;
	}
	while (save[a] != '\0')
		a++;
	if (!(str = malloc(sizeof(char) * (a + 1))))
		return (0);
	i++;
	a = 0;
	while (save[i] != '\0')
		str[a++] = save[i++];
	str[a] = '\0';
	return (str);
}

char	*ft_bzero(char *s, int n)
{
	int i;

	i = 0;
	n++;
	while (n--)
	{
		s[i] = '\0';
		i++;
	}
	return (s);
}

int		check_error(int fd, char **line)
{
	if (line == NULL || BUFFER_SIZE <= 0)
		return (0);
	if (fd == -1)
		return (-1);
	return (2);
}

int		get_next_line(int fd, char **line)
{
	static char	*save = NULL;
	int			ret;
	char		buf[BUFFER_SIZE + 1];

	ft_bzero(buf, BUFFER_SIZE);
	ret = 0;
	if (check_error(fd, line) != 2)
		return (-1);
	*line = ft_strdup(save);
	if ((get_slash(save) == 1) && (save = out_slash(save)))
		return (1);
	while ((ret = read(fd, buf, BUFFER_SIZE) > 0))
	{
		buf[BUFFER_SIZE] = '\0';
		save = ft_strjoin(save, buf);
		if (get_slash(save) == 1)
		{
			*line = ft_strdup(save);
			save = out_slash(save);
			return (1);
		}
	}
	free(save);
	save = NULL;
	return (0);
}
