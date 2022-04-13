#include "cubed.h"
#include <string.h>

bool	parse_input(char **argv, t_data *data)
{
	(void)argv;
	data->level.no_texture_path = strdup("assets/wood.png");
	if (data->level.no_texture_path == NULL)
		return (false);
	return (true);
}
