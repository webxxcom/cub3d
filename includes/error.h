/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: webxxcom <webxxcom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 14:47:00 by phutran           #+#    #+#             */
/*   Updated: 2026/02/07 18:05:03 by webxxcom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <string.h>
# include <errno.h>

// File access
# define ERROR_OPEN_FILE_FAILED			"Failed to open file"
# define ERROR_READ_FILE_FAILED			"Failed to read file"

// File
# define ERROR_NO_FILE					"Failed to load map: No such file or directory"
# define ERROR_EMPTY_FILE				"Failed to load map: Empty file"
# define ERROR_INVALID_FILE				"Failed to load map: Invalid file"
# define ERROR_FILE_EXTENSION			"Failed to load map: Missing file extension .cub"
# define ERROR_MISSING_TEXTURE			"Failed to load map: Missing texture/s"
# define ERROR_INVALID_IDENTIFIER		"Failed to load map: Invalid specifier"
# define ERROR_TEXTURE_PATH				"Failed to load map: Invalid texture path"

// Memory allocation
# define ERROR_PARSE_MAP_FAILED			"Failed to parse map"
# define ERROR_COPY_MAP_FAILED			"Failed to validate path"
# define ERROR_MALLOC_FAILED			"Oops, malloc failed"

// MLX
# define ERROR_MLX_INIT					"mlx_init: Failed to initialize MinilibX"
# define ERROR_MLX_WIN					"mlx_new_window: Failed to create window"
# define ERROR_MLX_IMAGE				"mlx_xpm_file_to_image: Failed to load image"

// Elements
# define ERROR_PLAYER_NOT_FOUND			"Invalid map: Player not found"
# define ERROR_MULTIPLE_PLAYERS_FOUND	"Invalid map: Multiple players found"
# define ERROR_WALL						"Invalid map: Incomplete wall"
# define ERROR_LIGHT_PARSING			"Misconfiguration for light color"
# define ERROR_UNKNOWN_ELEMENT_FOUND	"Invalid map: Unknown element"
# define ERROR_UNKNOW_CONFIGURATION		"Unknown configuration occured in map file"
# define ERROR_UKNOWN_DECOR_TYPE        "Unknown decor type found"
# define ERROR_TOO_FEW_CONFIGURATIONS	"There were more or less configurations than needed (3 is needed)"
# define ERROR_DECOR_DIR                "Incorrect decoration direction"
# define ERROR_NEG_POS                  "The position is negative"
# define ERROR_FEW_ATTRIBUTES_DOOR      "Not enough attributes for decoration door"
# define ERROR_FEW_ATTRIBUTES_WALL      "Not enough attributes for decoration wall"
# define ERROR_FEW_ATTRIBUTES_SPRITE    "Not enough attributes for decoration sprite"
#endif