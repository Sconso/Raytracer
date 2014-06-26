/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivannere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 21:21:52 by ivannere          #+#    #+#             */
/*   Updated: 2014/06/26 01:47:24 by sconso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

int			the_parse(int fd, int obj_nb, int spot_nb, t_rt *e)
{
	int		i;
	char	*line;

	i = 0;
	while (i < obj_nb)
	{
		while ((line = get_next_line(fd)) && (line[0] == '/' || line[0] == 0))
			;
		line = delete_spaces(line, ' ');
		if (!verif_obj(line, e, fd, i))
			return (0);
		i++;
	}
	i = 0;
	while (i < spot_nb)
	{
		while ((line = get_next_line(fd)) && (line[0] == '/' || line[0] == 0))
			;
		line = delete_spaces(line, ' ');
		if (!verif_spot(line, e, fd, i))
			return (0);
		i++;
	}
	return (1);
}
