/*
* This source file is part of an OSTIS project. For the latest info, see http://ostis.net
* Distributed under the MIT License
* (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
*/

#include <iostream>

#include <sc-memory/sc_memory.hpp>
#include <sc-memory/sc_stream.hpp>
#include <sc-memory/sc_template_search.cpp>

#include <sc-agents-common/utils/GenerationUtils.hpp>
#include <sc-agents-common/utils/AgentUtils.hpp>
#include <sc-agents-common/utils/IteratorUtils.hpp>
#include <sc-agents-common/utils/CommonUtils.hpp>

#include "FindBestWayAgent.hpp"

using namespace std;
using namespace utils;

namespace exampleModule
{

  ScAddr findSmaller(ScLog *logger, std::unique_ptr<ScMemoryContext> &ms_context, ScAddr first, ScAddr set){
	  float length = 100000;
    ScAddr answer = first;
    ScIterator5Ptr iter = ms_context->Iterator5(first, ScType::EdgeDCommonConst, ScType::NodeConst, ScType::EdgeAccessConstPosPerm, ScType::Link);
    while(iter->Next()){
      if(iter->Get(2).IsValid()){
        string lengthBetween = CommonUtils::getLinkContent(ms_context.get(), iter->Get(4));
        if (length >= stof(lengthBetween)){
          length = stof(lengthBetween);
          ScAddr answer = iter->Get(2);
        }                 
      }
    }

    ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, first, answer);  
    return answer;
  }

  SC_AGENT_IMPLEMENTATION(FindBestWayAgent)
  { 
    SC_LOG_ERROR("FindBestWayAgent started");
    ScLog *logger = ScLog::GetInstance();

    if (!edgeAddr.IsValid())
      return SC_RESULT_ERROR;
    
    ScAddr questionNode = ms_context->GetEdgeTarget(edgeAddr);
    ScAddr set = Keynodes::in_way;
    
    ScAddr node  = IteratorUtils::getFirstFromSet(ms_context.get(), questionNode);
      if (!node.IsValid())
      {
        SC_LOG_ERROR("Arg not found");
        return SC_RESULT_ERROR_INVALID_PARAMS; 
      }

    ScTemplate scTemplate;
    string toDelete = "_to_delete";
    scTemplate.Triple(
      node,
      ScType::EdgeAccessVarPosPerm >> toDelete,
      set
    );
    ScTemplateSearchResult searchResult;
    ms_context->HelperSearchTemplate(scTemplate, searchResult);
    if (!searchResult.IsEmpty())
      ms_context->EraseElement(searchResult[0][toDelete]);

    
    while (set.IsValid()){  
      ScAddr answer = findSmaller(logger, ms_context, node, set);
      node = answer;

      ScTemplate scTemplate;
      string toDelete = "_to_delete";
      scTemplate.Triple(
        node,
        ScType::EdgeAccessVarPosPerm >> toDelete,
        set
      );
      ScTemplateSearchResult searchResult;
      ms_context->HelperSearchTemplate(scTemplate, searchResult);
      if (!searchResult.IsEmpty())
        ms_context->EraseElement(searchResult[0][toDelete]);
    }

    utils::AgentUtils::finishAgentWork(ms_context.get(), questionNode);
    return SC_RESULT_OK;
  }
}
