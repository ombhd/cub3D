/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 13:50:19 by obouykou          #+#    #+#             */
/*   Updated: 2020/10/17 18:56:56 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	hundle_error(int err)
{
	err ? ft_putstr_fd("Error => ", 1) : 0;
	if (err == NO_ARG)
	{
		ft_putstr_fd("[USAGE : ./cub3d \"map_file.cub\"]\n", 1);
		exit(NO_ARG);
	}
	else if (err == FILE_ERROR)
		ft_putstr_fd("File not found or Permission denied !\n", 1);
	else if (err == EXTENSION_ERROR)
		ft_putstr_fd("Argument File extention is not '.cub' !\n", 1);
	else if (err == MAP_ERROR)
		ft_putstr_fd("MAP File content error !\n", 1);
	else if (err == GNL_ERROR)
		ft_putstr_fd("Reading source files Error !\n", 1);
	else if (err == MAP_ELM_REP)
		ft_putstr_fd("MAP Element was repeated !\n", 1);
	else if (err == SAVING_BMP_ERROR)
		ft_putstr_fd("Could not save first frame !\n", 1);
	else if (err)
		ft_putstr_fd("Execution Error !\n", 1);
	else
		ft_putstr_fd("End Game !\n", 1);
	exit(err);
}

char	*free_cub_exit(t_cub *cub, int err)
{
	if (err == END_GAME || err == SAVING_BMP_ERROR)
		free(cub->img.ptr);
	free_str_table(cub->map.map, cub->map.form.x);
	free(cub->dirs.no);
	free(cub->dirs.so);
	free(cub->dirs.we);
	free(cub->sprite.path);
	free(cub->dirs.ea);
	free(cub->zbuff);
	hundle_error(err);
	return ((char *)0);
}
