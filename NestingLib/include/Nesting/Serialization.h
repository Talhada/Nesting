#pragma once

#include "Nesting.h"
#include "NestingJob.h"
#include "NestingResult.h"
#include <nlohmann/json.hpp>

namespace Nesting
{
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Point, x, y);
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Part,id, width, height);
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Material, width, height);

	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Job::Order, part, quantity);
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Job, material, orders);

	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(PlacedPart, id, pos);
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Result, placedParts);
}