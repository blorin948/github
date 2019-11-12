/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   convert_c_s_d.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: blorin <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/11 04:07:38 by blorin       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/12 12:50:33 by blorin      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

void	convert_type_char(char *s, va_list argue)
{
	char c;

	c = va_arg(argue, int);
	write(1, &c, 1);
}

void	convert_type_string(char *s, va_list argue)	
{
	char *str;
	int i;
	static int par = 0;
	int k[2];
	int c;

	k[0] = 0;
	k[1] = 0;
	c = 0;
	i = 0;
	while (s[par] != '\0' && s[par] != 's')
		par++;
	while (s[par] != '%')
		par--;
	k[1] = is_precision(s, par);
	while (s[par] != 's')
	{
		if (s[par] == '*')
			k[0]++;
		par++;
		if (s[par] == '*' && k[0] > 0)
			c++;
	}
	if (k[0] > 0)
		k[0] = va_arg(argue, int);
	if (c  > 0)
		k[1] = va_arg(argue, int);
	str = va_arg(argue, char*);
	i = ft_strlen(str);
	add_space_before(s, i, k);
	//	add_space_after(s, i, k);
	write_string(str, k[1]);
	while (s[par - 1] != 's')
		par++;
}

int		is_precision(char *str, int i)
{
	int a;
	int k;
	int tmp;

	tmp = 0;
	k = 0;
	a = 0;
	while (str[i] != 'c' && str[i] != 's' && str[i] != 'p' && str[i] != 'd' && str[i] != 'i' &&
			str[i] != 'u' && str[i] != 'x' && str[i] != 'X')
	{
		if (str[i] == '.')
		{
			k++;
			tmp = i;
		}
		i++;
	}

	if (k > 0)
	{
		a = ft_atoi(str, tmp);
		return (a);
	}
	return (-1);
}


	

void	write_string(char *str, int len)
{
	int i;

	i = 0;
	if (len == -1)
		ft_putstr(str);
	else
	{
		while (str[i] != '\0' && i < len)
		{
			write(1, &str[i], 1);
			i++;
		}
	}
}

void	convert_type_int(char *s, va_list argue)
{
	int n;
	int i;
	static int par = 0;
	int k[2];
	int c;

	c = 0;
	k[0] = 0;
	k[1] = 0;
	i = 0;
	while(s[par] != '\0' && s[par] != '%')
		par++;
	if (is_precision(s, par) >= 0)
		k[1] = is_precision(s, par);
	while (s[par] != 'd' && s[par] != 'i')
	{
		if (s[par] == '*' && s[par - 1] != '.')
			k[0]++;
		par++;
		if (s[par] == '*' && s[par - 1] == '.')
			c++;
	}
	if (k[0] > 0)
		k[0] = va_arg(argue, int);
	if (c > 0)
		k[1] = va_arg(argue, int);
	n = va_arg(argue, int);
	i = ft_intlen(n);
	add_space_before(s, i, k);
	add_precision(s, i, k[1]);
	ft_putnbr(n);

}

void	add_precision(char *str, int len, int param)
{
	while (len < param)
	{
		write(1, "0", 1);
		len++;
	}
}

int		ft_intlen(int n)
{
	int len;

	len = 1;
	while (n >= 10)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	ft_putstr(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
	}
}

int		is_valid(char *str, int i)
{
	while (str[i] != 'c' && str[i] != 's' && str[i] != 'p' && str[i] != 'd' && str[i] != 'i' &&
			str[i] != 'u' && str[i] != 'x' && str[i] != 'X')
	{
		if (str[i] == '-')
			return (1);
		i++;
	}
	return (0);
}

int		is_zero(char *str, int i)
{
	int a;

	a = i;
	while (str[a] == '0' && str[i] != '\0' && str[i] != '.')
	{
		if (str[i] == 'c' || str[i] == 's' || str[i] == 'p' || str[i] == 'd' ||
				str[i] == 'i' || str[i] == 'u' || str[i] == 'x' || str[i] == 'X')
			return (1);
		i++;
	}
	return (0);
}

void	write_zero(char *str, int len, int *param, int i)
{
	int zero;

	zero = 0;
	if (param > 0)
	{
		zero = param[0] - len;
		while (zero > 0)
		{
			write(1, "0", 1);
			zero--;
		}
	}
	else
		zero = ft_atoi(str, i);
	{
		zero = zero - len;
		while (zero > 0)
		{
			write(1, "0", 1);
			zero--;
		}
	}
}

int		ft_atoi(char *str, int i)
{
	int n;

	n = 0;
	while (str[i] == ' ' || str[i] == '.')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + (str[i] - 48);
		i++;
	}
	return (n);
}

int		is_space(char *str, int i)
{
	int preci;

	preci = 0;
	while (str[i] == ' ' || str[i] == '0')
		i++;
	if ((str[i] == '*') || (str[i] >= '1' && str[i] <= '9'))
		return (1);
	while (str[i] != 'c' && str[i] != 's' && str[i] != 'p' && str[i] != 'd' &&
			str[i] != 'i' && str[i] != 'u' && str[i] != 'x' && str[i] != 'X')
	{
		if (str[i] == '.')
			preci++;
		i++;
	}
	return (0);
}


int		count_precision(char *str, int len, int param, int i)
{
	int preci;

	preci = 0;
	while (str[i] != 'c' && str[i] != 's' && str[i] != 'p' && str[i] != 'd' &&
			str[i] != 'i' && str[i] != 'u' && str[i] != 'x' && str[i] != 'X' &&
			str[i] != '.')
		i++;
	if (str[i] != '.')
		return (len);
	else if (param > 0)
	{
		if (param >= len)
			return (param);
		return (len);
	}
	preci = ft_atoi(str, i);
	if (preci < len)
		return (len);
	return (preci);
}

int		is_string(char *str, int i)
{
	while (str[i] != 'c' && str[i] != 's' && str[i] != 'p' && str[i] != 'd' &&
			str[i] != 'i' && str[i] != 'u' && str[i] != 'x' && str[i] != 'X')
		i++;
	if (str[i] == 's')
		return (1);
	return (0);
}


int		count_precision_string(char *str, int len, int param, int i)
{
	int preci;

	preci = 0;
	while (str[i] != 'c' && str[i] != 's' && str[i] != 'p' && str[i] != 'd' &&
			str[i] != 'i' && str[i] != 'u' && str[i] != 'x' && str[i] != 'X' &&
			str[i] != '.')
		i++;
	if (str[i] != '.')
		return (len);
	else if (param > 0)
	{
		if (param >= len)
			return (len);
		return (param);
	}
	preci = ft_atoi(str, i);
	if (preci < len)
		return (len);
	return (preci);
}

void	write_space(char *str, int len, int *param, int i)
{
	int preci;
	int space;

	space = 0;
	preci = 0;
	if (is_string(str, i) > 0)
		preci = count_precision_string(str, len, param[1], i);
	else
		preci  = count_precision(str, len, param[1], i);
	if (param[0] > 0)
	{
		space = param[0] - preci;
		while (space > 0)
		{
			write(1, " ", 1);
			space--;
		}
	}
	else
	{
		space = ft_atoi(str, i);
		space = space - preci;
		while (space > 0)
		{
			write(1, " ", 1);
			space--;
		}
	}
}


int		add_space_before(char *str, int len, int *param)
{
	static int i = 0;
	int a;

	while (str[i] != '\0' && str[i] != '%')
		i++;
	i++;
	if (is_valid(str, i) > 0)
		return (1);
	if (is_zero(str, i) > 0)
	{
		write_zero(str, len, param, i);
		return (1);
	}
	if (is_space(str, i) > 0)
	{
	  write_space(str, len, param, i);
	  return (1);
	}
	return (0);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int n)
{
	if (n > -2147483648)
	{
		if (n < 0)
		{
			ft_putchar('-');
			n = n * -1;
		}
		if (n >= 10)
		{
			ft_putnbr(n / 10);
			ft_putnbr(n % 10);
		}
		else
		{
			ft_putchar(n + '0');
		}
	}
	else if (n == -2147483648)
		write(1, "-2147483648", 11);
}
