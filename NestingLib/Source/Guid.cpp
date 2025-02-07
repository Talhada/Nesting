#include "Guid.h"

#include "Random.h"

Guid CreateGuid()
{
	return Random::Create<Guid>(1, std::numeric_limits<Guid>::max());
}
