#pragma once

#include <sc-memory/kpm/sc_agent.hpp>

#include "keynodes/keynodes.hpp"
#include "FilterPainting.generated.hpp"

namespace exampleModule
{

class FilterPainting : public ScAgent
{
  SC_CLASS(Agent, Event(Keynodes::question_painting_filter, ScEvent::Type::AddOutputEdge))
  SC_GENERATED_BODY()
};

} // namespace exampleModule