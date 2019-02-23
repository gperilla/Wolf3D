/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_through_portal3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <gperilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 13:53:21 by gperilla          #+#    #+#             */
/*   Updated: 2019/01/08 13:53:39 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	same_direction_portals(t_env *env, int p)
{
	env->map.x = env->portal[(p + 1) % 2].pos.x + ((env->portal[p].card < 2) *
	env->step.x);
	env->map.y = env->portal[(p + 1) % 2].pos.y + ((env->portal[p].card >= 2) *
	env->step.y);
}
