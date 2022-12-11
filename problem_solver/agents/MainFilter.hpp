#pragma once

#include <sc-memory/kpm/sc_agent.hpp>

#include "keynodes/keynodes.hpp"
#include "MainFilter.generated.hpp"

namespace exampleModule
{

class MainFilter : public ScAgent
{
  SC_CLASS(Agent, Event(Keynodes::question_filter_by, ScEvent::Type::AddOutputEdge))
  SC_GENERATED_BODY()
};

} // namespace exampleModule