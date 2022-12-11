/*
* This source file is part of an OSTIS project. For the latest info, see http://ostis.net
* Distributed under the MIT License
* (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
*/

#include <iostream>

#include <sc-memory/sc_memory.hpp>
#include <sc-memory/sc_stream.hpp>
#include "sc-memory/sc_link.hpp"

#include <sc-agents-common/utils/IteratorUtils.hpp>
#include <sc-agents-common/utils/AgentUtils.hpp>
#include <sc-agents-common/utils/GenerationUtils.hpp>
#include <sc-agents-common/utils/CommonUtils.hpp>

#include "FindBestWayAgent.hpp"

#include <vector>

using namespace std;
using namespace utils;

namespace exampleModule
{
  tuple <ScAddr, ScAddr, ScAddr, ScAddr, float> findSmaller(std::unique_ptr<ScMemoryContext> &ms_context, ScAddr first_place, ScAddr set_path, ScAddr path, ScAddr answer){
    float length = 10000000;
    ScAddr next_place;
    ScIterator3Ptr iter1 = ms_context->Iterator3(set_path, ScType::EdgeAccessConstPosPerm, ScType::Unknown);
    while(iter1->Next())
    { 
      ScAddr place = iter1->Get(2);
      if (place != first_place)
      {
        SC_LOG_ERROR("Find next place: " + ms_context->HelperGetSystemIdtf(iter1->Get(2)));

        ScIterator5Ptr iter_link = ms_context->Iterator5(first_place, ScType::EdgeAccessConstPosPerm, place, ScType::EdgeAccessConstPosPerm, ScType::NodeConst);
        while(iter_link->Next())
        {
          ScAddr node = iter_link->Get(4);

          ScIterator5Ptr iterator5 = ms_context->Iterator5(node, ScType::EdgeDCommonConst, ScType::Link, ScType::EdgeAccessConstPosPerm, Keynodes::nrel_distance);
          while (iterator5->Next()){

            ScAddr sc_link = iterator5->Get(2);
            if(sc_link.IsValid()){
              string lengthBetween = CommonUtils::readString(ms_context.get(), sc_link);

              SC_LOG_ERROR("Find link: " + lengthBetween);
              if (stof(lengthBetween) <= length)
              {
                length = stof(lengthBetween);
                next_place = iter1->Get(2);
                SC_LOG_ERROR("WHICH PLACE SHOULD BE NEXT: " + ms_context->HelperGetSystemIdtf(iter1->Get(2)));
              }
            }
          }
        }
      } 
    }

    ScIterator3Ptr del_edge = ms_context->Iterator3(set_path, ScType::EdgeAccessConstPosPerm, next_place);
    while (del_edge->Next())
    {
      ms_context->EraseElement(del_edge->Get(1));
    }


    ScAddr edge = ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, first_place, next_place);
    ScAddr rel = ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, Keynodes::rrel_next_point, edge);


    ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, path, edge);
    ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, path, rel);


    GenerationUtils::addSetToOutline(ms_context.get(), path, answer);
    return make_tuple(path, set_path, next_place, answer, length);
  }


  SC_AGENT_IMPLEMENTATION(FindBestWayAgent)
  { 
    SC_LOG_ERROR("START MY AGENT");

    if (!edgeAddr.IsValid())
    {
      SC_LOG_ERROR("Result Error");
      return SC_RESULT_ERROR;
    }
    
    ScAddr questionNode = ms_context->GetEdgeTarget(edgeAddr);

    ScAddr node  = IteratorUtils::getFirstFromSet(ms_context.get(), questionNode);
    if (!node.IsValid())
    {
    	SC_LOG_ERROR("Arg not found");
    	return SC_RESULT_ERROR_INVALID_PARAMS; 
    }


    ScAddr answer = ms_context->CreateNode(ScType::NodeConstStruct);

    SC_LOG_ERROR("answer: "+ ms_context->HelperGetSystemIdtf(answer));

    ScAddr rrel_1 = ms_context->HelperFindBySystemIdtf("rrel_1");


    ScAddr path = ms_context->CreateNode(ScType::NodeConst);
    ScAddr c_path = ms_context->HelperFindBySystemIdtf("concept_way");
    ScAddr some_edge = ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, c_path, path);



    ScAddr set_path = ms_context->CreateNode(ScType::NodeConst);
    ScAddr first_place;

    ScIterator5Ptr iter = ms_context->Iterator5(node, ScType::EdgeAccessConstPosPerm, ScType::Unknown, ScType::EdgeAccessConstPosPerm, rrel_1);
    while(iter->Next())
    {
      SC_LOG_ERROR("Find some place: " + ms_context->HelperGetSystemIdtf(iter->Get(2)));

      ScAddr edge = ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, path, iter->Get(2));
      ScAddr rel = ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, rrel_1, edge);

      first_place = iter->Get(2);

      ScIterator3Ptr iter1 = ms_context->Iterator3(node, ScType::EdgeAccessConstPosPerm, ScType::Unknown);
      while(iter1->Next())
      { 
        ScAddr place = iter1->Get(2);
        if (place != first_place)
        {
          SC_LOG_ERROR("Find next place: " + ms_context->HelperGetSystemIdtf(iter1->Get(2)));
      
          ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, path, place);
          ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, set_path, place);
          
        } 
      }

      ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, edge);
      ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, rel);

    }
    
    ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, c_path);
    ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, some_edge);

    float all_length = 0;
    float length;
    ScAddr next_place = first_place;
    while(CommonUtils::getPowerOfSet(ms_context.get(), set_path) != 0)
    {
      tie(path, set_path, next_place, answer, length) = findSmaller(ms_context, next_place, set_path,path,answer);
      all_length += length;
    }
    
    string const result = to_string(all_length);

    ScMemoryContext ctx(sc_access_lvl_make_min, "sc_links_content_changed");
    ScAddr const linkAddr = ms_context->CreateLink();
    ScLink link(ctx, linkAddr);
    link.Set(result);
    

    ScAddr edge = ms_context->CreateEdge(ScType::EdgeDCommonConst, path, linkAddr);
    ScAddr rel = ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, Keynodes::nrel_distance, edge);


    ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, edge);
    ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, rel);


    ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, path);

    GenerationUtils::addSetToOutline(ms_context.get(), path, answer);

    utils::AgentUtils::finishAgentWork(ms_context.get(), questionNode, answer);
    SC_LOG_ERROR("Agent finished working");
    
    return SC_RESULT_OK;
  }
}
