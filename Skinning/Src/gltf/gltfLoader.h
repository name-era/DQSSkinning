#pragma once
#include "cgltf/cgltf.h"
#include "pose.h"
#include "animationClip.h"
#include "transform.h"

cgltf_data* LoadGLTFFile(const char* path);
void FreeGLTFFile(cgltf_data* data);
Pose LoadRestPose(cgltf_data* data);
std::vector<AnimationClip> LoadAnimationClips(cgltf_data* data);