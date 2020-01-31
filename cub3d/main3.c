/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main3.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: blorin <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/17 21:48:06 by blorin       #+#   ##    ##    #+#       */
/*   Updated: 2019/12/17 21:56:07 by blorin      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(int ac, char **av)
{
	int fd = open(av[1], O_RDONLY);
	char *line;
	line = NULL;
	while (get_next_line(fd, &line))
	{
		printf("%s\n", line);
		free(line);
	}
}
