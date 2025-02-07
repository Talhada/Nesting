#pragma once

#include "Guid.h"

namespace Nesting
{
	struct Point 
	{
		double x = 0.0;
		double y = 0.0;
	};

	struct Part
	{
		Part()
			: id(CreateGuid())
		{
		}

		Guid id;
		double width = 0;
		double height = 0;
	};

	struct Material
	{
		double width = 0;
		double height = 0;
	};
}