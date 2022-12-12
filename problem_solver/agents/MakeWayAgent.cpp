/*
* This source file is part of an OSTIS project. For the latest info, see http://ostis.net
* Distributed under the MIT License
* (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
*/

#include <iostream>

#include <sc-memory/sc_memory.hpp>

#include <sc-agents-common/utils/IteratorUtils.hpp>
#include <sc-agents-common/utils/AgentUtils.hpp>
#include <sc-agents-common/utils/GenerationUtils.hpp>
#include <sc-agents-common/utils/CommonUtils.hpp>

#include "MakeWayAgent.hpp"

#include <vector>

using namespace std;
using namespace utils;

namespace exampleModule
{
 
  SC_AGENT_IMPLEMENTATION(MakeWayAgent)
  { 
    SC_LOG_ERROR("START MY AGENT");

    if (!edgeAddr.IsValid())
    {
      SC_LOG_ERROR("Result Error");
      return SC_RESULT_ERROR;
    }
    
    ScAddr questionNode = ms_context->GetEdgeTarget(edgeAddr);

    ScAddr param  = IteratorUtils::getFirstFromSet(ms_context.get(), questionNode);
    //ScAddr param = utils::IteratorUtils::getAnyByOutRelation(&m_memoryCtx, questionNode, scAgentsCommon::CoreKeynodes::rrel_1);
    if (!param.IsValid())
    {
    	SC_LOG_ERROR("Arg not found");
    	return SC_RESULT_ERROR_INVALID_PARAMS; 
    }
    
    ScAddr answer = ms_context->CreateNode(ScType::NodeConstStruct);

    ScAddr pre_answer = ms_context->CreateNode(ScType::NodeConst);
    ScAddr edge = ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, pre_answer, param);
    ScAddr rel = ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, scAgentsCommon::CoreKeynodes::rrel_1, edge);
    
    ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, rel);
    ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, scAgentsCommon::CoreKeynodes::rrel_1);

    ScIterator3Ptr iterator3 = ms_context->Iterator3(questionNode, ScType::Unknown, ScType::Unknown);
    while (iterator3->Next()){
      SC_LOG_ERROR("Find some: " + ms_context->HelperGetSystemIdtf(iterator3->Get(2)));
      ScIterator3Ptr iterator3_1 = ms_context->Iterator3(Keynodes::concept_geography_object, ScType::Unknown, iterator3->Get(2));
      while(iterator3_1->Next()){
        if (iterator3->Get(2) != param){
          SC_LOG_ERROR("Use some: " + ms_context->HelperGetSystemIdtf(iterator3->Get(2)));
          ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, pre_answer, iterator3->Get(2));
        }
      }
    }

    ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, pre_answer);
    GenerationUtils::addSetToOutline(ms_context.get(), pre_answer, answer);

    utils::AgentUtils::finishAgentWork(ms_context.get(), questionNode, answer);
    SC_LOG_ERROR("Agent finished working");
    
    return SC_RESULT_OK;
  }
}
