#include <stdio.h>
#include <stdlib.h>

#include "stl.h"

int main()
{
	Object3D *object = read_bin_stl_file("primjerbin.stl");

	/*print_object(object);*/
	
	write_Object3D_to_bin_file(object, "binExample.stl");

	write_Object3D_to_txt_file(object, "textExample.stl");

	delete_Object3D(object);

	return 0;
}

