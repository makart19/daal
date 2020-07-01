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

#include "oneapi/dal/detail/common.hpp"
#include "oneapi/dal/algo/decision_forest/infer_types.hpp"

namespace oneapi::dal::decision_forest {

class detail::infer_input_impl : public base {
  public:
    infer_input_impl(const model& trained_model, const table& data)
        : trained_model(trained_model), data(data) {}
    model trained_model;
    table data;
};

class detail::infer_result_impl : public base {
  public:
    table prediction;
    table probabilities;
    table log_probabilities;
};

using detail::infer_input_impl;
using detail::infer_result_impl;

infer_input::infer_input(const model& trained_model, const table& data)
    : impl_(new infer_input_impl(trained_model, data)) {}

model infer_input::get_model() const {
    return impl_->trained_model;
}

table infer_input::get_data() const {
    return impl_->data;
}

void infer_input::set_model_impl(const model& value) {
    impl_->trained_model = value;
}

void infer_input::set_data_impl(const table& value) {
    impl_->data = value;
}

/* infer_result implementation */

infer_result::infer_result() : impl_(new infer_result_impl{}) {}

table infer_result::get_prediction() const {
    return impl_->prediction;
}

table infer_result::get_probabilities() const {
    return impl_->probabilities;
}
/*
table infer_result::get_log_probabilities() const {
    return impl_->log_probabilities;
}
*/
void infer_result::set_prediction_impl(const table &value) {
    impl_->prediction = value;
}

void infer_result::set_probabilities_impl(const table &value) {
    impl_->probabilities = value;
}    
/*
void infer_result::set_log_probabilities_impl(const table &value) {
    impl_->log_probabilities = value;
} 
*/
} // namespace oneapi::dal::decision_forest
