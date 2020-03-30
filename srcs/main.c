/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 07:33:48 by user              #+#    #+#             */
/*   Updated: 2020/03/30 18:56:25 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// SDL_SetRenderDrawColor(rtv1->rend, 100, 100, i++,
// 									255); - это невероятно красиво)

#include "rtv1.h"
#include <stdio.h>
#include "SDL.h"

float	vec_len(t_vector a)
{
	return (sqrt(pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2)));
}

float	vec_dot(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vector	vec_add(t_vector v1, t_vector v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
	return (v1);
}

t_vector	vec_scale(t_vector v, float nb)
{
	v.x *= nb;
	v.y *= nb;
	v.z *= nb;
	return (v);
}

float	vec_magn(t_vector v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vector	vec_sub(t_vector a, t_vector b)
{
	b = vec_scale(b, -1);
	return (vec_add(a, b));
}

t_vector	vec_norm(t_vector v)
{
	return (vec_scale(v, 1.0 / vec_magn(v)));
}

// int		main(int ac, char **av)
// {
// 	t_rtv1	*rtv1;

// 	av = 0;
// 	ac = 2;
// 	if (!(rtv1 = (t_rtv1 *)malloc(sizeof(t_rtv1))))
// 		exit(0);
// 	if (ac == 2)
// 	{
// 		rtv1->mlx = mlx_init();
// 		ft_mlx_win_init(rtv1);
// 		init_hook(rtv1);
// 		draw(rtv1);
// 		draw_button(rtv1);
// 		mlx_loop(rtv1->mlx);
// 	}
// 	return (0);
// }

t_color	get_color(int x, int y)
{
	t_color	color;

	// x = 0;
	// y = 0;
	color.channel[0] = 0;
	color.channel[1] =
		(255 * y);
	color.channel[2] =
		(225 * x);
	color.channel[3] =
		(0);
	return (color);
}



int		ray_intersect(t_vector orig, t_vector dir, t_sphere sphere)
{
	t_vector vpc;
	t_vector point;
	t_vector d;
	float t; // множество точек на луче
	t_vector intersection;

	float tca;
	float d2;
	float t_max;
	// dir - точка на луче;
	// point - точка на луче
	point = vec_add(orig, vec_scale(dir, t));
	sphere.radius = vec_sub(point, sphere.center);
}

t_vector	cast_ray(t_vector orig, t_vector dir, t_sphere sphere)
{
	t_vector vector;

	vector.x = 0.4;
	vector.y = 0.4;
	vector.z = 0.3;
	if (!ray_intersect(orig, dir, sphere))
	{
		vector.x = 0.2;
		vector.y = 0.7;
		vector.z = 0.8;
		return (vector);
	}
	return (vector);
}

void		init_sdl(t_rtv1 *rtv1)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
		if ((rtv1->window = SDL_CreateWindow("RTv1", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN))) // SDL_WINDOW_FULLSCREEN
			if (!(rtv1->rend = SDL_CreateRenderer(rtv1->window, -1,
			SDL_RENDERER_ACCELERATED)))
				printf("no");
	SDL_SetRenderDrawBlendMode(rtv1->rend, SDL_BLENDMODE_BLEND);
}

int		main()
{
	t_rtv1 *rtv1;
	SDL_Event event;
	size_t j;
	size_t i;
	t_vector origin;
	t_sphere sphere;
	// t_color		color;
	// int	fov = M_PI/2;
	t_vector vector;
	t_vector dir;


	sphere.center.x = 500;
	sphere.center.y = 500;
	sphere.center.z = 160;
	sphere.radius = 100;
	float t;

	// origin - точка из которой смотрим
	origin.x = 0;
	origin.y = 0;
	origin.z = 0;
	t = 0;
	rtv1 = (t_rtv1 *)malloc(sizeof(t_rtv1));
	init_sdl(rtv1);
	j = 0;
	while (j < HEIGHT * 2)
	{
		i =  0;
		while (i < WIDTH * 2)
		{
			// dir - это луч из точки камеры в напраление к сфере
			dir.x = i;
			dir.y = j;
			dir.z = -1;
			vector = cast_ray(origin, dir, sphere);
			// printf("x = %f y = %f z = %f\n", vector.x, vector.y, vector.z);
			SDL_SetRenderDrawColor(rtv1->rend, 255 * (vector.y / ((float)HEIGHT * 2)), 255 * (vector.x / ((float)WIDTH * 2)), 255 * (vector.z / ((float)WIDTH * 2)),
									255);
			SDL_RenderDrawPoint(rtv1->rend, i, j);
			i++;
		}
		j++;
	}
	SDL_RenderPresent(rtv1->rend);
	while (1) 								//event on keyboard
		while (SDL_PollEvent(&event))
			if (event.type == SDL_QUIT ||
				(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
				exit(0);
	return (0);
}

