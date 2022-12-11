#include <sc-agents-common/utils/GenerationUtils.hpp>
#include <sc-agents-common/utils/AgentUtils.hpp>
#include <sc-agents-common/utils/IteratorUtils.hpp>
#include <iostream>

#include "ObjectCoordinatesSearchAgent.hpp"

using namespace std;
using namespace utils;

namespace exampleModule
{

SC_AGENT_IMPLEMENTATION(ObjectCoordinatesSearchAgent)
{
  if (!edgeAddr.IsValid())
    return SC_RESULT_ERROR;

  ScAddr questionNode = ms_context->GetEdgeTarget(edgeAddr);
  ScAddr param = IteratorUtils::getFirstFromSet(ms_context.get(), questionNode);
  if (!param.IsValid())
    return SC_RESULT_ERROR_INVALID_PARAMS;

  ScAddr answer = ms_context->CreateNode(ScType::NodeConstStruct);
  
  ScIterator5Ptr iterator5 = IteratorUtils::getIterator5(ms_context.get(), param, Keynodes::nrel_geographical_location, false);
  ScAddr sheaf;
  if (iterator5->Next())
  {
    sheaf = iterator5->Get(0);
    ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, sheaf);


  
    ScIterator5Ptr iter5_1 = IteratorUtils::getIterator5(ms_context.get(), sheaf, Keynodes::rrel_longitude, false);
    iter5_1->Next();

    ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, iter5_1->Get(0));
    ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, iter5_1->Get(1));
    ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, iter5_1->Get(3));
    ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, iter5_1->Get(4));

    ScIterator5Ptr iter5_2 = IteratorUtils::getIterator5(ms_context.get(), sheaf, Keynodes::rrel_latitude, false);
    iter5_2->Next();

    ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, iter5_2->Get(0));
    ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, iter5_2->Get(1));
    ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, iter5_2->Get(3));
    ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, iter5_2->Get(4));

    //GenerationUtils::addSetToOutline(ms_context.get(), sheaf, answer);
  }
  else
  {
    return SC_RESULT_ERROR_INVALID_PARAMS;
  }
       
  AgentUtils::finishAgentWork(ms_context.get(), questionNode, answer);
  return SC_RESULT_OK;
}
}
