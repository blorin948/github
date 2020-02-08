/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   inter.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: blorin <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/12 16:23:00 by blorin       #+#   ##    ##    #+#       */
/*   Updated: 2019/12/12 16:48:56 by blorin      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

int	check(char *s1, char *s2, int a)
{
	int i;

	i = 0;
	while (i < a)
	{
		if (s1[i] == s1[a])
			return (0);
		i++;
	}
	i = 0;
	while (s2[i])
	{
		if (s2[i] == s1[a])
			return (1);
		i++;
	}
	return (0);
}

void	ft_inter(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i])
	{
		if (check(s1, s2, i) > 0)
			write(1, &s1[i], 1);
		i++;
	}
}

int main(int ac, char **av)
{
	if (ac == 3)
		ft_inter(av[1], av[2]);
	write(1, "\n", 1);
}
