/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 02:56:54 by gperilla          #+#    #+#             */
/*   Updated: 2017/11/13 15:45:03 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *new;
	t_list *tmp;

	if (lst == NULL || f == NULL)
		return (NULL);
	tmp = (*f)(lst);
	new = tmp;
	while (lst->next)
	{
		lst = lst->next;
		if (!(new->next = f(lst)))
			return (NULL);
		new = new->next;
	}
	return (tmp);
}
