/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phutran <phutran@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 14:47:00 by phutran           #+#    #+#             */
/*   Updated: 2025/09/25 15:35:37 by phutran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <string.h>
# include <errno.h>

// File access
# define ERROR_OPEN_FILE_FAILED "Failed to open file"
# define ERROR_READ_FILE_FAILED "Failed to read file"

// File
# define ERROR_NO_FILE "Failed to load map: No such file or directory"
# define ERROR_EMPTY_FILE "Failed to load map: Empty file"
# define ERROR_INVALID_FILE	"Failed to load map: Invalid file"
# define ERROR_FILE_EXTENSION "Failed to load map: Missing file extension .ber"

// Memory allocation
# define ERROR_PARSE_MAP_FAILED "Failed to parse map"
# define ERROR_COPY_MAP_FAILED "Failed to validate path"

// MLX
# define ERROR_MLX_INIT "mlx_init: Failed to initialize MinilibX"
# define ERROR_MLX_WIN "mlx_new_window: Failed to create window"
# define ERROR_MLX_IMAGE "mlx_xpm_file_to_image: Failed to load image"

// Elements
# define ERROR_UNKNOWN_ELEMENT_FOUND "Invalid map: Unknown element"
# define ERROR_PLAYER_NOT_FOUND "Invalid map: Player not found"
# define ERROR_MULTIPLE_PLAYERS_FOUND "Invalid map: Multiple players found"
# define ERROR_WALL "Invalid map: Incomplete wall"

#endif