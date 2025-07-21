/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: michoi <michoi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:50:02 by michoi            #+#    #+#             */
/*   Updated: 2025/07/21 13:59:26 by michoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	open_map_file(char *file)
{
	int	map_fd;

	map_fd = open(file, O_RDONLY);
	if (map_fd == -1)
	{
		ft_putendl_fd("Error", STDERR_FILENO);
		perror(file);
		return (-1);
	}
	return (map_fd);
}

int	check_args(int argc, char **argv)
{
	int	map_fd;

	if (argc <= 1)
	{
		print_error_messages("No map file provided");
		return (1);
	}
	if (argc > 2)
	{
		print_error_messages("Too many arguments. Put one file");
		return (1);
	}
	if (ft_strrncmp(argv[1], MAP_EXTENSION, ft_strlen(MAP_EXTENSION)))
	{
		print_error_messages("Invalid file extension. Use '*.cub' file");
		return (1);
	}
	map_fd = open_map_file(argv[1]);
	if (map_fd == -1)
		return (1);
	close(map_fd);
	return (0);
}

/**
 * Check if given argument is valid.
 * If the argument is valid, open the file and extract the data inside.
 * @param argc: number of arguments from the main function
 * @param argv: argument array from the main function
 * @param game: pointer to the game   struct
 */
int	parse_map(int argc, char **argv, t_game *game)
{
	int map_fd;
	
	if (check_args(argc, argv))
		return (1);
	map_fd = open_map_file(argv[1]);
	if (map_fd == -1)
		return (1);
	
	// extract data here //
	// while (get_next_line(map_fd))
	//  * {
	//  * 	if (empty line)
	//  * 	skip
	//  * type check
	//  * 
	//  * }
	close(map_fd);
	return (0);
}
