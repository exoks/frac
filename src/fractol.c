/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 16:01:59 by oezzaou           #+#    #+#             */
/*   Updated: 2023/02/19 22:57:00 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"

int	main(int ac, char **av)
{
	t_var			var;
	t_img			img;
	t_complex_plan	p;
	t_julia			julia;

	(void) ac;
	(void) av;
	mlx_create_window(&var);
	mlx_create_image(&var, &img, &julia, &p);
	int	i = -1;
	while (++i < 1200)
		mlx_pixel_put_in_img(&img, i, i, create_color(i));
	mlx_put_image_to_window(img.var->mlx, img.var->win, img.img, 0, 0);
	//if (!display_fractal(&img, ac, av))
	//	return (display_options(), EXIT_SUCCESS);
	events_handler(&img);
	mlx_loop(var.mlx);
	return (EXIT_SUCCESS);
}
