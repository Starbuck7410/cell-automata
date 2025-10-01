#include "../headers/canvas.h"



int size_x_px(canvas_T * canvas){
    return canvas->size_x * canvas->scale;
}

int size_y_px(canvas_T * canvas){
    return canvas->size_y * canvas->scale;
}

int create_canvas(canvas_T * canvas) {
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
                                        10, 10, size_x_px(canvas), size_y_px(canvas) , 1,
                                        BlackPixel(canvas->display, canvas->screen),
                                        WhitePixel(canvas->display, canvas->screen));

    XStoreName(canvas->display, canvas->window, "Screen");
    XSelectInput(canvas->display, canvas->window, ExposureMask | KeyPressMask);
    XMapWindow(canvas->display, canvas->window);

    // Allocate memory for the image
    size_t bytes_per_pixel = 4;
    size_t image_size_bytes = size_x_px(canvas) * size_y_px(canvas) * bytes_per_pixel;

    canvas->image_data = malloc(image_size_bytes);
    if (!canvas->image_data) {
        fprintf(stderr, "Error: Failed to allocate memory\n");
        return -1;
    }

    // Create an XImage
    canvas->image = XCreateImage(canvas->display, DefaultVisual(canvas->display, canvas->screen),
                                 canvas->depth, ZPixmap, 0,
                                 canvas->image_data, size_x_px(canvas), size_y_px(canvas),
                                 32, 0);

    if (!canvas->image) {
        fprintf(stderr, "Error: Failed to create XImage\n");
        free(canvas->image_data);
        return -1;
    }
    return 0;
}


void update_canvas(canvas_T * canvas){
    XPutImage(canvas->display, canvas->window, 
            DefaultGC(canvas->display, canvas->screen), 
            canvas->image, 0, 0, 0, 0, 
            size_x_px(canvas), size_y_px(canvas));
}

void destroy_canvas(canvas_T * canvas){
    XDestroyImage(canvas->image); 
    XDestroyWindow(canvas->display, canvas->window);
    XCloseDisplay(canvas->display);
}

int get_event(canvas_T * canvas, long mask){
    return XCheckWindowEvent(canvas->display, canvas->window, mask, & canvas->event);
}