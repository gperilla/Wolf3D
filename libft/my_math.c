/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <gperilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 05:44:40 by gperilla          #+#    #+#             */
/*   Updated: 2018/05/16 17:44:32 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_puiss(int x, int n)
{
	int ans;

	ans = 1;
	while (n--)
		ans *= x;
	return (ans);
}

int		ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int		ft_max(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

int		ft_abs(int x)
{
	if (x < 0)
		return (-x);
	return (x);
}
