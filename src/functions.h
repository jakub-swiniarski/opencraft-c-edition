#include <raylib.h>
#include "structs.h"

char *path_to_file(char *name);
void draw_block(Texture *tx, int x, int y, int z, int *sides);
void update_player(Player *p, float dt);
void begin_3d(Player *p);
