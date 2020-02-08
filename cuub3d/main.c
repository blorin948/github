/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: blorin <blorin@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/03 01:41:56 by blorin       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/08 19:59:51 by blorin      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"

int		mouse(int button,int x,int y,void *ptr)
{
	//if (button == 1)
	
	printf("x = %d  = %d\n", x, y);
	return (1);
}

int		ecran(t_storage *ptr)
{
	mlx_hook(ptr->win_ptr, 2, 0, key, ptr);
	mlx_hook(ptr->win_ptr, 3, 0, key_release, ptr);
		//mlx_mouse_hook (ptr->win_ptr, mouse, ptr);
	ray_cast(ptr);
	mlx_loop_hook(ptr->mlx_ptr, move_side, ptr);
	mlx_loop(ptr->mlx_ptr);
	return (1);
}

int		ft_start(int ac, char **av, t_storage *ptr, t_check *checkv)
{
	if (check_argue(ptr, ac, av) != 1)
		return (0);
	gnl(av[1], ptr, checkv);
	if (ptr->error > 0)
		return (0);
	if ((checkv->ea != 1 || checkv->no != 1 || checkv->we != 1 || checkv->so
	!= 1 || checkv->f != 1 || (checkv->c != 1 && ptr->che.sky != 1) || checkv->f
	!= 1 || checkv->sprite != 1 || checkv->r != 1))
		return (error(ptr, "parametres"));
	parsing(ptr);
	position(ptr);
	create_tab(ptr);
	if (check_tab(ptr) < 0)
		return (0);
	set_val(ptr);
	if (ptr->checkdoor > 0 && checkv->p < 1)
		error(ptr, "door");
	open_win(ptr);
	return (1);
}

int		open_win(t_storage *ptr)
{
	if (!(ptr->buffer = malloc(sizeof(double) * ptr->resox)))
		return (0);
	if (!(ptr->mlx_ptr = mlx_init()))
		return (0);
	load(ptr);
	if (ptr->error > 0)
		return (0);
	if (!(ptr->win_ptr = mlx_new_window(ptr->mlx_ptr,
	ptr->resox, ptr->resoy, "cub3d")))
		return (0);
	if (ptr->che.sky > 0)
	{
		if (skybox(ptr) != 1)
			return (0);
	}
	return (1);
}

int		main(int ac, char **av)
{
	t_storage	ptr;
	t_check		checkv;

	ptr = (t_storage){0};
	checkv = (t_check){0};
	ft_start(ac, av, &ptr, &checkv);
	if (ptr.error > 0)
		return (0);
	ecran(&ptr);
}
