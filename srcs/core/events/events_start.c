/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 18:13:06 by moabid            #+#    #+#             */
/*   Updated: 2022/11/06 18:13:09 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		key_hold(int key, struct s_cub3d *env)
{
	if (key == KEY_UP)
		env->move_flag |= 1;
	else if (key == KEY_DOWN)
		env->move_flag |= 2;
	else if (key == ROTATE_LEFT)
		env->move_flag |= 4;
	else if (key == ROTATE_RIGHT)
		env->move_flag |= 8;
	else if (key == KEY_LEFT)
		env->move_flag |= 16;
	else if (key == KEY_RIGHT)
		env->move_flag |= 32;
	else if (key == KEY_EXIT)
		ft_exit(env);
	return (SUCCESS);
}


int		key_release(int key, struct s_cub3d *env)
{
	if (key == KEY_UP)
		env->move_flag &= (~(1 << 0));
	else if (key == KEY_DOWN)
		env->move_flag &= (~(1 << 1));
	else if (key == ROTATE_LEFT)
		env->move_flag &= (~(1 << 2));
	else if (key == ROTATE_RIGHT)
		env->move_flag &= (~(1 << 3));
	else if (key == KEY_LEFT)
		env->move_flag &= (~(1 << 4));
	else if (key == KEY_RIGHT)
		env->move_flag &= (~(1 << 5));
	return (SUCCESS);
}

int		frames_run(struct s_cub3d *env)
{
	ft_free_img(env, env->img);
	if ((env->img = ft_new_image(env, env->width, env->height)) == NULL)
	{
		env->error = IMG_ERROR;
		ft_error(env->error, env);
		return (IMG_ERROR);
	}
	movements_create(env);
	frames_display(env, 0);
	mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->img->img_ptr, 0,
		0);
	return (SUCCESS);
}

bool		cub3d_run(struct s_cub3d env)
{
	while (env.width % 4)
		env.width++;
    if (!(env.win_ptr = mlx_new_window(env.mlx_ptr, 1, 1, "Cub3D")))
        return (false);
	else
	{
		if (!(env.win_ptr = mlx_new_window(env.mlx_ptr, env.width, \
		env.height, "Cub3D")))
			return (false);
	}
	mlx_hook(env.win_ptr, 17, STRUCTURENOTIFYMASK, ft_exit, &env);
	mlx_hook(env.win_ptr, KEYPRESS, KEYPRESSMASK, key_hold, &env);
	mlx_hook(env.win_ptr, KEYRELEASE, KEYRELEASEMASK, key_release, &env);
	mlx_loop_hook(env.mlx_ptr, frames_run, &env);
	mlx_loop(env.mlx_ptr);
	return (true);
}
