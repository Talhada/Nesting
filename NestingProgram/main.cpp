#include <iostream>
#include <sstream>
#include "Utils/Utils.h"

Nesting::Result RunNesting(const Nesting::Job& job);

int main()
{
	// Utils::CreateRandomJobs(5);

	// Load Jobs
	auto jobs = Utils::LoadGeneratedJobs(5);

	for (int i = 0; const auto & job : jobs)
	{
		auto result = RunNesting(job);

		Utils::PrintEfficiency(job, result);
		Utils::PlotToFile(job, result, i++);
	}

	return 0;
}


Nesting::Result RunNesting(const Nesting::Job& job)
{
	// Variables to track the current row
	Nesting::Point currentPos = { 0.0, 0.0 };   // Where the next part will be placed
	double currentColWidth = 0;					// The longest part in this col

	Nesting::Result result;
	auto jb = job;

	// Sort Parts based on width
	std::sort(jb.orders.begin(), jb.orders.end(), [](const Nesting::Job::Order& o1, const Nesting::Job::Order& o2)
		{
			return o1.part.width > o2.part.width;
		});

	const auto partMargin = 2.0;

	// Attempt to place each order in a column-by-column manner
	for (auto& order : jb.orders)
	{
		auto& part = order.part;

		// Attempt to place all parts
		while (order.quantity > 0)
		{
			// Check if we can place this part in the current col
			// Condition 1: It fits vertically (currentY + partHeight <= sheetHeight)
			// Condition 2: It fits horizontally (currentX + partWidth <= sheetWidth)
			if (currentPos.y + part.height <= jb.material.height && currentPos.x + part.width <= jb.material.width)
			{
				// Place the part here
				Nesting::PlacedPart placedPart(part);

				placedPart.pos.x = currentPos.x;
				placedPart.pos.y = currentPos.y;

				result.placedParts.push_back(placedPart);
				--order.quantity;

				// Update the col usage
				currentPos.y += part.height;
				currentPos.y += partMargin;

				// The columns width might need to increase if this part is longer
				if (part.width > currentColWidth)
					currentColWidth = part.width + partMargin;
			}
			else
			{
				// Part doesn't fit in the current column, try a new column
				// Move to next col: x=0, y += currentColWidth
				currentPos.y = 0.0;
				currentPos.x += currentColWidth;

				// Reset row width to 0 (it will be updated by the new part)
				currentColWidth = 0.0;

				// Check if we still fit in the sheet
				if (currentPos.x + part.width <= jb.material.width && part.height <= jb.material.height)
				{
					// Place part at the start of the new col
					Nesting::PlacedPart placedPart(part);

					placedPart.pos.x = currentPos.x;
					placedPart.pos.y = currentPos.y;

					result.placedParts.push_back(placedPart);
					--order.quantity;

					currentPos.y += part.height;
					currentPos.y += partMargin;

					currentColWidth = part.width + partMargin;
				}
				else
				{
					// We can't fit the part even on a new column there's no space
					std::cout << "Cannot fit all order parts\n";
					break; // Go to next Order
				}
			}
		}
	}

	return result;
}