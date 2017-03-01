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

#include "opencdm_key_systems.h"
#include "base/strings/string16.h"
#include "media/base/key_system_properties.h"
#include "base/logging.h"

using namespace std;
using namespace media;

using media::KeySystemProperties;
using media::SupportedCodecs;

// Playready key system
#if defined(ENABLE_PEPPER_CDMS)

  static const char kExternalOpenCdmPepperType[] = 
    "application/x-ppapi-open-cdm";
  
#endif  // defined(ENABLE_PEPPER_CDMS)

// KeySystemProperties implementation for Playready Key systems.
class PlayreadyProperties : public KeySystemProperties {
 public:
  explicit PlayreadyProperties(const std::string& key_system_name)
      : key_system_name_(key_system_name) {}

  std::string GetKeySystemName() const override { return key_system_name_; }
  bool IsSupportedInitDataType(
      media::EmeInitDataType init_data_type) const override {
    switch (init_data_type) {
      case media::EmeInitDataType::WEBM:
      case media::EmeInitDataType::KEYIDS:
        return true;

      case media::EmeInitDataType::CENC:
#if defined(USE_PROPRIETARY_CODECS)
        return true;
#else
        return false;
#endif  // defined(USE_PROPRIETARY_CODECS)

      case media::EmeInitDataType::UNKNOWN:
        return false;
    }
    NOTREACHED();
    return false;
  }

  SupportedCodecs GetSupportedCodecs() const override {
#if defined(USE_PROPRIETARY_CODECS)
    return media::EME_CODEC_MP4_ALL | media::EME_CODEC_WEBM_ALL;
#else
    return media::EME_CODEC_WEBM_ALL;
#endif // defined(USE_PROPRIETARY_CODECS)
  }

  media::EmeConfigRule GetRobustnessConfigRule(
      media::EmeMediaType media_type,
      const std::string& requested_robustness) const override {
    return requested_robustness.empty() ? media::EmeConfigRule::SUPPORTED
                                        : media::EmeConfigRule::NOT_SUPPORTED;
  }

  // Persistent license sessions are faked.
  media::EmeSessionTypeSupport GetPersistentLicenseSessionSupport()
      const override {
    return media::EmeSessionTypeSupport::SUPPORTED;
  }

  media::EmeSessionTypeSupport GetPersistentReleaseMessageSessionSupport()
      const override {
    return media::EmeSessionTypeSupport::NOT_SUPPORTED;
  }

  media::EmeFeatureSupport GetPersistentStateSupport() const override {
    return media::EmeFeatureSupport::REQUESTABLE;
  }

  media::EmeFeatureSupport GetDistinctiveIdentifierSupport() const override {
    return media::EmeFeatureSupport::NOT_SUPPORTED;
  }

  std::string GetPepperType() const override {
    return kExternalOpenCdmPepperType;
  }

 private:
  const std::string key_system_name_;
};


#ifdef OCDM_USE_PLAYREADY

static void AddPlayreadyKeySystem(std::vector<std::unique_ptr<::media::KeySystemProperties>>* concrete_key_systems) {
  static const char kExternalOpenCdmKeySystem[] =
      "com.microsoft.playready";

  concrete_key_systems->emplace_back(
  new PlayreadyProperties(kExternalOpenCdmKeySystem));
}

void AddExternalOpenCdmKeySystems(
  std::vector<std::unique_ptr<::media::KeySystemProperties>>* key_systems_properties)
{
  #ifdef OCDM_USE_PLAYREADY
  AddPlayreadyKeySystem(key_systems_properties);
  #endif
}

#endif  // defined(ENABLE_PEPPER_CDMS)
