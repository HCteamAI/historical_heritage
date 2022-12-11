#pragma once

#include <sc-memory/kpm/sc_agent.hpp>

#include "keynodes/keynodes.hpp"
#include "FilterMonumentalArt.generated.hpp"

namespace exampleModule
{

class FilterMonumentalArt : public ScAgent
{
  SC_CLASS(Agent, Event(Keynodes::question_monumental_filter, ScEvent::Type::AddOutputEdge))
  SC_GENERATED_BODY()
};

} // namespace exampleModule