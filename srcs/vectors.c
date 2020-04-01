/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 17:21:41 by user              #+#    #+#             */
/*   Updated: 2020/04/01 17:22:01 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

float	vec_len(t_vector a)
{
	return (sqrt(pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2)));
}

float	vec_dot(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vector	vec_add(t_vector a, t_vector b)
{
	a.x += b.x;
	a.y += b.y;
	a.z += b.z;
	return (a);
}

t_vector	vec_scale(t_vector a, float nb)
{
	a.x *= nb;
	a.y *= nb;
	a.z *= nb;
	return (a);
}

float	vec_magn(t_vector a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

t_vector	vec_sub(t_vector a, t_vector b)
{
	b = vec_scale(b, -1);
	return (vec_add(a, b));
}

t_vector	vec_norm(t_vector a)
{
	return (vec_scale(a, 1.0 / vec_magn(a)));
}
