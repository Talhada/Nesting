#pragma once

#include <vector>
#include "Nesting.h"

namespace Nesting
{
	struct Job
	{
		// Material to place a part
		Material material;

		// Define an order of placing with part and quantity
		struct Order
		{
			Part part;
			int quantity = 0;
		};

		// Define the list of orders for nesting
		std::vector<Order> orders;
	};
}