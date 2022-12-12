/*
* This source file is part of an OSTIS project. For the latest info, see http://ostis.net
* Distributed under the MIT License
* (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
*/

#pragma once

#include <sc-memory/sc_object.hpp>
#include <sc-memory/sc_addr.hpp>

#include "keynodes.generated.hpp"

namespace exampleModule
{

class Keynodes : public ScObject
{
  SC_CLASS()
  SC_GENERATED_BODY()

public:

  SC_PROPERTY(Keynode("question_find_subdividing"), ForceCreate)
  static ScAddr question_find_subdividing;

  SC_PROPERTY(Keynode("nrel_subdividing"), ForceCreate)
  static ScAddr nrel_subdividing;

  SC_PROPERTY(Keynode("question_find_isomorphic_structures"), ForceCreate)
  static ScAddr question_find_isomorphic_structures;
  
  SC_PROPERTY(Keynode("question_find_best_way"), ForceCreate)
  static ScAddr question_find_best_way;
  
  SC_PROPERTY(Keynode("question_make_way"), ForceCreate)
  static ScAddr question_make_way;
  
  SC_PROPERTY(Keynode("in_way"), ForceCreate)
  static ScAddr in_way;

  SC_PROPERTY(Keynode("nrel_distance"), ForceCreate)
  static ScAddr nrel_distance;
  
  SC_PROPERTY(Keynode("concept_geography_object"), ForceCreate)
  static ScAddr concept_geography_object;
  
  SC_PROPERTY(Keynode("rrel_next_point"), ForceCreate)
  static ScAddr rrel_next_point;
  
  SC_PROPERTY(Keynode("question_find_objects_in_radius"), ForceCreate)
  static ScAddr question_find_objects_in_radius;
 
  SC_PROPERTY(Keynode("located_in_radius"), ForceCreate)
  static ScAddr located_in_radius;
  
  SC_PROPERTY(Keynode("concept_historical_and_cultural_heritage"), ForceCreate)
  static ScAddr concept_historical_and_cultural_heritage;
  
  SC_PROPERTY(Keynode("question_find_all_object_coordinate"), ForceCreate)
  static ScAddr question_find_all_object_coordinate;

  SC_PROPERTY(Keynode("question_find_object_coordinate"), ForceCreate)
  static ScAddr question_find_object_coordinate;

  SC_PROPERTY(Keynode("rrel_latitude"), ForceCreate)
  static ScAddr rrel_latitude;

  SC_PROPERTY(Keynode("rrel_longitude"), ForceCreate)
  static ScAddr rrel_longitude;

  SC_PROPERTY(Keynode("concept_coordinate"), ForceCreate)
  static ScAddr concept_coordinate;
  
  SC_PROPERTY(Keynode("question_filter_by"), ForceCreate)
  static ScAddr question_filter_by;

  SC_PROPERTY(Keynode("question_monumental_filter"), ForceCreate)
  static ScAddr question_monumental_filter;

  SC_PROPERTY(Keynode("question_literature_filter"), ForceCreate)
  static ScAddr question_literature_filter;

  SC_PROPERTY(Keynode("question_painting_filter"), ForceCreate)
  static ScAddr question_painting_filter;
};

} // namespace exampleModule
