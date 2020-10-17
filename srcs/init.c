/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 11:50:03 by obouykou          #+#    #+#             */
/*   Updated: 2020/10/17 17:16:59 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_color(t_rgb *color)
{
	color->r = -1;
	color->g = -1;
	color->b = -1;
}

void	init_cub(t_cub *cub)
{
	cub->rsl.x = -1;
	cub->rsl.y = -1;
	cub->map.form.x = -1;
	cub->map.form.y = -1;
	cub->map.in_pos.y = -1;
	cub->map.tmp_map = NULL;
	cub->map.map = NULL;
	cub->dirs.no = NULL;
	cub->dirs.so = NULL;
	cub->dirs.we = NULL;
	cub->dirs.ea = NULL;
	cub->sprite.path = NULL;
	cub->zbuff = NULL;
	init_color(&cub->floor);
	init_color(&cub->ceil);
	cub->map.dir_count = 0;
	cub->sprite.count = 0;
}

void	init_player(t_cub *cub)
{
	cub->ctrl.pos.x = cub->map.in_pos.x + 0.5;
	cub->ctrl.pos.y = cub->map.in_pos.y + 0.5;
	if (cub->map.orient == 'N' || cub->map.orient == 'S')
	{
		cub->ctrl.dir.x = (cub->map.orient == 'N') ? -1 : 1;
		cub->ctrl.dir.y = 0;
		cub->ctrl.plane.x = 0;
		cub->ctrl.plane.y = (cub->map.orient == 'N') ? 0.66 : -0.66;
	}
	else if (cub->map.orient == 'E' || cub->map.orient == 'W')
	{
		cub->ctrl.dir.x = 0;
		cub->ctrl.dir.y = (cub->map.orient == 'W') ? -1 : 1;
		cub->ctrl.plane.x = (cub->map.orient == 'W') ? -0.66 : 0.66;
		cub->ctrl.plane.y = 0;
	}
}

void	init_map(t_cub *cub)
{
	init_player(cub);
	cub->ctrl.wall_d = 0.0;
	cub->ceil.a = (cub->ceil.r << 16) + (cub->ceil.g << 8) + cub->ceil.b;
	cub->floor.a = (cub->floor.r << 16) + (cub->floor.g << 8) + cub->floor.b;
	cub->sp.move = 0.04;
	cub->sp.root = 0.02;
	cub->key.u = 0;
	cub->key.d = 0;
	cub->key.l = 0;
	cub->key.r = 0;
	cub->key.rot_r = 0;
	cub->key.rot_l = 0;
	cub->key.exit = 0;
	cub->map.map[(int)cub->map.in_pos.x][(int)cub->map.in_pos.y] = '0';
	cub->zbuff = (double *)malloc(cub->rsl.x * sizeof(double));
}
