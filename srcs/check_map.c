/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 18:57:14 by obouykou          #+#    #+#             */
/*   Updated: 2020/10/15 11:56:58 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		check_extension(char *file_name, char *extension)
{
	int lf;
	int le;

	lf = len_if(file_name, 0);
	le = len_if(extension, 0);
	while (le--)
		if (file_name[--lf] != extension[le])
			return (0);
	return (1);
}

void	hundle_sp(char *line, t_cub *cub)
{
	char *tmp;

	tmp = ft_strtrim(line, " ");
	if (tmp && *tmp != '1')
	{
		free(line);
		free(tmp);
		free_cub_exit(cub, MAP_ERROR);
	}
	free(tmp);
}

int		analyse_line(int fd, char *line, t_cub *cub)
{
	if (*line == 'R')
		get_resolution(line, cub);
	else if (!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2) ||
			!ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2) ||
			!ft_strncmp(line, "S ", 2))
		get_verify_path(line, cub);
	else if (*line == 'F' || *line == 'C')
		get_verify_color(line, cub);
	else if (*line == '1' || *line == ' ')
	{
		hundle_sp(line, cub);
		get_verify_map(fd, line, &(cub->map), cub);
		return (1);
	}
	else if (!*line)
		return (0);
	else
	{
		free(line);
		free_cub_exit(cub, MAP_ERROR);
	}
	return (0);
}

void	verify_cub(t_cub *cub)
{
	int i;

	i = 1;
	if (cub->ceil.b == -1 || cub->floor.b == -1)
		i = 0;
	if (!cub->dirs.ea || !cub->dirs.we || !cub->dirs.no || !cub->dirs.so)
		i = 0;
	if (!cub->sprite.path || !cub->map.map || cub->rsl.x == -1 ||
		cub->rsl.y == -1)
		i = 0;
	if (i == 0)
		free_cub_exit(cub, MAP_ERROR);
}

void	check_map(char *map, t_cub *cub)
{
	int		r;
	int		fd;
	char	*line;

	if ((fd = open(map, O_RDONLY)) == -1)
		hundle_error(FILE_ERROR);
	if (check_extension(map, ".cub") == 0)
		hundle_error(EXTENSION_ERROR);
	r = 1;
	line = NULL;
	while (r > 0)
	{
		if ((r = get_next_line(fd, &line)) == -1 && !close(fd))
		{
			free(line);
			free_cub_exit(cub, GNL_ERROR);
		}
		if (analyse_line(fd, line, cub) == 1)
			break ;
		free(line);
	}
	verify_cub(cub);
	close(fd);
}
