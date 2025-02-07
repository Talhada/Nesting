#include "Utils.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

namespace Utils
{

	bool SaveJob(const Nesting::Job& job, const std::string& fileName)
	{
		std::ofstream of(fileName.c_str());

		if (!of)
			return false;

		nlohmann::json data = job;
		auto strData = data.dump(2);

		of << strData;

		return true;

	}

	bool LoadJob(Nesting::Job& job, const std::string& fileName)
	{
		std::ifstream of(fileName.c_str());

		if (!of)
			return false;

		auto data = nlohmann::json::parse(of);

		job = data;
		return true;

	}

	Nesting::Job CreateRandomJob()
	{
		Nesting::Job job;

		const int numParts = Random::Create(5, 15);

		// Generate material
		job.material.width = Random::Create(2000.0, 5000.0);
		job.material.height = Random::Create(1000.0, 2750.0);

		// Generate orders
		job.orders.resize(numParts);
		for (int i = 0; i < numParts; ++i)
		{
			job.orders[i].part.width = Random::Create(100.0, 450.0);
			job.orders[i].part.height = Random::Create(50.0, 350.0);
			job.orders[i].quantity = Random::Create(1, 10);
		}

		return job;
	}

	bool CreateRandomJobs(int amount /*= 1*/)
	{
		bool r = true;
		
		for (int i=0; i<amount; ++i)
		{
			std::stringstream ss;
			ss << "NestingJob_" << i << ".json";
			auto fileName = ss.str();

			auto job = CreateRandomJob();
			r &= SaveJob(job, fileName.c_str());
		}

		return r;
	}

	std::vector<Nesting::Job> LoadGeneratedJobs(int amount/*=1*/)
	{
		std::vector<Nesting::Job> jobs;

		for (int i = 0; i < amount; ++i)
		{
			std::stringstream ss;
			ss << "NestingJob_" << i << ".json";

			Nesting::Job job;
			LoadJob(job, ss.str().c_str());
			jobs.push_back(job);
		}

		return jobs;
	}

	std::ostream& PlotRectangle(std::ostream& os, const double& x, const double& y, const double& w, const double h)
	{
		const auto units = 40.0;

		os << "PA" << units * x << "," << units * y << ";\n";
		os << "PD" << units * (x + w) << "," << units * y << ";\n";
		os << "PD" << units * (x + w) << "," << units * (y + h) << ";\n";
		os << "PD" << units * x << "," << units * (y + h) << ";\n";
		os << "PD" << units * x << "," << units * y << ";\n";
		os << "PU;\n";

		return os;
	}

	bool PlotToFile(const Nesting::Job& job, const Nesting::Result& result, int index)
	{
		std::stringstream ss;
		ss << "Nesting_" << index << ".plt";

		std::ofstream of(ss.str().c_str());

		if (!of)
			return false;

		// Plot result
		of << "SP1;\n";
		PlotRectangle(of, 0, 0, job.material.width, job.material.height);

		of << "SP2;\n";
		for (const auto& placedPart : result.placedParts)
		{
			auto partID = placedPart.id;
			// Get part geometry from order
			auto it = std::find_if(job.orders.begin(), job.orders.end(), [partID](const Nesting::Job::Order& ord)
				{
					return partID == ord.part.id;
				});

			if (it == job.orders.end())
				throw("Attempting to save a part id that does not exist. Malformed nesting result");

			PlotRectangle(of, placedPart.pos.x, placedPart.pos.y, it->part.width, it->part.height);
		}

		return true;
	}

	double PrintEfficiency(const Nesting::Job& job, const Nesting::Result& result)
	{
		const auto materialArea = job.material.width * job.material.height;

		if (materialArea == 0.0)
			return 0.0;

		auto partArea = 0.0;

		for (const auto& placedPart : result.placedParts)
		{
			auto id = placedPart.id;
			auto it = std::find_if(job.orders.begin(), job.orders.end(), [id](const Nesting::Job::Order& o)
				{
					return o.part.id == id;
				});

			if (it == job.orders.end())
				throw("Part not found, invalid nesting result generated");

			partArea += it->part.width * it->part.height;
		}

		auto efficiency = partArea / materialArea * 100.0;

		std::cout << "Nesting Efficiency = " << efficiency << " %\n";

		return efficiency;
	}
}