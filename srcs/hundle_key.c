/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hundle_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 11:15:42 by obouykou          #+#    #+#             */
/*   Updated: 2020/10/15 11:22:25 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	move_right_left(t_cub *cub, char d)
{
	if (d == 'r')
	{
		if (cub->map.map[(int)(cub->ctrl.pos.x + cub->ctrl.plane.x *
							cub->sp.move)][(int)cub->ctrl.pos.y] == '0')
			cub->ctrl.pos.x += cub->ctrl.plane.x * cub->sp.move;
		if (cub->map.map[(int)cub->ctrl.pos.x][(int)(cub->ctrl.pos.y +
								cub->ctrl.plane.y * cub->sp.move)] == '0')
			cub->ctrl.pos.y += cub->ctrl.plane.y * cub->sp.move;
	}
	else if (d == 'l')
	{
		if (cub->map.map[(int)(cub->ctrl.pos.x - cub->ctrl.plane.x *
							cub->sp.move)][(int)cub->ctrl.pos.y] == '0')
			cub->ctrl.pos.x -= cub->ctrl.plane.x * cub->sp.move;
		if (cub->map.map[(int)cub->ctrl.pos.x][(int)(cub->ctrl.pos.y -
								cub->ctrl.plane.y * cub->sp.move)] == '0')
			cub->ctrl.pos.y -= cub->ctrl.plane.y * cub->sp.move;
	}
}

void	forward_backward(t_cub *cub, char d)
{
	if (d == 'f')
	{
		if (cub->map.map[(int)(cub->ctrl.pos.x + cub->ctrl.dir.x *
							cub->sp.move)][(int)cub->ctrl.pos.y] == '0')
			cub->ctrl.pos.x += cub->ctrl.dir.x * cub->sp.move;
		if (cub->map.map[(int)cub->ctrl.pos.x][(int)(cub->ctrl.pos.y +
								cub->ctrl.dir.y * cub->sp.move)] == '0')
			cub->ctrl.pos.y += cub->ctrl.dir.y * cub->sp.move;
	}
	else if (d == 'b')
	{
		if (cub->map.map[(int)(cub->ctrl.pos.x - cub->ctrl.dir.x *
							cub->sp.move)][(int)cub->ctrl.pos.y] == '0')
			cub->ctrl.pos.x -= cub->ctrl.dir.x * cub->sp.move;
		if (cub->map.map[(int)cub->ctrl.pos.x][(int)(cub->ctrl.pos.y -
								cub->ctrl.dir.y * cub->sp.move)] == '0')
			cub->ctrl.pos.y -= cub->ctrl.dir.y * cub->sp.move;
	}
}

void	rotate_right_left(t_cub *cub, char d)
{
	if (d == 'r')
	{
		cub->ctrl.old_dir.x = cub->ctrl.dir.x;
		cub->ctrl.dir.x = cub->ctrl.dir.x * cos(-cub->sp.root) -
									cub->ctrl.dir.y * sin(-cub->sp.root);
		cub->ctrl.dir.y = cub->ctrl.old_dir.x * sin(-cub->sp.root) +
									cub->ctrl.dir.y * cos(-cub->sp.root);
		cub->ctrl.old_plane.x = cub->ctrl.plane.x;
		cub->ctrl.plane.x = cub->ctrl.plane.x * cos(-cub->sp.root) -
									cub->ctrl.plane.y * sin(-cub->sp.root);
		cub->ctrl.plane.y = cub->ctrl.old_plane.x * sin(-cub->sp.root) +
									cub->ctrl.plane.y * cos(-cub->sp.root);
		return ;
	}
	cub->ctrl.old_dir.x = cub->ctrl.dir.x;
	cub->ctrl.dir.x = cub->ctrl.dir.x * cos(cub->sp.root) -
					cub->ctrl.dir.y * sin(cub->sp.root);
	cub->ctrl.dir.y = cub->ctrl.old_dir.x * sin(cub->sp.root) +
					cub->ctrl.dir.y * cos(cub->sp.root);
	cub->ctrl.old_plane.x = cub->ctrl.plane.x;
	cub->ctrl.plane.x = cub->ctrl.plane.x * cos(cub->sp.root) -
						cub->ctrl.plane.y * sin(cub->sp.root);
	cub->ctrl.plane.y = cub->ctrl.old_plane.x * sin(cub->sp.root) +
						cub->ctrl.plane.y * cos(cub->sp.root);
}

int		hundle_key(t_cub *cub)
{
	if (cub->key.u == 1)
		forward_backward(cub, 'f');
	if (cub->key.d == 1)
		forward_backward(cub, 'b');
	if (cub->key.rot_r == 1)
		rotate_right_left(cub, 'r');
	if (cub->key.rot_l == 1)
		rotate_right_left(cub, 'l');
	if (cub->key.r == 1)
		move_right_left(cub, 'r');
	if (cub->key.l == 1)
		move_right_left(cub, 'l');
	return (0);
}
