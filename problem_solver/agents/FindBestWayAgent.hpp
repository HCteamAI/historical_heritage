#pragma once

#include <sc-memory/kpm/sc_agent.hpp>

#include "keynodes/keynodes.hpp"
#include "FindBestWayAgent.generated.hpp"

namespace exampleModule
{

class FindBestWayAgent : public ScAgent
{
  SC_CLASS(Agent, Event(Keynodes::question_find_best_way, ScEvent::Type::AddOutputEdge))
  SC_GENERATED_BODY()
};

} // namespace exampleModule
