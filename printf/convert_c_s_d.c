/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   convert_c_s_d.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: blorin <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/11 04:07:38 by blorin       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/16 14:46:35 by blorin      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

void	convert_type_char(char *s, va_list argue, int par)
{
	char z;
	int i;
	int k[2];
	int c;

	k[0] = 0;
	k[1] = 0;
	i = 1;
	while (s[par] != 'c')
	{
		if (s[par] == '*')
			k[0]++;
		par++;
	}
	if (k[0] > 0)
		k[0] = va_arg(argue, int);
	z = va_arg(argue, int);
	add_space_before(s, i, k);
	write(1, &z, 1);
	add_space_after(s, i, k);
}

int		write_p(int n)
{
	char *str;
	str = convert_p(n);
			ft_putstr(str);
	return (1);
}

char	convert_hexa(unsigned long i)
{
	char c;

	if (i == 10)
		c = 97;
	if (i == 11)
		c = 98;
	if (i == 12)
		c = 99;
	if (i == 13)
		c = 100;
	if (i == 14)
		c = 101;
	if (i == 15)
		c = 102;
	if (i == 16)
		c = 103;
	if (i < 10)
		c = i + 48;
	return (c);
}

int		hexa_len(unsigned long n)	
{
	int i;

	i = 1;
	while (n > 16)
	{	
		n = n / 16;
		i++;
	}
	return (i);
}
	

char	*ft_strrev(char *str)
{
	int i;
	char tmp;
	int a;
	int k;
	
	a = 0;
	i = 0;
	tmp = 0;
	while (str[i])
		i++;
	i--;
	k = i;
	while (a < i)
	{
		tmp = str[a];
		str[a] = str[i];
		str[i] = tmp;
		i--;
		a++;
	}
	return (str);

}

void	ft_free(char *str)
{
	if (str)
	{
		free(str);
		str = NULL;
	}
}

char	*add_0x(char *str)
{
	int i;
	char *new;
	int a;

	a = 0;
	i = 0;
	a = ft_strlen(str);
	if (!(new = malloc(sizeof(i + 3))))
		return (0);
	i = 0;
	new[i] = '0';
	i++;
	new[i] = 'x';
	i++;
	if (a < 9)
		new[i] = '1';
	a = 0;
	while (str[a])
	{
		new[i] = str[a];
		i++;
		a++;
	}
	new[i] = '\0';
	ft_free(str);
	return (new);
}

char	*convert_p(unsigned long n)
{
	unsigned long y;
	unsigned long tmp;
	char *str;
	int i;
	char c;
	
	tmp = 0;
	y = 0;
	y = n;
	i = hexa_len(y);
	if (!(str = malloc(sizeof(i + 1))))
		return (0);
	i = 0;
	while (y >= 16)
	{
		tmp = y % 16;
		c = convert_hexa(tmp);
		str[i] = c;
		i++;
		y = y / 16;
	}
	c = convert_hexa(y);
	str[i] = c;
	str[i+1] = '\0';
	str = ft_strrev(str);
	str = add_0x(str);
	return (str);
}



char	*convert_x(unsigned long n)
{
	unsigned long y;
	unsigned long tmp;
	char *str;
	int i;
	char c;
	
	tmp = 0;
	y = 0;
	y = n;
	i = hexa_len(y);
	if (!(str = malloc(sizeof(i + 1))))
		return (0);
	i = 0;
	while (y >= 16)
	{
		tmp = y % 16;
		c = convert_hexa(tmp);
		str[i] = c;
		i++;
		y = y / 16;
	}
	c = convert_hexa(y);
	str[i] = c;
	str[i+1] = '\0';
	str = ft_strrev(str);
	return (str);
}

char 	*ft_capitalize(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 97 && str[i] <= 122)
			str[i] = str[i] - 32;
		i++;
	}
	return (str);
}


void	convert_type_hexa_m(char *s, va_list argue, int par)
{
	unsigned long n;
	int i;
	int k[2];
	int c;

	c = 0;
	k[0] = 0;
	k[1] = 0;
	i = 0;
	if (is_precision(s, par) >= 0)
		k[1] = is_precision(s, par);
	while (s[par] != 'X')
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
	i = hexa_len(n);
	add_space_before(s, i, k);
	add_precision(i, k[1]);
	ft_putstr(ft_capitalize(convert_x(n)));
	add_space_after(s, i, k);

}

void	convert_type_hexa(char *s, va_list argue, int par)
{
	unsigned long n;
	int i;
	int k[2];
	int c;

	c = 0;
	k[0] = 0;
	k[1] = 0;
	i = 0;
	if (is_precision(s, par) >= 0)
		k[1] = is_precision(s, par);
	while (s[par] != 'x')
	{
		if (s[par] == '*' && s[par - 1] != '.')
			k[0]++;
		par++;
		if (s[par] == '*' && s[par - 1] == '.')
			c++;
	}
	par++;
	if (k[0] > 0)
		k[0] = va_arg(argue, int);
	if (c > 0)
		k[1] = va_arg(argue, int);
	n = va_arg(argue, int);
	i = hexa_len(n);
	add_space_before(s, i, k);
	add_precision(i, k[1]);
	ft_putstr(convert_x(n));
	add_space_after(s, i, k);
}

void	convert_type_adress(char *s, va_list argue, int par)
{
	unsigned long n;
	int i;
	int k[2];
	int c;

	c = 0;
	k[0] = 0;
	k[1] = 0;
	i = 0;
	if (is_precision(s, par) >= 0)
		k[1] = is_precision(s, par);
	while (s[par] != 'p')
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
	n = va_arg(argue, unsigned long);
	i = hexa_len(n) + 3;
	if (i > 13)
		i--;
	add_space_before(s, (int)i, k);
	add_precision(i, k[1]);
	ft_putstr(convert_p(n));
	add_space_after(s, i, k);
}

void	convert_type_string(char *s, va_list argue, int par)	
{
	char *str;
	int i;
	int k[2];
	int c;

	k[0] = 0;
	k[1] = 0;
	c = 0;
	i = 0;
	k[1] = is_precision(s, par);
	while (s[par] != 's')
	{
		if (s[par] == '*' && s[par - 1] != '.')
			k[0]++;
		par++;
		if (s[par] == '*' && s[par - 1] == '.')
			c++;
	}
	if (k[0] > 0)
		k[0] = va_arg(argue, int);
	if (c  > 0)
		k[1] = va_arg(argue, int);
	str = va_arg(argue, char*);
	i = ft_strlen(str);
	add_space_before(s, i, k);
	write_string(str, k[1]);
	add_space_after(s, i, k);
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
void	convert_type_unsigned(char *s, va_list argue, int par)
{
	int n;
	int i;
	int k[2];
	int c;

	c = 0;
	k[0] = 0;
	k[1] = 0;
	i = 0;
	if (is_precision(s, par) >= 0)
		k[1] = is_precision(s, par);
	while (s[par] != 'u')
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
	add_precision(i, k[1]);
	ft_putnbr_unsigned(n);
	add_space_after(s, i, k);
}

void	convert_type_int(char *s, va_list argue, int par)
{
	int n;
	int i;
	int k[2];
	int c;

	c = 0;
	k[0] = 0;
	k[1] = 0;
	i = 0;
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
	add_precision(i, k[1]);
	ft_putnbr((unsigned int)n);
	add_space_after(s, i, k);

}

void	add_precision(int len, int param)
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
int		is_valid_after(char *str, int i, int param)
{
	if (param < 0)
		return (0);
	while (str[i] != 'c' && str[i] != 's' && str[i] != 'p' && str[i] != 'd' && str[i] != 'i' &&
			str[i] != 'u' && str[i] != 'x' && str[i] != 'X')
	{
		if (str[i] == '-')
			return (0);
		i++;
	}
	return (1);
}

int		is_valid_before(char *str, int i, int param)
{
	if (param < 0)
		return (1);
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
	if (param[0] > 0)
	{
		zero = param[0] - len;
		while (zero > 0)
		{
			write(1, "0", 1);
			zero--;
		}
	}
	else
	{
		zero = ft_atoi(str, i);
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
	while (str[i] == ' ' || str[i] == '.' || str[i] == '-' || str[i] == '%')
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
	while (str[i] == ' ' || str[i] == '0' || str[i] == '-' || str[i] == '%')
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
	if (param[0] < 0)
		param[0] = param[0] * -1;
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

int		add_space_after(char *str, int len, int *param)
{
	static int i = 0;
	int a;

	while (str[i] != '%')
		i++;
	i++;
	while (str[i] != '\0' && str[i] != 'c' && str[i] != 's' && str[i] != 'p' && str[i] != 'd' &&
			str[i] != 'i' && str[i] != 'u' && str[i] != 'x' && str[i] != 'X')
		i++;
	while (str[i - 1] != '%')
		i--;
	if (is_valid_after(str, i, param[0]) > 0)
		return (1);
	if (is_space(str, i) > 0)
	{
	  write_space(str, len, param, i);
	  return (1);
	}
	return (0);
}




int		add_space_before(char *str, int len, int *param)
{
	static int i = 0;
	int a;
	
	while (str[i] != '%')
		i++;
	i++;
	while (str[i] != '\0' && str[i] != 'c' && str[i] != 's' && str[i] != 'p' && str[i] != 'd' &&
			str[i] != 'i' && str[i] != 'u' && str[i] != 'x' && str[i] != 'X')
		i++;
	while (str[i - 1] != '%')
		i--;
	if (is_valid_before(str, i, param[0]) > 0)
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

void	ft_putnbr_unsigned(unsigned int n)
{
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
