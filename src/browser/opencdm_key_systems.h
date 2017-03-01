/*
* Copyright 2015 Linaro LtD
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
*/

#ifndef MEDIA_CDM_PPAPI_EXTERNALOCDM_OCDM_KEYSYSTEMS_H_
#define MEDIA_CDM_PPAPI_EXTERNALOCDM_OCDM_KEYSYSTEMS_H_
#include <vector>
#include <memory>

namespace media {
class KeySystemProperties;
}

void AddExternalOpenCdmKeySystems(std::vector<std::unique_ptr<::media::KeySystemProperties>>* key_systems_properties);

#endif