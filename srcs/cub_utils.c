/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 12:46:49 by obouykou          #+#    #+#             */
/*   Updated: 2020/10/16 17:10:50 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		get_next_line(int fd, char **line)
{
	static	char	*buff_s;
	char			*buff;
	int				b;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0 ||
		!line || !(*line = (char *)malloc(1 * sizeof(char))))
		return (-1);
	**line = '\0';
	b = 1;
	if (!(buff = (char*)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	while (b)
	{
		if (!buff_s && (b = read(fd, buff, BUFFER_SIZE)) == -1)
			return (-1);
		buff[b] = '\0';
		if (!buff_s && build_line(line, &buff, &(buff_s), 1))
			return (1);
		else if (buff_s && build_line(line, &buff, &(buff_s), 0))
			return (1);
	}
	(buff_s != NULL) ? free(buff_s) : 0;
	(buff != NULL) ? free(buff) : 0;
	return (0);
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*tmp;

	tmp = (unsigned char*)b;
	i = 0;
	while (i < len)
		tmp[i++] = (unsigned char)c;
	return (b);
}

int		is_set(char *target, char *set)
{
	int	i;
	int j;
	int	b;

	if (!target || !*target || !set)
		return (0);
	j = -1;
	while (target[++j])
	{
		b = 0;
		i = -1;
		while (set[++i])
			if (target[j] == set[i])
				b = 1;
		if (!b)
			return (0);
	}
	return (1);
}

int		tb_len(char **table)
{
	int len;

	len = 0;
	if (table)
		while (table[len])
			++len;
	return (len);
}

int		is_color(int color_code)
{
	return (color_code >= 0 && color_code <= 255);
}
