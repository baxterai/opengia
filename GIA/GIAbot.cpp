/*******************************************************************************
 *
 * This file is part of BAIPROJECT.
 *
 * BAIPROJECT is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * BAIPROJECT is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Affero General Public License
 * version 3 along with BAIPROJECT.  If not, see <http://www.gnu.org/licenses/>
 * for a copy of the AGPLv3 License.
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: GIAbot.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2013 Baxter AI (baxterai.com)
 * Project: General Intelligence Algorithm
 * Project Version: 1s7b 29-June-2013
 * Requirements: requires text parsed by NLP Parser (eg Relex; available in .CFF format <relations>)
 * Description: Converts relation objects into GIA nodes (of type entity, action, condition etc) in GIA network/tree
 * TO DO: replace vectors entityNodesActiveListConcepts/conceptEntityNamesList with a map, and replace vectors GIAtimeConditionNode/timeConditionNumbersActiveList with a map
 * TO DO: extract date information of entities from relex <features> tag area
 *******************************************************************************/


#include "GIAbot.h"

#ifdef GIA_BOT_SWITCH_FIRST_AND_SECOND_PERSON
void botSwitchFirstAndSecondPerson(Sentence * currentSentenceInList, bool GIAentityNodeArrayFilled[], GIAentityNode * GIAentityNodeArray[], int NLPdependencyRelationsType)
{
	Relation * currentRelationInList = currentSentenceInList->firstRelationInList;
 	while(currentRelationInList->next != NULL)
	{
		#ifdef GIA_DO_NOT_PARSE_DISABLED_RELATIONS
		if(!(currentRelationInList->disabled))
		{
		#endif
			bool passedFirstPersonGovernor = false;
			bool passedFirstPersonDependent = false;
			for(int i=0; i<FEATURE_FIRST_PERSON_NUMBER_OF_TYPES; i++)
			{
				if(currentRelationInList->relationGovernor == featureFirstPersonNameArray[i])
				{
					GIAentityNode * firstPersonEntity = GIAentityNodeArray[currentRelationInList->relationGovernorIndex];
					currentRelationInList->relationGovernor = featureSecondPersonNameArray[i];
					firstPersonEntity->entityName = featureSecondPersonNameArray[i];
					passedFirstPersonGovernor = true;
				}
				if(currentRelationInList->relationDependent == featureFirstPersonNameArray[i])
				{
					GIAentityNode * firstPersonEntity = GIAentityNodeArray[currentRelationInList->relationDependentIndex];
					currentRelationInList->relationDependent = featureSecondPersonNameArray[i];
					firstPersonEntity->entityName = featureSecondPersonNameArray[i];
					passedFirstPersonDependent = true;
				}				
			}
			for(int i=0; i<FEATURE_SECOND_PERSON_NUMBER_OF_TYPES; i++)
			{
				if(!passedFirstPersonGovernor)
				{		
					if(currentRelationInList->relationGovernor == featureSecondPersonNameArray[i])
					{
						GIAentityNode * secondPersonEntity = GIAentityNodeArray[currentRelationInList->relationGovernorIndex];
						currentRelationInList->relationGovernor = featureFirstPersonNameArray[i];
						secondPersonEntity->entityName = featureFirstPersonNameArray[i];
					}
				}
				if(!passedFirstPersonDependent)
				{
					if(currentRelationInList->relationDependent == featureSecondPersonNameArray[i])
					{
						GIAentityNode * secondPersonEntity = GIAentityNodeArray[currentRelationInList->relationDependentIndex];
						currentRelationInList->relationDependent = featureFirstPersonNameArray[i];
						secondPersonEntity->entityName = featureFirstPersonNameArray[i];
					}	
				}			
			}		
		#ifdef GIA_DO_NOT_PARSE_DISABLED_RELATIONS
		}
		#endif
		currentRelationInList = currentRelationInList->next;
	}
}
#endif