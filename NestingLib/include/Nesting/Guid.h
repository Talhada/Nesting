#pragma once


using Guid = unsigned long long;

constexpr Guid GuidInvalid = -1;

Guid CreateGuid();