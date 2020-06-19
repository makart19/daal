/* file: fill_buffer_helper.h */
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

#ifndef __FILL_BUFFER_HELPER_H__
#define __FILL_BUFFER_HELPER_H__

#include "services/buffer.h"

namespace daal
{
namespace oneapi
{
namespace internal
{
template <typename algorithmType>
services::Status fillBuffer(services::Buffer<algorithmType> & buf, size_t nElems, algorithmType val);

} // namespace internal
} // namespace oneapi
} // namespace daal

#endif
