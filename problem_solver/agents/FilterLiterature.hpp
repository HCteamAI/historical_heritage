#pragma once

#include <sc-memory/kpm/sc_agent.hpp>

#include "keynodes/keynodes.hpp"
#include "FilterLiterature.generated.hpp"

namespace exampleModule
{

class FilterLiterature : public ScAgent
{
  SC_CLASS(Agent, Event(Keynodes::question_literature_filter, ScEvent::Type::AddOutputEdge))
  SC_GENERATED_BODY()
};

} // namespace exampleModule