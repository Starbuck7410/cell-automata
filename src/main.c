#include "../headers/canvas.h"


int main(){
    canvas_T canvas = {
        // properties
        .size_x = 256,
        .size_y = 256,
        .scale = 3,
    };

    if (create_canvas(&canvas)) return -1;
    for(int i = 0; i < (size_x_px(&canvas) * size_y_px(&canvas) ); i++){
        canvas.image_data[i] = 0;
    }
	
    update_canvas(&canvas);
    while(!get_event(&canvas, KeyPressMask)){

    }

    destroy_canvas(&canvas);

}