/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 07:33:48 by user              #+#    #+#             */
/*   Updated: 2020/03/13 11:56:30 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>

int		main(int ac, char **av)
{
	t_rtv1	*rtv1;

	av = 0;
	ac = 2;
	if (!(rtv1 = (t_rtv1 *)malloc(sizeof(t_rtv1))))
		exit(0);
	if (ac == 2)
	{
		rtv1->mlx = mlx_init();
		ft_mlx_win_init(rtv1);
		init_hook(rtv1);
		ft_draw(rtv1);
		mlx_loop(rtv1->mlx);
	}
	return (0);
}
