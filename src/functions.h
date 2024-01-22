#include <raylib.h>

char *path_to_file(char *name);
void draw_block(Texture *texture, int x, int y, int z, int *sides);
void update_camera(Camera *camera, float dt);
