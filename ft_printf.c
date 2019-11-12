/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   test.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: blorin <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/09 18:26:01 by blorin       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/12 12:52:46 by blorin      ###    #+. /#+    ###.fr     */
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

int	use_argue(char *s, va_list argue)
{
	char c;
	int i = 0;

	va_list_wrap copy;
	va_copy(copy.arg, argue);
//	va_arg(copy.arg, char*);
	while (is_pourcent(s) > 0)
	{
		//check_space_before(s, *argue);
		c = what_type(s);
		if (c == 'c')
			convert_type_char(s, copy.arg);
		else if (c == 's')
			convert_type_string(s, copy.arg);
	//	else if (c == 'p')
	//		convert_type_adress(s, *argue);
		else if (c == 'd' || c == 'i')
			convert_type_int(s, copy.arg);
	/*	else if (c == 'u')
			convert_type_unsigned(s, *argue);
		else if (c == 'x')
			convert_type_hexa(s, *argue);
		else if (c == 'X')
			convert_type_hexa_m(s, *argue);
		else if (c == '%')
			convert_type_%(s, *argue);
		check_space_after(s, *argue);*/
		i++;
	}
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
//	int i = 4575;
//	p = unsigned long en hexadecimal
	char c = 'c';
//	printf("%.2f", 454, 745);
//	printf("lol");
	char k = 'k';
	//printf("%040d", "je mange");
	ft_printf("%00*.*d",40,30, 415);
	printf("\n");
	printf("%00*.*d\n",40,30, 415);

//	ft_printf("%30.0s",   "cest bon");
}

