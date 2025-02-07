#pragma once

#include <vector>

#include "Nesting.h"

namespace Nesting
{
	struct PlacedPart
	{
		PlacedPart(const Part& part={})
			: id(part.id)
		{
		}

		Guid id = GuidInvalid;
		Point pos;
	};

	struct Result
	{
		std::vector<PlacedPart> placedParts;
	};
}