#ifndef MOUSE_H
#define MOUSE_H

// Variables ko extern bana diya
extern int mouse_x;
extern int mouse_y;

// Sirf functions ke naam
void mouse_wait(unsigned char type);
void mouse_write(unsigned char command);
unsigned char mouse_read();
void init_mouse();

#endif