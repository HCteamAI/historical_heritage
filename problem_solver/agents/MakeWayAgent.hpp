#pragma once

#include <sc-memory/kpm/sc_agent.hpp>

#include "keynodes/keynodes.hpp"
#include "MakeWayAgent.generated.hpp"

namespace exampleModule
{

class MakeWayAgent : public ScAgent
{
  SC_CLASS(Agent, Event(Keynodes::question_make_way, ScEvent::Type::AddOutputEdge))
  SC_GENERATED_BODY()
};

} // namespace exampleModule
