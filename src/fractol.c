/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 16:01:59 by oezzaou           #+#    #+#             */
/*   Updated: 2023/02/18 22:51:59 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"

int	main(int ac, char **av)
{
	t_var			var;
	t_img			img;
	t_complex_plan	p;
	t_julia			julia;
	
	mlx_create_window(&var);
	mlx_create_image(&var, &img, &julia, &p);
	if (!display_fractal(&img, ac, av))
		return (display_options(), EXIT_SUCCESS);
	mlx_key_hook(var.win, on_press_button, &img);
	mlx_mouse_hook(img.var->win, zoom, &img);
	mlx_hook(var.win, 17, 0, close_window, &img);
	mlx_loop(var.mlx);
	return (EXIT_SUCCESS);
}
