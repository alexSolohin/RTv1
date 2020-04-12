/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 07:34:07 by user              #+#    #+#             */
/*   Updated: 2020/04/12 17:45:05 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H


# define ABS(a) (((a) < 0) ? -(a) : (a))
# define DIAM(d)	ABS(d) < 0.00001 ? 0 : (d)
# define VHEIGHT	1200
# define VWIDTH		1900
# define WIDTH		1900
# define HEIGHT		1200
# define RED 		0xFF0000
# define GREEN 		0xFF00
# define BLUE 		0x000066
# define IVKLEIN 	0x3a75c4
# define WHITE 		0xFFFFFF
# define B_H		200

#include <math.h>
#include <pthread.h>
#include "libft.h"
#include "mlx.h"
#include "SDL.h"






typedef struct	s_vector
{
	float		x;
	float		y;
	float		z;
}				t_vector;

typedef struct s_spvec
{
	t_vector	N;
	t_vector	point;
}				t_spvec;


typedef	struct		s_color
{
	int			c;
	int			channel[4];
}					t_color;

typedef struct s_light
{
	t_vector	position;
	float		intensity;
}				t_light;

typedef struct s_material
{
	t_vector	difuse_color;
}				t_material;

typedef struct s_sphere
{
	t_vector	center;
	float		radius;
	t_color		color;
	t_material	material;
}				t_sphere;

typedef	struct		s_rtv1
{
	void	*mlx;
	void	*win;
	void	*img;
	int		x;
	int		y;
	SDL_Window	*window;
	char	*pixels_arr;
	int		*pixels;
	int		line_size;
	int		bits_per_pixel;
	int		endian;
	SDL_Renderer	*rend;
}					t_rtv1;

void		ft_draw(t_rtv1 *rtv1);
void		draw(t_rtv1	*rtv1);
void		draw_button(t_rtv1 *rtv1);

void		ft_mlx_win_init(t_rtv1 *rtv1);

int			ft_close(void *param);

int			key_press(int key);
int			init_hook(t_rtv1 *rtv1);

void		put_pixel(t_rtv1 *rtv1, int x, int y, t_color color);
t_vector	cast_ray(t_vector orig, t_vector dir, t_sphere sphere, t_light light);

/*
**			<====================== start vectors.c ======================>
*/
float			vec_len(t_vector a);
float			vec_dot(t_vector a, t_vector b);
t_vector		vec_add(t_vector a, t_vector b);
t_vector		vec_scale(t_vector a, float nb);
float			vec_magn(t_vector a);
t_vector		vec_sub(t_vector a, t_vector b);
t_vector		vec_norm(t_vector a);
t_vector		vec_diff(t_vector a, float nb);
t_vector 		vec_normalize(t_vector a);
/*
**			<====================== end vectors.c ======================>
*/
#endif
