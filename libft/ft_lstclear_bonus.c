/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstclear.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: blorin <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/28 15:32:34 by blorin       #+#   ##    ##    #+#       */
/*   Updated: 2019/10/28 16:17:11 by blorin      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list *supr;

	supr = *lst;
	while (supr)
	{
		*lst = supr;
		del((*lst)->content);
		free(*lst);
		supr = supr->next;
	}
	*lst = NULL;
}
