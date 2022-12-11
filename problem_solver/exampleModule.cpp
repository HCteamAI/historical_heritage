/*
* This source file is part of an OSTIS project. For the latest info, see http://ostis.net
* Distributed under the MIT License
* (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
*/

#include "exampleModule.hpp"
#include "keynodes/keynodes.hpp"
#include "agents/SubdividingSearchAgent.hpp"
#include "agents/IsomorphicSearchAgent.hpp"
#include "agents/FindBestWayAgent.hpp"
#include "agents/agent_find_objects_in_radius.hpp"
#include "agents/MainFilter.hpp"
#include "agents/FilterMonumentalArt.hpp"
#include "agents/FilterLiterature.hpp"
#include "agents/FilterPainting.hpp"
#include "agents/AllObjectCoordinatesSearchAgent.hpp"
#include "agents/ObjectCoordinatesSearchAgent.hpp"


using namespace exampleModule;

SC_IMPLEMENT_MODULE(ExampleModule)

sc_result ExampleModule::InitializeImpl()
{
  if (!exampleModule::Keynodes::InitGlobal())
    return SC_RESULT_ERROR;

  SC_AGENT_REGISTER(SubdividingSearchAgent)
  SC_AGENT_REGISTER(IsomorphicSearchAgent)
  SC_AGENT_REGISTER(FindBestWayAgent)
  SC_AGENT_REGISTER(agent_find_objects_in_radius)
  SC_AGENT_REGISTER(MainFilter)
  SC_AGENT_REGISTER(FilterMonumentalArt)
  SC_AGENT_REGISTER(FilterLiterature)
  SC_AGENT_REGISTER(FilterPainting)
  SC_AGENT_REGISTER(ObjectCoordinatesSearchAgent)
  SC_AGENT_REGISTER(AllObjectCoordinatesSearchAgent)

  return SC_RESULT_OK;
}

sc_result ExampleModule::ShutdownImpl()
{
  SC_AGENT_UNREGISTER(SubdividingSearchAgent)
  SC_AGENT_UNREGISTER(IsomorphicSearchAgent)
  SC_AGENT_UNREGISTER(FindBestWayAgent)
  SC_AGENT_UNREGISTER(agent_find_objects_in_radius)
  SC_AGENT_UNREGISTER(MainFilter)
  SC_AGENT_UNREGISTER(FilterMonumentalArt)
  SC_AGENT_UNREGISTER(FilterLiterature)
  SC_AGENT_UNREGISTER(FilterPainting)
  SC_AGENT_UNREGISTER(ObjectCoordinatesSearchAgent)
  SC_AGENT_UNREGISTER(AllObjectCoordinatesSearchAgent)
    
  return SC_RESULT_OK;
}
