#include "../headers/canvas.h"

// I gotta set my terminology right: Each pixel is composed of scale^2 minipixels
// Index is the linear index for an xy coordinate pair of pixels

// Size x minipixels
int size_x_mpx(canvas_T * canvas){
    return canvas->size_x * canvas->scale;
}

// Same for y
int size_y_mpx(canvas_T * canvas){
    return canvas->size_y * canvas->scale;
}

int create_canvas(canvas_T * canvas, char * name) {
    // Connect to the X server
    canvas->display = XOpenDisplay(NULL);
    
    if (!canvas->display) {
        fprintf(stderr, "Error: Cannot open X display\n");
        return -1;
    }
    canvas->screen = DefaultScreen(canvas->display);
    
    // Get screen depth (bits per pixel)
    canvas->depth = DefaultDepth(canvas->display, canvas->screen);
    // printf("Screen Depth: %d bits per pixel\n", canvas->depth);
    
    // Ensure we are working with 32-bit color (ARGB)
    if (canvas->depth != 24 && canvas->depth != 32) {
        fprintf(stderr, "Unsupported depth: %d\n", canvas->depth);
        return -1;
    }
    
    
    // Create a window
    canvas->window = XCreateSimpleWindow(canvas->display, RootWindow(canvas->display, canvas->screen),
    10, 10, size_x_mpx(canvas), size_y_mpx(canvas) , 1,
    BlackPixel(canvas->display, canvas->screen),
    WhitePixel(canvas->display, canvas->screen));
    
    XStoreName(canvas->display, canvas->window, name);
    XSelectInput(canvas->display, canvas->window, ExposureMask | KeyPressMask);
    XMapWindow(canvas->display, canvas->window);
    XFlush(canvas->display);

    // Allocate memory for the image
    size_t image_size_bytes = size_x_mpx(canvas) * size_y_mpx(canvas) * BPP;

    canvas->image_data = malloc(image_size_bytes);
    
    // init the buffer
    for(int i = 0; i < size_x_mpx(canvas) * size_y_mpx(canvas); i++){
        canvas->image_data[i] = (pixel_T) {0, 0, 0, 255}; 
    }

    if (!canvas->image_data) {
        fprintf(stderr, "Error: Failed to allocate memory\n");
        return -1;
    }

    // Create an XImage
    canvas->image = XCreateImage(canvas->display, DefaultVisual(canvas->display, canvas->screen),
                                 canvas->depth, ZPixmap, 0,
                                 (char *) canvas->image_data, size_x_mpx(canvas), size_y_mpx(canvas),
                                 32, 0);


    if (!canvas->image) {
        fprintf(stderr, "Error: Failed to create XImage\n");
        free(canvas->image_data);
        return -1;
    }

    // Setup the window

    XPutImage(canvas->display, canvas->window, 
            DefaultGC(canvas->display, canvas->screen), 
            canvas->image, 0, 0, 0, 0, 
            size_x_mpx(canvas), size_y_mpx(canvas));


    return 0;
}


void update_canvas(canvas_T * canvas){
    XFlush(canvas->display);
    XPutImage(canvas->display, canvas->window, 
            DefaultGC(canvas->display, canvas->screen), 
            canvas->image, 0, 0, 0, 0, 
            size_x_mpx(canvas), size_y_mpx(canvas));
}

void destroy_canvas(canvas_T * canvas){
    XDestroyImage(canvas->image); 
    XDestroyWindow(canvas->display, canvas->window);
    XCloseDisplay(canvas->display);
}

int get_event(canvas_T * canvas, long mask){
    return XCheckWindowEvent(canvas->display, canvas->window, mask, & canvas->event);
}

int xy_to_index(canvas_T * canvas, int x, int y){
    return canvas->scale * (y * size_x_mpx(canvas) + x);
}


void set_pixel(canvas_T * canvas, int x, int y, pixel_T pixel){
    int start_index = xy_to_index(canvas, x, y);
    for(int j = 0; j < canvas->scale; j++){
        for(int i = 0; i < canvas->scale; i++){
            int index = (start_index + i + j * size_x_mpx(canvas));
            canvas->image_data[index] = pixel;
        }
    }
}