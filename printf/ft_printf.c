/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: blorin <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/16 16:15:09 by blorin       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/19 23:32:42 by blorin      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int		is_pourcent(char *s)
{
	static int	i = 0;
	int			a;

	a = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '%')
		{
			i++;
			while (s[i] != 'c' && s[i] != 's' && s[i] != 'p' && s[i] != 'd' &&
					s[i] != 'i' && s[i] != 'u' && s[i] != 'x' &&
					s[i] != 'X' && s[i] != '%')
				i++;
			a++;
			break ;
		}
		i++;
	}
	if (a > 0)
	{
		i++;
		return (1);
	}
	return (0);
}

int		convert_all(va_list_wrap *copy, char *s, int par, char c)
{
	int z;

	z = 0;
	if (c == 'c')
		convert_type_char(s, copy->arg, par);
	else if (c == 's')
		convert_type_string(s, copy->arg, par);
	else if (c == 'p')
		convert_type_adress(s, copy->arg, par);
	else if (c == 'd' || c == 'i')
		convert_type_int(s, copy->arg, par);
	else if (c == 'u')
		convert_type_unsigned(s, copy->arg, par);
	else if (c == 'x')
		convert_type_hexa(s, copy->arg, par);
	else if (c == 'X')
		convert_type_hexa_m(s, copy->arg, par);
	else if (c == '%')
		z = convert_type_pourcent(s, copy->arg, par);
	return (z);
}

int		use_argue(char *s, va_list argue)
{
	char			c;
	int				par;
	int				z;
	va_list_wrap	copy;

	z = 0;
	va_copy(copy.arg, argue);
	while (is_pourcent(s) > 0)
	{
		z = 0;
		write_between(s);
		c = what_type(s);
		par = parse_str(s, z);
		z = convert_all(&copy, s, par, c);
	}
	par = parse_str(s, z);
	write_end(s, par);
	return (1);
}

int		ft_printf(char *s, ...)
{
	va_list argue;

	va_start(argue, s);
	use_argue(s, argue);
	return (1);
}

int main()
{
//	int i = 10;
//	float o = 45.5455145125412;

//printf("%-9.2sok\n", NULL);

	// printf("%0-8.5dok\n", 54);
//ft_printf("%ok", 54);


printf("%*.*d\n",10, 7,415);

	 ft_printf("%*.*d",10,7,415);



	//ft_printf("%%%%%*p\n",-40, &b);
	//printf("%%%5%%020%||%s||%c||%-5.9d||\n", "salut", 't', 2555);
	//ft_printf("%%%5%%020%||%s||%c||%-5.9d||", "salut", 't', 2555);
	//ft_printf("%.4s", NULL);

//	ft_printf("%%0*%d %*u %u%% %-5% %%%% %% %% %010%%X%*sfd%%%p %p",30,10, 30, 7845, 301,41, "une bonne truite qui mange du poulet en aperitif", "mdr", &b);

// 	printf("cspiudxX%10.*d%10c%*.xue gros%%%%%%%%%%%.*s%*.*u%.1x%.50x\n", 10, 30, 7845,c, -30, 41, 71, "ok c bon la", -4, -55, 6874, 87, 96);
//ft_printf("cspiudxX%*.*d%10c%*.xue gros%%%%%%%%%%%.*s%*.*u%.1x%.50x", 10, 30, 7845,c, -30, 41, 71, "ok c bon la", -4, -55, 6874, 87, 96);

//ft_printf("%.*s%*.*u",71, "ok c bon la", -4, -55, 6874);

//	ft_printf("%30.0s",   "cest bon");
}

