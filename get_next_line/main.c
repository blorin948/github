/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: blorin <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/26 17:14:00 by blorin       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/02 22:52:42 by blorin      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	int i = 0;
	int fd = open("salut.txt", O_RDONLY);
	char *line;
	while (i < 3)
	{
	get_next_line(fd, &line);
	printf("%s\n", line);
	i++;
	}
	free(line);
	close(fd);
}
