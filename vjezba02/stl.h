#ifndef stl_h
#define stl_h

#include <stdio.h>

typedef struct {
	float x, y, z;
} Point;

typedef struct {
	Point normal;
	Point vertex[3];
	unsigned short color;
}Triangle;

typedef struct {
	unsigned int triangleNum;
	Triangle* triangleArray;
}Object3D;


Object3D* read_bin_stl_file(char*);
void print_object(Object3D*);
void write_Object3D_to_bin_file(Object3D*, char*);
void write_Object3D_to_txt_file(Object3D*, char*);
void delete_Object3D(Object3D*);
void check_file(FILE*);

#endif 
