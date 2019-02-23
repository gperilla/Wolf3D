/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_through_portal.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <gperilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 19:30:39 by gperilla          #+#    #+#             */
/*   Updated: 2019/01/08 14:20:04 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	view_through_portal2(t_env *env, float *nbx, float *nby)
{
	if ((env->portal[env->cheatp].card == 0 && env->portal[(env->cheatp
		+ 1) % 2].card == 2)
			|| (env->portal[env->cheatp].card == 1 && env->portal[(env->cheatp
				+ 1) % 2].card == 3)
			|| (env->portal[env->cheatp].card == 2 && env->portal[(env->cheatp
				+ 1) % 2].card == 1)
			|| (env->portal[env->cheatp].card == 3 && env->portal[(env->cheatp
				+ 1) % 2].card == 0))
		one_quarter_turn_portals(env, env->cheatp, &(*nbx), &(*nby));
	else if ((env->portal[env->cheatp].card == 0 && env->portal[(env->cheatp
		+ 1) % 2].card == 3)
			|| (env->portal[env->cheatp].card == 1 && env->portal[(env->cheatp
				+ 1) % 2].card == 2)
			|| (env->portal[env->cheatp].card == 2 && env->portal[(env->cheatp
				+ 1) % 2].card == 0)
			|| (env->portal[env->cheatp].card == 3 && env->portal[(env->cheatp
				+ 1) % 2].card == 1))
		the_other_quarter_turn(env, env->cheatp, &(*nbx), &(*nby));
}

void	view_through_portal(t_env *env, int x, float *nbx, float *nby)
{
	calcul_portal_height(env, x, (*nbx), (*nby));
	apply_height_to_portal(env, env->cheatp);
	portal_coloring(env, x);
	if ((env->portal[env->cheatp].card % 2 == 0 && env->portal[env->cheatp].card
		== env->portal[(env->cheatp + 1) % 2].card - 1)
		|| (env->portal[env->cheatp].card % 2 == 1 &&
			env->portal[env->cheatp].card == env->portal[(env->cheatp + 1)
			% 2].card + 1))
		same_direction_portals(env, env->cheatp);
	else if (env->portal[env->cheatp].card == env->portal[(env->cheatp + 1)
	% 2].card)
		reverse_direction_portals(env, env->cheatp);
	else
		view_through_portal2(env, nbx, nby);
}
