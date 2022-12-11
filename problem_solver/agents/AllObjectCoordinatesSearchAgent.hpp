#pragma once

#include <sc-memory/kpm/sc_agent.hpp>

#include "keynodes/keynodes.hpp"
#include "AllObjectCoordinatesSearchAgent.generated.hpp"

namespace exampleModule
{

class AllObjectCoordinatesSearchAgent : public ScAgent
{
  SC_CLASS(Agent, Event(Keynodes::question_find_all_object_coordinates, ScEvent::Type::AddOutputEdge))
  SC_GENERATED_BODY()
};
}
