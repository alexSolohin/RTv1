/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 07:34:07 by user              #+#    #+#             */
/*   Updated: 2020/03/17 21:00:43 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

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

typedef struct s_viewport
{
	double	x;
	double	y;
	int		d;
}				t_viewport;


typedef	struct		s_color
{
	int			c;
	int			channel[4];
}					t_color;

typedef struct s_sphere
{
	t_vector	center;
	int			radius;
	t_color		color;
}				t_sphere;

typedef	struct		s_rtv1
{
	void	*mlx;
	void	*win;
	void	*img;
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

#endif
