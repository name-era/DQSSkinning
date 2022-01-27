#pragma once
#include "cgltf/cgltf.h"
#include "pose.h"

cgltf_data* LoadGLTFFile(const char* path);
void FreeGLTFFile(cgltf_data* data);
Pose LoadRestPose(cgltf_data* data);