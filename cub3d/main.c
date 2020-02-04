/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: blorin <blorin@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/03 01:41:56 by blorin       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/04 19:27:19 by blorin      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "cub3d.h"

int		ecran(t_storage *ptr)
{
	mlx_hook(ptr->win_ptr, 2, 0, key, ptr);
	mlx_hook(ptr->win_ptr, 3, 0, key_release, ptr);
	ray_cast(ptr);
	if (ptr->save > 0)
	{
		int i = 0;
		int j = 0;
		int color;
while (i < ptr->resoy)
	{
		j = 0;
		while (j < ptr->resox)
		{
			color = ptr->t_img.image[i * ptr->resox + j];
            printf("%d\n", color);
		//	write(fd, &color, 3);
		//	write(fd, &zero, pad);
			j++;
		}
       // printf("lol\n");
		i++;
	}
	//	printf("%d\n", ptr->t_img.image[i * ptr->resox + j]);
		//save_bmp_file(ptr);
		exit(0);
	}
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
	parsing(ptr->linecount, ptr);
	position(ptr);
	create_tab(ptr);
	if (check_tab(ptr) < 0)
		return (0);
	set_val(ptr);
	if (!(ptr->buffer = malloc(sizeof(double) * ptr->resox)))
		return (0);
	if (!(ptr->mlx_ptr = mlx_init()))
		return (0);
	open_win(ptr);
}

int		open_win(t_storage *ptr)
{
	load(ptr);
	if (ptr->error > 0)
		return (0);
	if (!(ptr->win_ptr = mlx_new_window(ptr->mlx_ptr,
	ptr->resox, ptr->resoy, "loool")))
		return (0);
	if (ptr->che.sky > 0)
	{
		if (skybox(ptr) != 1)
			return (0);
	}
}

int		main(int ac, char **av)
{
	t_storage	ptr;
	t_check		checkv;

	ptr = (t_storage){0};
	checkv = (t_check){0};
	ft_start(ac, av, &ptr, &checkv);
	ecran(&ptr);
}
