/*
* This source file is part of an OSTIS project. For the latest info, see http://ostis.net
* Distributed under the MIT License
* (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
*/

#include <sc-agents-common/utils/GenerationUtils.hpp>
#include <sc-agents-common/utils/AgentUtils.hpp>
#include <sc-agents-common/utils/IteratorUtils.hpp>
#include <sc-agents-common/utils/CommonUtils.hpp>

#include "FilterPainting.hpp"

using namespace std;
using namespace utils;

namespace exampleModule
{

SC_AGENT_IMPLEMENTATION(FilterPainting)
{
  if (!edgeAddr.IsValid())
    {
    return SC_RESULT_ERROR;
    }
  ScAddr questionNode = ms_context->GetEdgeTarget(edgeAddr);
  ScAddr param = IteratorUtils::getFirstFromSet(ms_context.get(), questionNode);
  if (!param.IsValid())
  {
    return SC_RESULT_ERROR_INVALID_PARAMS;
  }
  ScAddr answer = ms_context->CreateNode(ScType::NodeConstStruct);
  ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, param);
  ScAddr rrel = ms_context->HelperFindBySystemIdtf("rrel_maximum_studied_object_class");
  ScAddr begin = ms_context->HelperFindBySystemIdtf("subject_domain_of_painting");
  ScIterator3Ptr it3 = ms_context->Iterator3(param, ScType::EdgeAccessConstPosPerm, ScType::Unknown);
  while (it3->Next())
  { 
    SC_LOG_ERROR(ms_context->HelperGetSystemIdtf(it3->Get(2)));
    ScIterator5Ptr it5 = ms_context->Iterator5(begin, ScType::Unknown, it3->Get(2), ScType::Unknown, rrel);
    if (it5->Next()){
       ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, it3->Get(2));
       ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, questionNode, it3->Get(2));
    }
  }

  AgentUtils::finishAgentWork(ms_context.get(), questionNode, answer);
  return SC_RESULT_OK;
}
}
