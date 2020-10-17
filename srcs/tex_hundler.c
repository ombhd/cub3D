/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_hundler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 10:56:43 by obouykou          #+#    #+#             */
/*   Updated: 2020/10/16 19:16:26 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	verif_ptrs(t_tex tex[], void *s_ptr, t_cub *cub)
{
	if (!tex[0].ptr || !tex[1].ptr || !tex[2].ptr ||
					!tex[3].ptr || !s_ptr)
		free_cub_exit(cub, GNL_ERROR);
}

void	tex_extractor(t_cub *cub)
{
	cub->tex[0].ptr = mlx_xpm_file_to_image(cub->mlx_ptr,
					cub->dirs.no, &cub->tex[0].w, &cub->tex[0].h);
	cub->tex[1].ptr = mlx_xpm_file_to_image(cub->mlx_ptr,
					cub->dirs.so, &cub->tex[1].w, &cub->tex[1].h);
	cub->tex[2].ptr = mlx_xpm_file_to_image(cub->mlx_ptr,
					cub->dirs.ea, &cub->tex[2].w, &cub->tex[2].h);
	cub->tex[3].ptr = mlx_xpm_file_to_image(cub->mlx_ptr,
					cub->dirs.we, &cub->tex[3].w, &cub->tex[3].h);
	cub->sprite.tex.ptr = mlx_xpm_file_to_image(cub->mlx_ptr,
					cub->sprite.path, &cub->sprite.tex.w, &cub->sprite.tex.h);
	verif_ptrs(cub->tex, cub->sprite.tex.ptr, cub);
	cub->img.buff = (int *)mlx_get_data_addr(cub->img.ptr,
						&cub->img.bpp, &cub->img.size_l, &cub->img.endian);
	cub->tex[0].data = (int *)mlx_get_data_addr(cub->tex[0].ptr,
						&cub->img.bpp, &cub->img.size_l, &cub->img.endian);
	cub->tex[1].data = (int *)mlx_get_data_addr(cub->tex[1].ptr,
						&cub->img.bpp, &cub->img.size_l, &cub->img.endian);
	cub->tex[2].data = (int *)mlx_get_data_addr(cub->tex[2].ptr,
						&cub->img.bpp, &cub->img.size_l, &cub->img.endian);
	cub->tex[3].data = (int *)mlx_get_data_addr(cub->tex[3].ptr,
						&cub->img.bpp, &cub->img.size_l, &cub->img.endian);
	cub->sprite.tex.data = (int *)mlx_get_data_addr(cub->sprite.tex.ptr,
						&cub->img.bpp, &cub->img.size_l, &cub->img.endian);
	verif_ptrs(cub->tex, (void *)cub->sprite.tex.data, cub);
}
