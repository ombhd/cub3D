/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 19:26:37 by obouykou          #+#    #+#             */
/*   Updated: 2020/10/17 19:07:26 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_saving(t_bmp *b, t_cub *cub)
{
	b->w = cub->rsl.x;
	b->h = cub->rsl.y;
	b->bitcount = 32;
	b->w_in_bytes = ((b->w * b->bitcount + 31) / 32) * 4;
	b->img_size = b->w_in_bytes * b->h;
	b->bi_size = 40;
	b->bfi_size = 54;
	b->file_size = 54 + b->img_size;
	b->bi_planes = 1;
	ft_memcpy(b->header, "BM", 2);
	ft_memcpy(b->header + 2, &b->file_size, 4);
	ft_memcpy(b->header + 10, &b->bfi_size, 4);
	ft_memcpy(b->header + 14, &b->bi_size, 4);
	ft_memcpy(b->header + 18, &b->w, 4);
	ft_memcpy(b->header + 22, &b->h, 4);
	ft_memcpy(b->header + 26, &b->bi_planes, 2);
	ft_memcpy(b->header + 28, &b->bitcount, 2);
	ft_memcpy(b->header + 34, &b->img_size, 4);
}

int		save_bmp(t_cub *cub, int *buff)
{
	int fd;
	int i;
	int j;
	int l;
	int m;

	if ((fd = open("./first_frame.bmp", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR)) == -1 ||
			!(buff = (int *)malloc(cub->rsl.x * cub->rsl.y * sizeof(int))))
		free_cub_exit(cub, SAVING_BMP_ERROR);
	init_saving(&cub->bmp, cub);
	i = cub->rsl.y;
	l = 0;
	while (--i >= 0 && (j = cub->rsl.x))
	{
		m = -1;
		while (--j >= 0)
			buff[l * cub->rsl.x + ++m] = cub->img.buff[i * cub->rsl.x + j];
		l++;
	}
	write(fd, cub->bmp.header, 54);
	write(fd, buff, cub->rsl.x * cub->rsl.y * sizeof(int));
	free(buff);
	ft_putstr_fd("\nFirst frame saved successfully !\n", 1);
	close(fd);
	return (1);
}
