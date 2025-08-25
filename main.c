#include "so_long.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		error_exit("Usage: ./so_long map.ber");
	game.map.grid = read_map(argv[1]);
	if (!validate_map(&game.map))
		error_exit("Invalid map.");
	init_game(&game);
	render_map(&game);
	mlx_key_hook(game.win, handle_key, &game);
	mlx_hook(game.win, 17, 0, handle_exit, &game);
	mlx_loop(game.mlx);
	return (0);
}
