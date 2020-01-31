#include "cub3d.h"
#include "mlx/mlx.h"
#include "map.cub"

int main()
{
	int larg = 500;
	int haut = 500;
	int x;
	int y;

	x = 0;
	y = haut - (28 + ((haut - 28) / 2));
	//306
	worldmap[1][3];
	t_storage ptr;
	
ptr.mlx_ptr = mlx_init();
ptr.win_ptr = mlx_new_window(ptr.mlx_ptr, larg, haut, "cub3d");
//worldmap[3][8] - 3 1

		mlx_pixel_put(ptr.mlx_ptr, ptr.win_ptr, x, y, 255);
//(200 / -7) * -1 = 28
while (y < haut - ((haut - 28)/2))
{
	while (x < larg)
	{
		mlx_pixel_put(ptr.mlx_ptr, ptr.win_ptr, x, y, 255);
		x++;
	}
	x = 0;
	y++;
}
//haut = 1000;
while (y < haut)
{
	while(x < larg)
	{
		mlx_pixel_put(ptr.mlx_ptr, ptr.win_ptr, x, y, 16777215);
		x++;
	}
	x = 0;
	y++;
}
		mlx_pixel_put(ptr.mlx_ptr, ptr.win_ptr, x, y, 255);
mlx_loop(ptr.mlx_ptr);
}
