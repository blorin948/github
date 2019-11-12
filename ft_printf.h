/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: blorin <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/09 23:47:40 by blorin       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/12 12:51:25 by blorin      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
#define FT_PRINTF_H
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
/*typedef struct a_list a_list;
struct	a_list
{
	char type;
	int param;
	char c;
	char *string;
	struct a_list	*next;
};*/

typedef struct va_list_wrap
{
	va_list arg;
}				va_list_wrap;
int		ft_atoi(char *str, int i);
int		add_space_before(char *str, int len, int *param);
void	write_zero(char *str, int len, int *param, int i);
int		is_zero(char *str, int i);
int		ft_intlen(int n);
int		is_string(char *str, int i);
int		is_precision(char *str, int i);
void	convert_type_int(char *s, va_list argue);
void	ft_putstr(char *str);
int		ft_strlen(char *str);
void	ft_putnbr(int n);
void	add_precision(char *str, int len, int param);
void	write_space(char *str, int len, int *param, int i);
int		count_precision(char *str, int len, int param, int i);
int		is_space(char *str, int i);
int		count_precision_string(char *str, int len, int param, int i);
void	ft_putchar(char c);
void	write_string(char *str, int len);
int		is_valid(char *str, int i);
int		use_argue(char *s, va_list argue);
int		is_pourcent(char *s);
void	convert_type_char(char *s, va_list argue);
void	convert_type_string(char *s, va_list argue);
char	what_type(char *str);
#endif
