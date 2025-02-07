#include <iostream>
#include <sstream>
#include "Utils/Utils.h"

Nesting::Result RunNesting(const Nesting::Job& job);

int main()
{
	// Utils::CreateRandomJobs(5);
	
	// Load Jobs
	auto jobs = Utils::LoadGeneratedJobs(5);

	for (int i=0; const auto& job : jobs)
	{
		auto result = RunNesting(job);

		Utils::PrintEfficiency(job, result);
		Utils::PlotToFile(job, result, i++);
	}

	return 0;
}


Nesting::Result RunNesting(const Nesting::Job& job)
{
	Nesting::Result result;
	
	// Use this margin between parts on your algorithm
	const auto partMargin = 2.0;

	
	// TODO : Your code starts here (I leave a suggestion for a starting algorithm)

//	Iterate Over Each Order
//		You have multiple “orders, ” each specifying a part and a quantity.
//		For each order :
//	While there are still parts in the current order’s quantity :
//	Check if the part fits in the current column (Check x and y directions):
//		If it fits :
//		    Add the placed part to result.placedParts.
//		    Decrement quantity for order.
//		    Track your current position (for the next part)
//		    Track the width of the largest part (the width of the current column)
//		If it doesn’t fit :
//	        Move to a new column  
//		    Check again if the new part fits in this new column space :
//	        If yes :
//				Place the part(same steps : position, decrement quantity, update coordinates).
//	        If no :
//				Stop and report (std::cout) that it’s not possible to fit all parts.
//				Try next order (if the part is smaller maybe it fits)				

	return result;
}