/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   union.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: blorin <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/12 16:01:21 by blorin       #+#   ##    ##    #+#       */
/*   Updated: 2019/12/12 16:24:15 by blorin      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <unistd.h>

int		check2(char *s1, char *s2, int i)
{
	int a;

	a = i;
	i = 0;
	while (s1[i])
	{
		if (s1[i] == s2[a])
			return (0);
		i++;
	}
	i = 0;
	while (i < a)
	{
		if (s2[i] == s2[a])
			return (0);
		i++;
	}
	return (1);
}

int		check(char *s1, int i)
{
	int a;

	a = i;
	i = 0;
	while (i < a)
	{
		if (s1[i] == s1[a])
			return (0);
		i++;
	}
	return (1);
}

void	ft_union(char *s1, char *s2)
{
	int i = 0;
	while (s1[i])
	{
		if (check2(s1,s2, i) > 0)
			write(1, &s1[i], 1);
		i++;
	}
	i = 0;
	while (s2[i])
	{
		if (check2(s1, s2, i) > 0)
			write(1, &s2[i], 1);
		i++;
	}
}

int main(int ac, char **av)
{
	if (ac == 3)
		ft_union(av[1], av[2]);
	write(1, "\n", 1);
}
