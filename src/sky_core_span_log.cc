/*
 * Copyright 2021 SkyAPM
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */


#include "sky_core_span_log.h"

#include <utility>
#include <string>
#include <sky_utils.h>

SkyCoreSpanLog::SkyCoreSpanLog(std::string key, std::string value) : _key(std::move(key)), _value(std::move(value)) {
    _time = getUnixTimeStamp();
}

long SkyCoreSpanLog::getTime() {
    return _time;
}

const std::string &SkyCoreSpanLog::getKey() {
    return _key;
}

const std::string &SkyCoreSpanLog::getValue() {
    return _value;
}
