#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include "stl.h"

//Object3D* read_txt_stl_file(Object3D, FILE*); dodatno, 7 redova opisuje 1 trokut, izbrojimo sve redove -1 i podjelimo s 7 da dobijemo broj trokuta 

Object3D* read_bin_stl_file(char* fileName)
{
	Object3D* obj = (Object3D*)malloc(sizeof(Object3D));
	if (!obj) return 0;
	FILE* filePtr = fopen(fileName, "rb");
	check_file(filePtr);

	fseek(filePtr, 80, SEEK_SET);

	fread(&obj->triangleNum, sizeof(int), 1, filePtr);

	obj->triangleArray = (Triangle*)malloc(sizeof(Triangle) * obj->triangleNum);
	if (!(obj->triangleArray)) return 0;

	for (int current = 0; current < obj->triangleNum; current++) {
		fread(obj->triangleArray + current, 50, 1, filePtr);
	}

	fclose(filePtr);
	return obj;
}

void write_Object3D_to_bin_file(Object3D* obj, char* fileName)
{
	FILE* filePtr = fopen(fileName, "wb");
	check_file(filePtr);
	char header[80] = { 0 };

	fwrite(header, 80, 1, filePtr);

	fwrite(&(obj->triangleNum), sizeof(int), 1, filePtr);

	for (int current = 0; current < obj->triangleNum; current++) {
		fwrite(&(obj->triangleArray[current]), 50, 1, filePtr);
	}

	fclose(filePtr);
}

void write_Object3D_to_txt_file(Object3D* obj, char* fileName)
{
	FILE* filePtr = fopen(fileName, "w");
	check_file(filePtr);

	fprintf(filePtr, "solid %s\n", fileName);

	for (int current = 0; current < obj->triangleNum; current++)
	{
		fprintf(filePtr, "facet normal %f %f %f\n", obj->triangleArray[current].normal.x, obj->triangleArray[current].normal.y, obj->triangleArray[current].normal.z);
		fprintf(filePtr, "    outer loop\n");
		fprintf(filePtr, "        vertex %f %f %f\n", obj->triangleArray[current].vertex[0].x, obj->triangleArray[current].vertex[0].y, obj->triangleArray[current].vertex[0].z);
		fprintf(filePtr, "        vertex %f %f %f\n", obj->triangleArray[current].vertex[1].x, obj->triangleArray[current].vertex[1].y, obj->triangleArray[current].vertex[1].z);
		fprintf(filePtr, "        vertex %f %f %f\n", obj->triangleArray[current].vertex[2].x, obj->triangleArray[current].vertex[2].y, obj->triangleArray[current].vertex[2].z);
		fprintf(filePtr, "    endloop\nendfacet\n");
	}

	fclose(filePtr);
}

void delete_Object3D(Object3D* obj)
{
	free(obj->triangleArray);
	free(obj);
}

void check_file(FILE* fptr)
{
	if (!fptr) {
		printf("Cannot open file. Make sure it is in same directory as project and check file name spelling!\n");
		exit(1);
	}
	else {
		printf("File opened!\n");
	}
}

void print_object(Object3D* obj) {

	for (int i = 0; i < obj->triangleNum; i++) {
		printf("normal[%d] %f %f %f\n", i, obj->triangleArray[i].normal.x, obj->triangleArray[i].normal.y, obj->triangleArray[i].normal.z);
		printf("	vertex[%d] %f %f %f\n", i, obj->triangleArray[i].vertex[0].x, obj->triangleArray[i].vertex[0].y, obj->triangleArray[i].vertex[0].z);
		printf("	vertex[%d] %f %f %f\n", i, obj->triangleArray[i].vertex[1].x, obj->triangleArray[i].vertex[1].y, obj->triangleArray[i].vertex[1].z);
		printf("	vertex[%d] %f %f %f\n\n", i, obj->triangleArray[i].vertex[2].x, obj->triangleArray[i].vertex[2].y, obj->triangleArray[i].vertex[2].z);
	}
}

