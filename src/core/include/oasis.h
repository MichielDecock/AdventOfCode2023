#pragma once
#include <string>
#include <vector>

namespace core
{

using Value = long long;
using Values = std::vector<Value>;

Values extrapolatedValues(const char* fileName);

Value sum(const Values& numbers);

} // namespace core
