/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 07:34:07 by user              #+#    #+#             */
/*   Updated: 2020/03/13 11:56:05 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H


# define WIDTH		1900
# define HEIGHT		1200
# define RED 		0xFF0000
# define GREEN 		0xFF00
# define BLUE 		0x000066
# define IVKLEIN 	0x3a75c4
# define WHITE 		0xFFFFFF

#include <math.h>
#include <pthread.h>
#include "libft.h"
#include "mlx.h"

typedef	struct		s_color
{
	int			channel[4];
}					t_color;

typedef	struct		s_rtv1
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*pixels_arr;
	int		line_size;
	int		bits_per_pixel;
	int		endian;
}					t_rtv1;

void		ft_draw(t_rtv1 *rtv1);

void		ft_mlx_win_init(t_rtv1 *rtv1);

int			ft_close(void *param);

int			key_press(int key);
int			init_hook(t_rtv1 *rtv1);

#endif
