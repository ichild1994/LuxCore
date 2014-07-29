#include <string>
namespace slg { namespace ocl {
std::string KernelSource_materialdefs_funcs_matte = 
"#line 2 \"materialdefs_funcs_matte.cl\"\n"
"\n"
"/***************************************************************************\n"
" * Copyright 1998-2013 by authors (see AUTHORS.txt)                        *\n"
" *                                                                         *\n"
" *   This file is part of LuxRender.                                       *\n"
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
"// Matte material\n"
"//------------------------------------------------------------------------------\n"
"\n"
"#if defined (PARAM_ENABLE_MAT_MATTE)\n"
"\n"
"BSDFEvent MatteMaterial_GetEventTypes() {\n"
"	return DIFFUSE | REFLECT;\n"
"}\n"
"\n"
"bool MatteMaterial_IsDelta() {\n"
"	return false;\n"
"}\n"
"\n"
"#if defined(PARAM_HAS_PASSTHROUGH)\n"
"float3 MatteMaterial_GetPassThroughTransparency(__global Material *material,\n"
"		__global HitPoint *hitPoint, const float3 localFixedDir, const float passThroughEvent\n"
"		TEXTURES_PARAM_DECL) {\n"
"	return BLACK;\n"
"}\n"
"#endif\n"
"\n"
"float3 MatteMaterial_ConstEvaluate(\n"
"		__global HitPoint *hitPoint, const float3 lightDir, const float3 eyeDir,\n"
"		BSDFEvent *event, float *directPdfW,\n"
"		const float3 kdVal) {\n"
"	if (directPdfW)\n"
"		*directPdfW = fabs(lightDir.z * M_1_PI_F);\n"
"\n"
"	*event = DIFFUSE | REFLECT;\n"
"\n"
"	return Spectrum_Clamp(kdVal) * fabs(lightDir.z * M_1_PI_F);\n"
"}\n"
"\n"
"float3 MatteMaterial_ConstSample(__global HitPoint *hitPoint, const float3 fixedDir, float3 *sampledDir,\n"
"		const float u0, const float u1, \n"
"#if defined(PARAM_HAS_PASSTHROUGH)\n"
"		const float passThroughEvent,\n"
"#endif\n"
"		float *pdfW, float *cosSampledDir, BSDFEvent *event,\n"
"		const BSDFEvent requestedEvent,\n"
"		const float3 kdVal) {\n"
"	if (!(requestedEvent & (DIFFUSE | REFLECT)) ||\n"
"			(fabs(fixedDir.z) < DEFAULT_COS_EPSILON_STATIC))\n"
"		return BLACK;\n"
"\n"
"	*sampledDir = (signbit(fixedDir.z) ? -1.f : 1.f) * CosineSampleHemisphereWithPdf(u0, u1, pdfW);\n"
"\n"
"	*cosSampledDir = fabs((*sampledDir).z);\n"
"	if (*cosSampledDir < DEFAULT_COS_EPSILON_STATIC)\n"
"		return BLACK;\n"
"\n"
"	*event = DIFFUSE | REFLECT;\n"
"\n"
"	return Spectrum_Clamp(kdVal);\n"
"}\n"
"\n"
"#if defined(PARAM_DIASBLE_MAT_DYNAMIC_EVALUATION)\n"
"float3 MatteMaterial_Sample(__global Material *material,\n"
"		__global HitPoint *hitPoint, const float3 fixedDir, float3 *sampledDir,\n"
"		const float u0, const float u1, \n"
"#if defined(PARAM_HAS_PASSTHROUGH)\n"
"		const float passThroughEvent,\n"
"#endif\n"
"		float *pdfW, float *cosSampledDir, BSDFEvent *event,\n"
"		const BSDFEvent requestedEvent\n"
"		TEXTURES_PARAM_DECL) {\n"
"	const float3 kdVal = Texture_GetSpectrumValue(material->matte.kdTexIndex, hitPoint\n"
"			TEXTURES_PARAM);\n"
"	\n"
"	return MatteMaterial_ConstSample(hitPoint, fixedDir, sampledDir,\n"
"			u0, u1, \n"
"#if defined(PARAM_HAS_PASSTHROUGH)\n"
"			passThroughEvent,\n"
"#endif\n"
"			pdfW, cosSampledDir, event, requestedEvent,\n"
"			kdVal);\n"
"}\n"
"\n"
"float3 MatteMaterial_Evaluate(__global Material *material,\n"
"		__global HitPoint *hitPoint, const float3 lightDir, const float3 eyeDir,\n"
"		BSDFEvent *event, float *directPdfW\n"
"		TEXTURES_PARAM_DECL) {\n"
"	const float3 kdVal = Texture_GetSpectrumValue(material->matte.kdTexIndex, hitPoint\n"
"			TEXTURES_PARAM);\n"
"\n"
"	return MatteMaterial_ConstEvaluate(hitPoint, lightDir, eyeDir,\n"
"			event, directPdfW,\n"
"			kdVal);\n"
"}\n"
"#endif\n"
"\n"
"#endif\n"
"\n"
"//------------------------------------------------------------------------------\n"
"// Rough matte material\n"
"//------------------------------------------------------------------------------\n"
"\n"
"#if defined (PARAM_ENABLE_MAT_ROUGHMATTE)\n"
"\n"
"BSDFEvent RoughMatteMaterial_GetEventTypes() {\n"
"	return DIFFUSE | REFLECT;\n"
"}\n"
"\n"
"bool RoughMatteMaterial_IsDelta() {\n"
"	return false;\n"
"}\n"
"\n"
"#if defined(PARAM_HAS_PASSTHROUGH)\n"
"float3 RoughMatteMaterial_GetPassThroughTransparency(__global Material *material,\n"
"		__global HitPoint *hitPoint, const float3 localFixedDir, const float passThroughEvent\n"
"		TEXTURES_PARAM_DECL) {\n"
"	return BLACK;\n"
"}\n"
"#endif\n"
"\n"
"float3 RoughMatteMaterial_ConstEvaluate(\n"
"		__global HitPoint *hitPoint, const float3 lightDir, const float3 eyeDir,\n"
"		BSDFEvent *event, float *directPdfW,\n"
"		const float s, const float3 kdVal) {\n"
"	if (directPdfW)\n"
"		*directPdfW = fabs(lightDir.z * M_1_PI_F);\n"
"\n"
"	*event = DIFFUSE | REFLECT;\n"
"\n"
"	const float sigma2 = s * s;\n"
"	const float A = 1.f - (sigma2 / (2.f * (sigma2 + 0.33f)));\n"
"	const float B = 0.45f * sigma2 / (sigma2 + 0.09f);\n"
"	const float sinthetai = SinTheta(eyeDir);\n"
"	const float sinthetao = SinTheta(lightDir);\n"
"	float maxcos = 0.f;\n"
"	if (sinthetai > 1e-4f && sinthetao > 1e-4f) {\n"
"			const float dcos = CosPhi(lightDir) * CosPhi(eyeDir) +\n"
"					SinPhi(lightDir) * SinPhi(eyeDir);\n"
"			maxcos = fmax(0.f, dcos);\n"
"	}\n"
"	return Spectrum_Clamp(kdVal) * fabs(lightDir.z * M_1_PI_F) *\n"
"		(A + B * maxcos * sinthetai * sinthetao / fmax(fabs(CosTheta(lightDir)), fabs(CosTheta(eyeDir))));\n"
"}\n"
"\n"
"float3 RoughMatteMaterial_ConstSample(\n"
"		__global HitPoint *hitPoint, const float3 fixedDir, float3 *sampledDir,\n"
"		const float u0, const float u1, \n"
"#if defined(PARAM_HAS_PASSTHROUGH)\n"
"		const float passThroughEvent,\n"
"#endif\n"
"		float *pdfW, float *cosSampledDir, BSDFEvent *event,\n"
"		const BSDFEvent requestedEvent,\n"
"		const float s, const float3 kdVal) {\n"
"	if (!(requestedEvent & (DIFFUSE | REFLECT)) ||\n"
"			(fabs(fixedDir.z) < DEFAULT_COS_EPSILON_STATIC))\n"
"		return BLACK;\n"
"\n"
"	*sampledDir = (signbit(fixedDir.z) ? -1.f : 1.f) * CosineSampleHemisphereWithPdf(u0, u1, pdfW);\n"
"\n"
"	*cosSampledDir = fabs((*sampledDir).z);\n"
"	if (*cosSampledDir < DEFAULT_COS_EPSILON_STATIC)\n"
"		return BLACK;\n"
"\n"
"	*event = DIFFUSE | REFLECT;\n"
"\n"
"	const float sigma2 = s * s;\n"
"	const float A = 1.f - (sigma2 / (2.f * (sigma2 + 0.33f)));\n"
"	const float B = 0.45f * sigma2 / (sigma2 + 0.09f);\n"
"	const float sinthetai = SinTheta(fixedDir);\n"
"	const float sinthetao = SinTheta(*sampledDir);\n"
"	float maxcos = 0.f;\n"
"	if (sinthetai > 1e-4f && sinthetao > 1e-4f) {\n"
"			const float dcos = CosPhi(*sampledDir) * CosPhi(fixedDir) +\n"
"					SinPhi(*sampledDir) * SinPhi(fixedDir);\n"
"			maxcos = fmax(0.f, dcos);\n"
"	}\n"
"\n"
"	return Spectrum_Clamp(kdVal) *\n"
"		(A + B * maxcos * sinthetai * sinthetao / fmax(fabs(CosTheta(*sampledDir)), fabs(CosTheta(fixedDir))));\n"
"}\n"
"\n"
"#if defined(PARAM_DIASBLE_MAT_DYNAMIC_EVALUATION)\n"
"float3 RoughMatteMaterial_Evaluate(__global Material *material,\n"
"		__global HitPoint *hitPoint, const float3 lightDir, const float3 eyeDir,\n"
"		BSDFEvent *event, float *directPdfW\n"
"		TEXTURES_PARAM_DECL) {\n"
"	const float s = Texture_GetFloatValue(material->roughmatte.sigmaTexIndex, hitPoint TEXTURES_PARAM);\n"
"	const float3 kdVal = Texture_GetSpectrumValue(material->roughmatte.kdTexIndex, hitPoint\n"
"			TEXTURES_PARAM);\n"
"\n"
"	return RoughMatteMaterial_ConstEvaluate(\n"
"			hitPoint, lightDir, eyeDir,\n"
"			event, directPdfW,\n"
"			s, kdVal);\n"
"}\n"
"\n"
"float3 RoughMatteMaterial_Sample(__global Material *material,\n"
"		__global HitPoint *hitPoint, const float3 fixedDir, float3 *sampledDir,\n"
"		const float u0, const float u1, \n"
"#if defined(PARAM_HAS_PASSTHROUGH)\n"
"		const float passThroughEvent,\n"
"#endif\n"
"		float *pdfW, float *cosSampledDir, BSDFEvent *event,\n"
"		const BSDFEvent requestedEvent\n"
"		TEXTURES_PARAM_DECL) {\n"
"\n"
"	const float s = Texture_GetFloatValue(material->roughmatte.sigmaTexIndex, hitPoint TEXTURES_PARAM);\n"
"	const float3 kdVal = Texture_GetSpectrumValue(material->roughmatte.kdTexIndex, hitPoint\n"
"			TEXTURES_PARAM);\n"
"\n"
"	return RoughMatteMaterial_ConstSample(\n"
"			hitPoint, fixedDir, sampledDir,\n"
"			u0, u1, \n"
"#if defined(PARAM_HAS_PASSTHROUGH)\n"
"			passThroughEvent,\n"
"#endif\n"
"			pdfW, cosSampledDir, event,\n"
"			requestedEvent,\n"
"			s, kdVal);\n"
"}\n"
"#endif\n"
"\n"
"#endif\n"
; } }
