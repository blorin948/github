/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: blorin <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/23 17:39:20 by blorin       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/02 19:06:15 by blorin      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"

int get_next_line(int fd, char **line)
{
	static char **buf;
	int ret;
	static int i = 0;
	static int ind = 0;

	ret = 0;
	while (ret >= 0)
	{
			printf("lol\n");
		if (i < BUFFER_SIZE)
		{
			if (!(buf[ind] = malloc(sizeof(char *) * BUFFER_SIZE + 1)))
				return (0);
			printf("lol\n");
			ret = read(fd, buf[ind], BUFFER_SIZE);
			buf[ind][BUFFER_SIZE] = '\0';
			ind++;
		}
		if (get_slash(buf) == 1)
		{
			if (!(*line = malloc(sizeof(char) * count_words(buf))))
			*line = ft_strcpy(line, buf);
			i = count_words(buf) + i;
			return (1);
		}
		if (ret == 0)
		{
			while (ind > 0)
			{
				free(buf[ind]);
				ind--;
			}
			return (0);
		}
		ret = 0;
	}
	return (-1);
}
