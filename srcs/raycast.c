/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 11:38:22 by obouykou          #+#    #+#             */
/*   Updated: 2020/10/15 11:44:56 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ray_calcs(t_cub *cub, int x)
{
	cub->ctrl.cam.x = 2 * x / (double)cub->rsl.x - 1;
	cub->ctrl.ray.x = cub->ctrl.dir.x + cub->ctrl.plane.x * cub->ctrl.cam.x;
	cub->ctrl.ray.y = cub->ctrl.dir.y + cub->ctrl.plane.y * cub->ctrl.cam.x;
	cub->ctrl.map.x = (int)cub->ctrl.pos.x;
	cub->ctrl.map.y = (int)cub->ctrl.pos.y;
	cub->ctrl.delta_d.x = fabs(1 / cub->ctrl.ray.x);
	cub->ctrl.delta_d.y = fabs(1 / cub->ctrl.ray.y);
}

void	step_dir(t_cub *cub)
{
	if (cub->ctrl.ray.x < 0)
	{
		cub->ctrl.step.x = -1;
		cub->ctrl.side_dist.x = (cub->ctrl.pos.x - cub->ctrl.map.x) *
									cub->ctrl.delta_d.x;
	}
	else
	{
		cub->ctrl.step.x = 1;
		cub->ctrl.side_dist.x = (cub->ctrl.map.x + 1.0 - cub->ctrl.pos.x) *
									cub->ctrl.delta_d.x;
	}
	if (cub->ctrl.ray.y < 0)
	{
		cub->ctrl.step.y = -1;
		cub->ctrl.side_dist.y = (cub->ctrl.pos.y - cub->ctrl.map.y) *
									cub->ctrl.delta_d.y;
	}
	else
	{
		cub->ctrl.step.y = 1;
		cub->ctrl.side_dist.y = (cub->ctrl.map.y + 1.0 - cub->ctrl.pos.y) *
									cub->ctrl.delta_d.y;
	}
}

void	dda(t_cub *cub)
{
	char pos;

	while (cub->ctrl.hit == 0)
	{
		if (cub->ctrl.side_dist.x < cub->ctrl.side_dist.y)
		{
			cub->ctrl.side_dist.x += cub->ctrl.delta_d.x;
			cub->ctrl.map.x += cub->ctrl.step.x;
			cub->ctrl.side_dir = 0;
		}
		else
		{
			cub->ctrl.side_dist.y += cub->ctrl.delta_d.y;
			cub->ctrl.map.y += cub->ctrl.step.y;
			cub->ctrl.side_dir = 1;
		}
		pos = cub->map.map[cub->ctrl.map.x][cub->ctrl.map.y];
		if (pos != '0' && pos != '2')
			cub->ctrl.hit = 1;
	}
}
