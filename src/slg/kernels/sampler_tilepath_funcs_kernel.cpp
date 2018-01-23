#include <string>
namespace slg { namespace ocl {
std::string KernelSource_sampler_tilepath_funcs = 
"#line 2 \"sampler_tilepath_funcs.cl\"\n"
"\n"
"/***************************************************************************\n"
" * Copyright 1998-2018 by authors (see AUTHORS.txt)                        *\n"
" *                                                                         *\n"
" *   This file is part of LuxCoreRender.                                   *\n"
" *                                                                         *\n"
" * Licensed under the Apache License, Version 2.0 (the \"License\");         *\n"
" * you may not use this file except in compliance with the License.        *\n"
" * You may obtain a copy of the License at                                 *\n"
" *                                                                         *\n"
" *     http://www.apache.org/licenses/LICENSE-2.0                          *\n"
" *                                                                         *\n"
" * Unless required by applicable law or agreed to in writing, software     *\n"
" * distributed under the License is distributed on an \"AS IS\" BASIS,       *\n"
" * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.*\n"
" * See the License for the specific language governing permissions and     *\n"
" * limitations under the License.                                          *\n"
" ***************************************************************************/\n"
"\n"
"//------------------------------------------------------------------------------\n"
"// TilePath Sampler Kernel\n"
"//------------------------------------------------------------------------------\n"
"\n"
"#if (PARAM_SAMPLER_TYPE == 3)\n"
"\n"
"__global float *Sampler_GetSampleData(__global Sample *sample, __global float *samplesData) {\n"
"	const size_t gid = get_global_id(0);\n"
"	return &samplesData[gid * TOTAL_U_SIZE];\n"
"}\n"
"\n"
"__global float *Sampler_GetSampleDataPathBase(__global Sample *sample, __global float *sampleData) {\n"
"	return sampleData;\n"
"}\n"
"\n"
"__global float *Sampler_GetSampleDataPathVertex(__global Sample *sample,\n"
"		__global float *sampleDataPathBase, const uint depth) {\n"
"	return &sampleDataPathBase[IDX_BSDF_OFFSET + depth * VERTEX_SAMPLE_SIZE];\n"
"}\n"
"\n"
"float Sampler_GetSamplePath(Seed *seed, __global Sample *sample,\n"
"		__global float *sampleDataPathBase, const uint index) {\n"
"	return Rnd_FloatValue(seed);\n"
"}\n"
"\n"
"float Sampler_GetSamplePathVertex(Seed *seed, __global Sample *sample,\n"
"		__global float *sampleDataPathVertexBase,\n"
"		const uint depth, const uint index) {\n"
"	return Rnd_FloatValue(seed);\n"
"}\n"
"\n"
"void Sampler_SplatSample(\n"
"		Seed *seed,\n"
"		__global Sample *sample,\n"
"		__global float *sampleData\n"
"		FILM_PARAM_DECL\n"
"		) {\n"
"#if defined(RENDER_ENGINE_RTPATHOCL)\n"
"	// Check if I'm in preview phase\n"
"	if (sample->currentTilePass < PARAM_RTPATHOCL_PREVIEW_RESOLUTION_REDUCTION_STEP) {\n"
"		// I have to copy the current pixel to fill the assigned square\n"
"		for (uint y = 0; y < PARAM_RTPATHOCL_PREVIEW_RESOLUTION_REDUCTION; ++y) {\n"
"			for (uint x = 0; x < PARAM_RTPATHOCL_PREVIEW_RESOLUTION_REDUCTION; ++x) {\n"
"				// The sample weight is very low so this value is rapidly replaced\n"
"				// during normal rendering\n"
"				const uint px = sample->result.pixelX + x;\n"
"				const uint py = sample->result.pixelY + y;\n"
"				// px and py are unsigned so there is no need to check if they are >= 0\n"
"				if ((px < filmWidth) && (py < filmHeight)) {\n"
"					Film_AddSample(px, py,\n"
"							&sample->result, .001f\n"
"							FILM_PARAM);\n"
"				}\n"
"			}\n"
"		}\n"
"	} else\n"
"		Film_AddSample(sample->result.pixelX, sample->result.pixelY,\n"
"			&sample->result, 1.f\n"
"			FILM_PARAM);\n"
"#else\n"
"	Film_AddSample(sample->result.pixelX, sample->result.pixelY,\n"
"			&sample->result, 1.f\n"
"			FILM_PARAM);\n"
"#endif\n"
"}\n"
"\n"
"void Sampler_NextSample(\n"
"		Seed *seed,\n"
"		__global Sample *sample,\n"
"		__global float *sampleData\n"
"		) {\n"
"	// sampleData[] is not used at all in random sampler\n"
"}\n"
"\n"
"void Sampler_Init(Seed *seed, __global SamplerSharedData *samplerSharedData,\n"
"		__global Sample *sample, __global float *sampleData) {\n"
"	Sampler_NextSample(seed, sample, sampleData);\n"
"}\n"
"\n"
"#endif\n"
; } }