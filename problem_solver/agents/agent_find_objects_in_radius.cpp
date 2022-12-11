/*
* This source file is part of an OSTIS project. For the latest info, see http://ostis.net
* Distributed under the MIT License
* (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
*/

#include <sc-agents-common/utils/GenerationUtils.hpp>
#include <sc-agents-common/utils/AgentUtils.hpp>
#include <sc-agents-common/utils/IteratorUtils.hpp>
#include <sc-agents-common/utils/CommonUtils.hpp>
#include "agent_find_objects_in_radius.hpp"
#include <cmath> 

using namespace std;
using namespace utils;

namespace exampleModule
{

SC_AGENT_IMPLEMENTATION(agent_find_objects_in_radius)
{
  
  if (!edgeAddr.IsValid())
    return SC_RESULT_ERROR;

  ScAddr questionNode = ms_context->GetEdgeTarget(edgeAddr);
  ScAddr param = IteratorUtils::getFirstFromSet(ms_context.get(), questionNode);
  
  if (!param.IsValid())
    return SC_RESULT_ERROR_INVALID_PARAMS;
  ScAddr answer = ms_context->CreateNode(ScType::NodeConstStruct);
  ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, Keynodes::in_radius_now);
  
  ScIterator3Ptr result_node = ms_context->Iterator3(Keynodes::located_in_radius,ScType::EdgeAccessConstPosPerm, ScType::NodeConst);
  while(result_node->Next())
  {
    ms_context->EraseElement(result_node->Get(1));
  }
  
  ScIterator5Ptr param_radius = ms_context->Iterator5(ScType::Link, ScType::EdgeAccessConstPosPerm, 
  param, ScType::EdgeAccessConstPosPerm, ms_context->HelperFindBySystemIdtf("rrel_radius"));
  ScIterator5Ptr param_user_x = ms_context->Iterator5(ScType::Link, ScType::EdgeAccessConstPosPerm, 
  param, ScType::EdgeAccessConstPosPerm, ms_context->HelperFindBySystemIdtf("rrel_user_x"));
  ScIterator5Ptr param_user_y = ms_context->Iterator5(ScType::Link, ScType::EdgeAccessConstPosPerm, 
  param, ScType::EdgeAccessConstPosPerm, ms_context->HelperFindBySystemIdtf("rrel_user_y"));
  string radius, user_x, user_y;
  string current_object_x, current_object_y;
  param_radius->Next();
  param_user_x->Next();
  param_user_y->Next();
  if(param_radius->Get(0).IsValid())
     ScStreamConverter::StreamToString(ms_context->GetLinkContent(param_radius->Get(0)), radius);
  if(param_user_x->Get(0).IsValid())
     ScStreamConverter::StreamToString(ms_context->GetLinkContent(param_user_x->Get(0)), user_x);
  if(param_user_y->Get(0).IsValid())
     ScStreamConverter::StreamToString(ms_context->GetLinkContent(param_user_y->Get(0)), user_y);

  ScIterator3Ptr all_objects = ms_context->Iterator3(Keynodes::concept_historical_and_cultural_heritage,ScType::EdgeAccessConstPosPerm, ScType::NodeConst );
  while(all_objects->Next())
  {
    if(all_objects->Get(2).IsValid())
    {
      ScIterator5Ptr object_coordinates = ms_context->Iterator5(all_objects->Get(2), ScType::EdgeAccessConstPosPerm, 
      ScType::NodeConst, ScType::EdgeAccessConstPosPerm, ms_context->HelperFindBySystemIdtf("nrel_geographical_location"));
      object_coordinates->Next();
      ScIterator5Ptr object_x = ms_context->Iterator5(ScType::Link, ScType::EdgeAccessConstPosPerm, 
      object_coordinates->Get(2), ScType::EdgeAccessConstPosPerm, ms_context->HelperFindBySystemIdtf("rrel_decart_x"));
      object_x->Next();
      if(object_x->Get(0).IsValid())
      ScStreamConverter::StreamToString(ms_context->GetLinkContent(object_x->Get(0)), current_object_x);
      ScIterator5Ptr object_y = ms_context->Iterator5(ScType::Link, ScType::EdgeAccessConstPosPerm, 
      object_coordinates->Get(2), ScType::EdgeAccessConstPosPerm, ms_context->HelperFindBySystemIdtf("rrel_decart_y"));
      object_y->Next();
      if(object_y->Get(0).IsValid())
      ScStreamConverter::StreamToString(ms_context->GetLinkContent(object_y->Get(0)), current_object_y);
  
     if(sqrt(pow((stof(current_object_x)-stof(user_x)), 2) + pow((stof(current_object_y)-stof(user_y)), 2)) <= stof(radius))
     {
       ScAddr edge = ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, Keynodes::located_in_radius, all_objects->Get(2));
       ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, all_objects->Get(2));
       ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, edge);
     }

    }
  }
  ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, questionNode, Keynodes::located_in_radius);
  AgentUtils::finishAgentWork(ms_context.get(), questionNode, answer);
  return SC_RESULT_OK;
}
}
