#include "gltfLoader.h"
#include <iostream>

cgltf_data* LoadGLTFFile(const char* path) {

}


void FreeGLTFFile(cgltf_data* data) {
	if (data == 0) {
		std::cout << "can't free null data\n";
	}
	else {
		cgltf_free(data);
	}
}