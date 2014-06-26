/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/07 21:35:46 by ael-kadh          #+#    #+#             */
/*   Updated: 2014/06/26 02:41:20 by sconso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LISTS_H
# define LISTS_H

# include <fcntl.h>
# include <mlx.h>

# define LAR 1080
# define LON 800
# define MAX_DEPTH 5

# define UP 65362
# define DOWN 65364
# define LEFT 65361
# define RIGHT 65363
# define OK 65293
# define EXIT 65307

# define BLUE 0x0000cc
# define GREEN 0x00cc00
# define BROWN 0xcc6600
# define GRAY 0x999999
# define FUSHIA 0xcc00cc
# define YELLOW 0xcccc00
# define CYAN 0xccffff
# define WHITE 0xffffff
# define RED 0xff0000

typedef struct			s_vect3
{
	double				x;
	double				y;
	double				z;
}						t_vect3;

typedef struct			s_sp
{
	t_vect3				*center;
	t_vect3				*normal;
	double				radius;
	double				radius_2;
	t_vect3				*surface_c;
	t_vect3				*emission_c;
	double				trans;
	double				reflection;
	char				axe;
}						t_sp;

typedef struct			s_rt
{
	void				*mlx;
	void				*win;
	void				*img;
	char				*data;
	int					bpp;
	int					sizeline;
	int					endian;
	double				invwidth;
	double				invheight;
	double				fov;
	double				aspect_rat;
	double				angle;
	t_vect3				*raydir;
	t_vect3				*cam_ray;
	char				**types;
	t_sp				**objects;
	t_sp				**spot;
}						t_rt;

typedef struct			s_vars
{
	double				tnear;
	double				t0;
	double				t1;
	double				bias;
	double				fresneleffect;
	double				facingratio;
	double				ior;
	double				k;
	double				cosi;
	double				eta;
	t_sp				*sphere;
	int					inside;
	int					depth;
	int					i;
	t_vect3				*tmp;
	t_vect3				*nhit;
	t_vect3				*phit;
	t_vect3				*surface;
	t_vect3				*refldir;
	t_vect3				*refrdir;
	t_vect3				*reflection;
	t_vect3				*refraction;
	t_vect3				*transmission;
	t_vect3				*lightdirection;
}						t_vars;

typedef struct			s_con_var
{
	double		a;
	double		b;
	double		c;
	double		ray;
	double		org;
	double		con;
	double		delta;
}						t_con_var;

#endif
