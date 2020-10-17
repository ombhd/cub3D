/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 21:14:49 by obouykou          #+#    #+#             */
/*   Updated: 2020/10/17 18:36:41 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

void	init_game(t_cub *cub)
{
	cub->mlx_ptr = mlx_init();
	if (!(cub->win_ptr = mlx_new_window(cub->mlx_ptr, cub->rsl.x,
		cub->rsl.y, "cub3D")))
		free_cub_exit(cub, EXEC_ERROR);
	cub->img.ptr = mlx_new_image(cub->mlx_ptr, cub->rsl.x, cub->rsl.y);
	tex_extractor(cub);
	mlx_hook(cub->win_ptr, 2, 1L << 0, key_pressed, cub);
	mlx_hook(cub->win_ptr, 3, 1L << 1, key_release, &(cub->key));
	mlx_hook(cub->win_ptr, 17, 1L << 5, close_window, cub);
	mlx_loop_hook(cub->mlx_ptr, calc_draw, cub);
	mlx_loop(cub->mlx_ptr);
}

int		main(int ac, char **av)
{
	t_cub cub;

	if (ac == 1)
		hundle_error(NO_ARG);
	cub.is_save = 0;
	if (ac == 3 && !strncmp(av[2], "--save", len_if(av[2], 0)))
		cub.is_save = 1;
	init_cub(&cub);
	check_map(av[1], &cub);
	init_map(&cub);
	init_game(&cub);
	return (0);
}
