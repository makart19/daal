/*******************************************************************************
* Copyright 2020 Intel Corporation
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

#include "oneapi/dal/algo/decision_forest/backend/cpu/infer_kernel.hpp"
#include "oneapi/dal/algo/decision_forest/backend/gpu/infer_kernel.hpp"
#include "oneapi/dal/algo/decision_forest/detail/infer_ops.hpp"
#include "oneapi/dal/backend/dispatcher_dp.hpp"

namespace oneapi::dal::decision_forest::detail {

template <typename Float, typename Task, typename Method>
struct infer_ops_dispatcher<data_parallel_execution_context, Float, Task, Method> {
    infer_result<Task> operator()(const data_parallel_execution_context& ctx,
                                  const descriptor_base<Task>& params,
                                  const infer_input<Task>& input) const {
        using kernel_dispatcher_t =
            dal::backend::kernel_dispatcher<backend::infer_kernel_cpu<Float, Task, Method>,
                                            backend::infer_kernel_gpu<Float, Task, Method>>;
        return kernel_dispatcher_t{}(ctx, params, input);
    }
};

#define INSTANTIATE(F, T, M) \
    template struct infer_ops_dispatcher<data_parallel_execution_context, F, T, M>;

INSTANTIATE(float, task::classification, method::default_dense)
INSTANTIATE(double, task::classification, method::default_dense)

INSTANTIATE(float, task::regression, method::default_dense)
INSTANTIATE(double, task::regression, method::default_dense)
} // namespace oneapi::dal::decision_forest::detail