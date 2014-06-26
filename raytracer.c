/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/25 02:32:45 by ael-kadh          #+#    #+#             */
/*   Updated: 2014/06/26 02:43:13 by sconso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include <stdlib.h>

static void		fill_color(int x, int y, t_rt *e, t_vect3 *tmp)
{
	int		color;
	int		r;

	color = (int)(ft_min(1.0, tmp->z) * 0xff) \
			+ ((int)(ft_min(1.0, tmp->y) * 0xff) << 8) \
			+ ((int)(ft_min(1.0, tmp->x) * 0xff) << 16);
	if (x < 0 || x >= LAR || y < 0 || y >= LAR)
		return ;
	r = (x * 4) + (y * e->sizeline);
	e->data[r] = (color & 0xFF);
	e->data[r + 1] = (color & 0xFF00) >> 8;
	e->data[r + 2] = (color & 0xFF0000) >> 16;
}

static void		ray_direction_init(int x, int y, t_rt *e)
{
	double		xx;
	double		yy;

	xx = (2 * ((x + 0.5) * e->invwidth) - 1) * e->angle * e->aspect_rat;
	yy = (1 - 2 * ((y + 0.5) * e->invheight)) * e->angle;
	e->raydir = ft_vect_init(xx, yy, -1.0);
	fn_normalize(e->raydir);
}

void			ft_render(t_rt *e)
{
	int			x;
	int			y;
	t_vect3		*tmp;

	e->invwidth = 1.0 / ((double)(LAR));
	e->invheight = 1.0 / ((double)(LON));
	e->aspect_rat = (double)(LAR) / ((double)(LON));
	e->angle = tan(M_PI * e->fov * 0.5 / ((double)(180)));
	y = 0;
	while (y < LON)
	{
		x = 0;
		while (x < LAR)
		{
			ray_direction_init(x, y, e);
			tmp = fn_trace(e->cam_ray, e->raydir, e, 0);
			fill_color(x, y, e, tmp);
			free(e->raydir);
			free(tmp);
			x++;
		}
		y++;
	}
}
