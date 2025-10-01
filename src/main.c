#include "../headers/canvas.h"
#include <string.h>

int main(){
    canvas_T canvas = {
        // properties
        .size_x = 256,
        .size_y = 256,
        .scale = 3,
    };

    if (create_canvas(&canvas)) return -1;

    memset(canvas.image_data, 0, size_x_px(&canvas) * size_y_px(&canvas) * 4);
	
    update_canvas(&canvas);
    while(!get_event(&canvas, KeyPressMask)){

    }

    destroy_canvas(&canvas);

}