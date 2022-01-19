#include "gltfLoader.h"
#include <iostream>

cgltf_data* LoadGLTFFile(const char* path) {
	cgltf_options options;
	memset(&options, 0, sizeof(cgltf_options));
	cgltf_data* data = NULL;

	cgltf_result result = cgltf_parse_file(&options, path, &data);
	if (result != cgltf_result_success) {
		std::cout << "could not load input file.\n";
		return 0;
	}

	result = cgltf_load_buffers(&options, data, path);
	if (result != cgltf_result_success) {
		std::cout << "could not load buffers.\n";
		return 0;
	}

	result = cgltf_validate(data);
	if (result != cgltf_result_success) {
		std::cout << "invalid gltf file.\n";
		return 0;
	}

	return data;
}


void FreeGLTFFile(cgltf_data* data) {
	if (data == 0) {
		std::cout << "can't free null data\n";
	}
	else {
		cgltf_free(data);
	}
}