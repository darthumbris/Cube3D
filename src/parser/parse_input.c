#include "cubed.h"
#include <string.h>

// Make sure after the player position is set that the map data
// is updated to a 0 (easier for raycaster)
bool	parse_input(char **argv, t_data *data)
{
	(void)argv;
	data->level.no_texture_path = strdup("assets/wood.png");
	if (data->level.no_texture_path == NULL)
		return (false);
	return (true);
}
