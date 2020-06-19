/* file: fill_buffer_helper.cl */
/*******************************************************************************
* Copyright 2014-2020 Intel Corporation
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

/*
//++
//  Implementation of fill buffer helper OpenCL kernels.
//--
*/

#ifndef ___FILL_BUFFER_HELPER_KERNELS_CL__
#define ___FILL_BUFFER_HELPER_KERNELS_CL__

#include <string.h>

#define DECLARE_SOURCE_DAAL(name, src) static const char *(name) = #src;

DECLARE_SOURCE_DAAL(
    clFillBufferHelper,

    __kernel void fillBuffer(__global algorithmFPType * buf, algorithmFPType val) {
        const int id = get_global_id(0);
        buf[id]      = val;
    }

);

#undef DECLARE_SOURCE_DAAL

#endif
