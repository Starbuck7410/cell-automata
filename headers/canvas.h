#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct canvas_T {
    // properties
    const int size_x;
    const int size_y;
    const int scale;
    
    // data
    char * image_data;
    int depth;

    // X stuff
    XEvent event;
    XImage * image;
    Display * display;
    Window window;
    int screen;
} canvas_T;

int size_x_px(canvas_T *canvas);

int size_y_px(canvas_T *canvas);

int create_canvas(canvas_T *canvas);

void update_canvas(canvas_T *canvas);

void destroy_canvas(canvas_T *canvas);

int get_event(canvas_T *canvas, long mask);
