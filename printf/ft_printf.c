/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   test.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: blorin <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/09 18:26:01 by blorin       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/16 14:39:14 by blorin      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int		is_pourcent(char *s)
{
	static int i = 0;
	int a;

	a = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '%')
		{
			if (s[i + 1] == '%')
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

void	write_between(char *str)
{
	static int i= 0;

		while (str[i] != '%' && str[i] != '\0')
		{
			write(1, &str[i], 1);
			i++;
		}
		if (str[i] == '%')
		{
			i++;
			while (str[i] != 'c' && str[i] != 's' && str[i] != 'p' && str[i] != 'd' &&
					str[i] != 'i' && str[i] != 'u' && str[i] != 'x' && str[i] != 'X' && str[i] != '%')
				i++;
			i++;
		}
}



void	write_end(char *str)
{
	int i;

	i = ft_strlen(str);
	while (str[i] != '%')
		i--;
	i++;
	while (str[i] != 'c' && str[i] != 's' && str[i] != 'p' && str[i] != 'd' &&
			str[i] != 'i' && str[i] != 'u' && str[i] != 'x' && str[i] != 'X' && str[i] != '%')
		i++;
	i++;
	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
	}
}

int		parse_str(char *str)
{
	static int par = 0;
	int tmp;

	tmp = 0;
	while (str[par] != '\0')
	{
		if (str[par] == '%')
		{
			tmp = par;
			par++;
			while  (str[par] != 'c' && str[par] != 's' && str[par] != 'p' && str[par] != 'd' &&
			str[par] != 'i' && str[par] != 'u' && str[par] != 'x' && str[par] != 'X' && str[par] != '%')
				par++;
			if (str[par] == '%')
				par++;
			return (tmp);
		}
		par++;
	}
	return (par);
}

int	use_argue(char *s, va_list argue)
{
	char c;
	int i = 0;
	int par;

	va_list_wrap copy;
	va_copy(copy.arg, argue);
	while (is_pourcent(s) > 0)
	{
		write_between(s);
		c = what_type(s);
		par = parse_str(s);
		if (c == 'c')
			convert_type_char(s, copy.arg, par);
		else if (c == 's')
			convert_type_string(s, copy.arg, par);
		else if (c == 'p')
			convert_type_adress(s, copy.arg, par);
		else if (c == 'd' || c == 'i')
			convert_type_int(s, copy.arg, par);
		else if (c == 'u')
			convert_type_unsigned(s, copy.arg, par);
		else if (c == 'x')
			convert_type_hexa(s, copy.arg, par);
		else if (c == 'X')
			convert_type_hexa_m(s, copy.arg, par);
		else if (c == '%')
			write(1, "%", 1);
	}
	write_end(s);
	return (1);
}

int ft_printf(char *s, ...)
{
	va_list argue;
	va_start(argue, s);
	use_argue(s, argue);
	
		return (1);
}



int main()
{
//	float o = 45.5455145125412;
	int i = 540;
//	p = unsigned long en hexadecimal
	char c = 'c';
//	printf("%.2f", 454, 745);
//	printf("lol");
	char k = 'k';
	 int b = i;
/*	printf("bonjour%010d%.3s%%%%%pMDRCBON%-15Xok%*usaluthfl%%fd%%%s %s %p\n", 20, "je mange", &b, 50, 15, 15, "une bonne truite qui mange du poulet en aperitif", "mdr", &b);

	ft_printf("bonjour%010d%.3s%%%%%pMDRCBON%-15Xok%*usaluthfl%%fd%%%s %s %p", 20, "je mange", &b, 50, 15, 15, "une bonne truite qui mange du poulet en aperitif", "mdr", &b);*/

	//printf("%0*dok\n",-40, i);
	/*printf("%d %*u %u%% %X%*sfd%%%p %p\n",10, 30, 7845, 301 ,41, 15, "une bonne truite qui mange du poulet en aperitif", "mdr", &b);
	ft_printf("%d %*u %u%% %X%*sfd%%%p %p",10, 30, 7845, 301 ,41, 15, "une bonne truite qui mange du poulet en aperitif", "mdr", &b);*/

 	printf("cspiudxX%*.*d%10c%*.xue gros%%%%%%%%%%%.*s%*.*u%.1x%.50x\n", 10, 30, 7845,c, -30, 41, 71, "ok c bon la", -4, -55, 6874, 87, 96);
ft_printf("cspiudxX%*.*d%10c%*.xue gros%%%%%%%%%%%.*s%*.*u%.1x%.50x", 10, 30, 7845,c, -30, 41, 71, "ok c bon la", -4, -55, 6874, 87, 96);

//ft_printf("%.*s%*.*u",71, "ok c bon la", -4, -55, 6874);



//	ft_printf("%30.0s",   "cest bon");
}
