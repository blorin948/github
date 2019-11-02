/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstadd_back.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: blorin <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/27 20:56:01 by blorin       #+#   ##    ##    #+#       */
/*   Updated: 2019/11/02 18:47:18 by blorin      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list *a;

	a = ft_lstlast(*alst);
	if (a)
	{
		a->next = new;
		new->next = NULL;
	}
	else
	{
		*alst = new;
		(*alst)->next = NULL;
	}
}
