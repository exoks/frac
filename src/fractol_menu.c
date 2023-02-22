/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_menu.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 16:54:27 by oezzaou           #+#    #+#             */
/*   Updated: 2023/02/22 01:54:16 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"

void	display_options(void)
{
	ft_printf("%60s\n", "<: FRACTALS :>");
	ft_printf("%53d\n", 0);
	ft_printf("%54.4d\n", 0);
	ft_printf("%55.6d\n", 0);
	ft_printf("%55.5d\n", 0);
	ft_printf("%46d%10.9d\n", 0, 0);
	ft_printf("%43.3d%17.16d\n", 0, 0);
	ft_printf("%62.20d%3.2d\n", 0, 0);
	ft_printf("%64.28d\n", 0);
	ft_printf("%66.31d\n", 0);
	ft_printf("%67.33d\n", 0);
	ft_printf("%66.32d\n", 0);
	ft_printf("%21d%6.5d%40.34d\n", 0, 0, 0);
//	ft_printf("%25d%6.5d%36.33d\n", 0, 0, 0);
//	ft_printf("%33d\n", 0);
}

void	display_usage_menu(t_img *img)
{
	char	*tmp;
	char	*iter;

	tmp = ft_itoa(img->nmax);
	iter = ft_strjoin(ITERATIONS, tmp);
	mlx_string_put(img->var->mlx, img->var->win, 10, 15, WHITE, USAGE);
	mlx_string_put(img->var->mlx, img->var->win, 20, 40, WHITE, U_ESC);
	mlx_string_put(img->var->mlx, img->var->win, 20, 60, WHITE, U_R);
	mlx_string_put(img->var->mlx, img->var->win, 20, 80, WHITE, U_ARROWS);
	mlx_string_put(img->var->mlx, img->var->win, 20, 100, WHITE, U_M_WHEEL);
	mlx_string_put(img->var->mlx, img->var->win, 10, 1170, WHITE, iter);
	free(tmp);
	free(iter);
}
