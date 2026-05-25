#ifndef RACE_FACTORY_H
#define RACE_FACTORY_H

#include "Race.h"
#include <memory>
#include <vector>

namespace race_factory {
std::vector<std::unique_ptr<Race>> create_default_races();
}

#endif // RACE_FACTORY_H
