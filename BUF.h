/*
BUF.h - A rudimentary text editor.
Purpose: To write less.
Behaviour: The Editor is a single 1024 Buffer.
Author: Luis F. Silva
The buffer can be extended or I can use a list, but for now its what I need.
*/

#ifndef BUF_H
#define BUF_H

#define MAXBUFSIZE 1024

typedef struct {
        char* text;
        int   textsize;
        //int line; // there is just one.
        int col;
        char* cursor; 
}Buffer; 

#endif