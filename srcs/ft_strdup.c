/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 20:29:43 by obouykou          #+#    #+#             */
/*   Updated: 2020/02/03 12:45:41 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*ft_strdup(const char *src)
{
	int		l;
	int		i;
	char	*dup;

	if (!src)
		return (NULL);
	l = 0;
	i = 0;
	while (src[l])
		l++;
	dup = (char*)malloc(l + 1);
	if (!dup)
		return (NULL);
	while (i < l)
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
