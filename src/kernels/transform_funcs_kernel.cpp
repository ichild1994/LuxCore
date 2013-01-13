#include <string>
namespace luxrays { namespace ocl {
std::string KernelSource_transform_funcs = 
"#line 2 \"transform_funcs.cl\"\n"
"\n"
"/***************************************************************************\n"
" *   Copyright (C) 1998-2010 by authors (see AUTHORS.txt )                 *\n"
" *                                                                         *\n"
" *   This file is part of LuxRays.                                         *\n"
" *                                                                         *\n"
" *   LuxRays is free software; you can redistribute it and/or modify       *\n"
" *   it under the terms of the GNU General Public License as published by  *\n"
" *   the Free Software Foundation; either version 3 of the License, or     *\n"
" *   (at your option) any later version.                                   *\n"
" *                                                                         *\n"
" *   LuxRays is distributed in the hope that it will be useful,            *\n"
" *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *\n"
" *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *\n"
" *   GNU General Public License for more details.                          *\n"
" *                                                                         *\n"
" *   You should have received a copy of the GNU General Public License     *\n"
" *   along with this program.  If not, see <http://www.gnu.org/licenses/>. *\n"
" *                                                                         *\n"
" *   LuxRays website: http://www.luxrender.net                             *\n"
" ***************************************************************************/\n"
"\n"
"float3 Transform_ApplyPoint(__global Transform *trans, const float3 point) {\n"
"	return Matrix4x4_ApplyPoint(&trans->m, point);\n"
"}\n"
"\n"
"float3 Transform_ApplyVector(__global Transform *trans, const float3 vector) {\n"
"	return Matrix4x4_ApplyVector(&trans->m, vector);\n"
"}\n"
"\n"
"float3 Transform_InvApplyPoint(__global Transform *trans, const float3 point) {\n"
"	return Matrix4x4_ApplyPoint(&trans->mInv, point);\n"
"}\n"
"\n"
"float3 Transform_InvApplyVector(__global Transform *trans, const float3 vector) {\n"
"	return Matrix4x4_ApplyVector(&trans->mInv, vector);\n"
"}\n"
; } }
