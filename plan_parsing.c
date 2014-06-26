/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/16 19:23:22 by ael-kadh          #+#    #+#             */
/*   Updated: 2014/06/26 01:44:02 by sconso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include <stdlib.h>

static int		plan_parse3(int fd, t_sp **plan, int i)
{
	char	*line;

	while ((line = get_next_line(fd)) && (line[0] == '/' || !line[0]))
		;
	line = delete_spaces(line, ' ');
	if (!verif_real(line))
		return (0);
	plan[i]->reflection = ft_atoi_float(line);
	while ((line = get_next_line(fd)) && (line[0] == '/' || !line[0]))
		;
	line = delete_spaces(line, ' ');
	if (!verif_real(line))
		return (0);
	plan[i]->trans = ft_atoi_float(line);
	free(line);
	return (1);
}

static int		fn_parse_plan2(int fd, t_sp **plan, int i)
{
	char		*line;

	while ((line = get_next_line(fd)) && (line[0] == '/' || !line[0]))
		;
	if (!verif_vect(line))
		return (0);
	plan[i]->surface_c = ft_fill_vect(line, plan[i]->surface_c);
	while ((line = get_next_line(fd)) && (line[0] == '/' || !line[0]))
		;
	line = delete_spaces(line, ' ');
	if (!verif_vect(line))
		return (0);
	plan[i]->emission_c = ft_fill_vect(line, plan[i]->emission_c);
	free(line);
	if (!plan_parse3(fd, plan, i))
		return (0);
	return (1);
}

int				ft_parse_plan(int fd, char *line, t_sp **plan, int i)
{
	plan[i] = (t_sp*)malloc(sizeof(t_sp));
	while ((line = get_next_line(fd)) && (line[0] == '/' || !line[0]))
		;
	line = delete_spaces(line, ' ');
	if (!verif_vect(line))
		return (0);
	plan[i]->center = ft_fill_vect(line, plan[i]->center);
	while ((line = get_next_line(fd)) && (line[0] == '/' || !line[0]))
		;
	line = delete_spaces(line, ' ');
	if (!verif_vect(line))
		return (0);
	plan[i]->normal = ft_fill_vect(line, plan[i]->normal);
	free(line);
	if (!fn_parse_plan2(fd, plan, i))
		return (0);
	return (1);
}
