#include <sc-agents-common/utils/GenerationUtils.hpp>
#include <sc-agents-common/utils/AgentUtils.hpp>
#include <sc-agents-common/utils/IteratorUtils.hpp>
#include <sc-agents-common/utils/CommonUtils.hpp>
#include <iostream>
#include <fstream>

#include "AllObjectCoordinatesSearchAgent.hpp"

using namespace std;
using namespace utils;

namespace exampleModule
{

SC_AGENT_IMPLEMENTATION(AllObjectCoordinatesSearchAgent)
{

  fstream file;
  file.open("/home/taisia/ostis-example-app/problem-solver/cxx/exampleModule/agents/coordinates.txt");
  if (file.is_open()){
    SC_LOG_ERROR("open");
  }

  if (!edgeAddr.IsValid())
    return SC_RESULT_ERROR;

  ScAddr questionNode = ms_context->GetEdgeTarget(edgeAddr);
  ScAddr param = IteratorUtils::getFirstFromSet(ms_context.get(), questionNode);
  if (!param.IsValid())
    return SC_RESULT_ERROR_INVALID_PARAMS;

  ScAddr answer = ms_context->CreateNode(ScType::NodeConstStruct);

  ScIterator3Ptr iterator3 = ms_context->Iterator3(Keynodes::concept_coordinate, ScType::EdgeAccessConstPosPerm,  ScType::Unknown);

  while (iterator3->Next()){
    ScAddr coord = iterator3->Get(2);

    ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, coord);

    string coordinate = CommonUtils::getMainIdtf(ms_context.get(), coord);

    file << coordinate << endl;

    ScIterator5Ptr iter5_1 = IteratorUtils::getIterator5(ms_context.get(), coord, Keynodes::rrel_latitude, false);
    iter5_1->Next();
    string latitude = CommonUtils::getLinkContent(ms_context.get(), iter5_1->Get(0));

    file << latitude << endl;

    ScIterator5Ptr iter5_2 = IteratorUtils::getIterator5(ms_context.get(), coord, Keynodes::rrel_longitude, false);
    iter5_2->Next();
    string longitude = CommonUtils::getLinkContent(ms_context.get(), iter5_2->Get(0));

    file << longitude << endl;
  }

  file.close();

  AgentUtils::finishAgentWork(ms_context.get(), questionNode, answer);
  return SC_RESULT_OK;
}
}
