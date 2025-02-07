#pragma once

#include <string>


#include <Nesting/Serialization.h>
#include <Nesting/NestingJob.h>
#include <Nesting/Random.h>

namespace Utils
{
	// Creates Random job data for testing
	bool CreateRandomJobs(int amount=1);

	// Loads generated jobs to a list
	std::vector<Nesting::Job> LoadGeneratedJobs(int amount/*=1*/);

	// Loads a job from a json file
	bool LoadJob(Nesting::Job& job, const std::string& fileName);

	// Plots a Nesting to a resulting .plt file
	bool PlotToFile(const Nesting::Job& job, const Nesting::Result& result, int index);

	// Returns and prints the efficiency of a Nesting
	double PrintEfficiency(const Nesting::Job& job, const Nesting::Result& result);
}
