/* file: fill_buffer_helper.cpp */
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

#include "src/sycl/fill_buffer_helper.h"
#include "src/sycl/cl_kernels/fill_buffer_helper.cl"
#include "sycl/internal/types_utils.h"
#include "sycl/internal/execution_context.h"
#include "sycl/internal/utils.h"
#include "src/externals/service_ittnotify.h"

namespace daal
{
namespace oneapi
{
namespace internal
{
DAAL_ITTNOTIFY_DOMAIN(daal.oneapi.internal.fill_buffer_helper);

template <typename algorithmType>
static void buildProgram(ClKernelFactoryIface & kernelFactory)
{
    services::String cachekey("__daal_oneapi_internal_fill_buffer_helper");
    services::String buildOptions = getKeyFPType<algorithmType>();
    cachekey.add(buildOptions);
    kernelFactory.build(ExecutionTargetIds::device, cachekey.c_str(), clFillBufferHelper, buildOptions.c_str());
}

template <typename algorithmType>
services::Status fillBuffer(services::Buffer<algorithmType> & buf, size_t nElems, algorithmType val)
{
    DAAL_ITTNOTIFY_SCOPED_TASK(fillBufferHelper.fillBuffer);
    services::Status status;

    ExecutionContextIface & ctx    = services::Environment::getInstance()->getDefaultExecutionContext();
    ClKernelFactoryIface & factory = ctx.getClKernelFactory();

    buildProgram<algorithmType>(factory);

    const char * const kernelName = "fillBuffer";
    KernelPtr kernel              = factory.getKernel(kernelName);
    DAAL_ITTNOTIFY_SCOPED_TASK(fillFPBuffer);

    {
        KernelArguments args(2);
        args.set(0, buf, AccessModeIds::write);
        args.set(1, val);

        KernelRange global_range(nElems);

        ctx.run(global_range, kernel, args, &status);
        DAAL_CHECK_STATUS_VAR(status);
    }

    return status;
}

template services::Status fillBuffer<float>(services::Buffer<float> & buf, size_t nElems, float val);
template services::Status fillBuffer<double>(services::Buffer<double> & buf, size_t nElems, double val);
template services::Status fillBuffer<int32_t>(services::Buffer<int32_t> & buf, size_t nElems, int32_t val);
template services::Status fillBuffer<uint32_t>(services::Buffer<uint32_t> & buf, size_t nElems, uint32_t val);

} // namespace internal
} // namespace oneapi
} // namespace daal
