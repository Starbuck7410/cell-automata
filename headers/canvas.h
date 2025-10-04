#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BPP 4 // Bytes per pixel

typedef struct pixel_T { // BGRA
    char blue;
    char green;
    char red;
    char alpha;
} pixel_T;

typedef struct canvas_T {
    // properties
    const int size_x;
    const int size_y;
    const int scale;
    char * name;
    
    // data
    pixel_T * image_data;
    int depth;

    // X stuff
    XEvent event;
    XImage * image;
    Display * display;
    Window window;
    int screen;
} canvas_T;

int size_x_mpx(canvas_T *canvas);

int size_y_mpx(canvas_T *canvas);

int create_canvas(canvas_T *canvas);

void update_canvas(canvas_T *canvas);

void destroy_canvas(canvas_T *canvas);

int get_event(canvas_T *canvas, long mask);

void set_pixel(canvas_T *canvas, int x, int y, pixel_T pixel);
void fill_canvas(canvas_T * canvas, pixel_T pixel);
int get_last_keypress(canvas_T * canvas);
