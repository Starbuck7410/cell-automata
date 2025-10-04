#include "../headers/canvas.h"
#include "../headers/automata.h"
#include <stdio.h>
#define SIZE_X 64
#define SIZE_Y 64

int automata_life(automata_T * automata, int x, int y){
    if (y < 1) return 0;
    int idx = ((y - 1) * automata->size_x + x);
    return automata->cells[idx];
}

int automata_death(automata_T * automata, int x, int y){ 
    if (y < 1) return 1;
    int idx = ((y - 1) * automata->size_x + x);
    return !automata->cells[idx];
}

void draw_automata(canvas_T * canvas, automata_T * automata){
    for (int y = 0; y < canvas->size_y; y++) {
        for (int x = 0; x < canvas->size_x; x++) {
            int idx = y * automata->size_x + x;
            if(automata->cells[idx]){
                set_pixel(canvas, x, y, (pixel_T) { .red = 255, .green = 255, .blue = 255 });
            }else{
                set_pixel(canvas, x, y, (pixel_T) { .red = 0, .green = 0, .blue = 0 });
            }
        }
    }
}

int main(){
    canvas_T canvas = {
        .name = "Game of Life",
        .size_x = SIZE_X,
        .size_y = SIZE_Y,
        .scale = 12,
    };

    automata_T automata = {
        .size_x = SIZE_X,
        .size_y = SIZE_Y,
        .rule_death = &automata_death,
        .rule_life = &automata_life
    };



    if (create_canvas(&canvas)) return -1;
    if (create_automata(&automata)) return -1;

    fill_canvas(&canvas, (pixel_T) {.red = 0, .green = 0, .blue = 0, .alpha = 255});

    while(canvas.event.xkey.keycode != 24){ // q for quit
        draw_automata(&canvas, &automata);
        update_canvas(&canvas);
        while(!get_event(&canvas, KeyPressMask | ButtonPressMask | Button1MotionMask));

        if(canvas.event.type == ButtonPress || canvas.event.type == MotionNotify){
            int idx = (canvas.event.xbutton.y / canvas.scale) * automata.size_x + (canvas.event.xbutton.x / canvas.scale);
            automata.cells[idx] = !automata.cells[idx];
        }else{
            iterate_automata(&automata);
        }
        // printf("Location: %d, %d\n", canvas.event.xbutton.x, canvas.event.xbutton.y);
        // printf("Keycode: %d\n", canvas.event.xkey.keycode);
    }

    destroy_automata(&automata);
    destroy_canvas(&canvas);

}