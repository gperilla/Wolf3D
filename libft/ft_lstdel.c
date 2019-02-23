/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 08:03:59 by gperilla          #+#    #+#             */
/*   Updated: 2017/11/13 10:37:14 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *tmp;

	tmp = *alst;
	if (del != NULL)
	{
		while (tmp)
		{
			(*del)(tmp->content, tmp->content_size);
			free(tmp);
			tmp = tmp->next;
		}
	}
	*alst = NULL;
	free(*alst);
}
