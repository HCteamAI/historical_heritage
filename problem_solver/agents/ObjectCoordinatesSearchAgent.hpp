#pragma once

#include <sc-memory/kpm/sc_agent.hpp>

#include "keynodes/keynodes.hpp"
#include "ObjectCoordinatesSearchAgent.generated.hpp"

namespace exampleModule
{

class ObjectCoordinatesSearchAgent : public ScAgent
{
  SC_CLASS(Agent, Event(Keynodes::question_find_object_coordinates, ScEvent::Type::AddOutputEdge))
  SC_GENERATED_BODY()
};
}
