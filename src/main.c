#include "../headers/canvas.h"


int main(){
    canvas_T canvas = {
        // properties
        .size_x = 256,
        .size_y = 256,
        .scale = 3,
    };

    if (create_canvas(&canvas, "Game of Life")) return -1;
    

    for (int y = 0; y < canvas.size_y; y++) {
        for (int x = 0; x < canvas.size_x; x++) {
            set_pixel(&canvas, x, y, 1, 20, 30);
        }
    }
    
    update_canvas(&canvas);
    while(!get_event(&canvas, KeyPressMask)){
        continue;
    }

    destroy_canvas(&canvas);

}