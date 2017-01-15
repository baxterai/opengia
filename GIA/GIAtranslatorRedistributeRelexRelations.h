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
 * File Name: GIAtranslatorRedistributeRelexRelations.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2013 Baxter AI (baxterai.com)
 * Project: General Intelligence Algorithm
 * Project Version: 1t1d 15-July-2013
 * Requirements: requires text parsed by NLP Parser (eg Relex; available in .CFF format <relations>)
 * Description: Converts relation objects into GIA network nodes (of type entity, action, condition etc) in GIA network/tree
 *
 *******************************************************************************/


#ifndef HEADER_GIA_TRANSLATOR_REDISTRIBUTE_RELEX_RELATIONS
#define HEADER_GIA_TRANSLATOR_REDISTRIBUTE_RELEX_RELATIONS

#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>
#include <cstdlib>	//for random number generation
#include <cmath>
#include <string>
#include <vector>
using namespace std;

#include "GIAglobalDefs.h"
#include "GIAsentenceClass.h"
#include "GIAentityNodeClass.h"
#include "GIAentityConnectionClass.h"
#include "GIAconditionNodeClass.h"

//should move the following to GIAtranslatorRedistributeRelations.h/.cpp
#ifdef GIA_TRANSLATOR_CORRECT_IRREGULAR_VERB_LEMMAS
bool detectContinuousVerbBasic(string * verb);
void redistributeStanfordAndRelexRelationsCorrectPOStagsAndLemmasOfAllContinuousVerbs(Sentence * currentSentenceInList, bool GIAentityNodeArrayFilled[], GIAentityNode * GIAentityNodeArray[], Feature * featureArrayTemp[]);	//Stanford Specific? (may require Relex equivalent redistribution function)
	bool correctContinuousVerbPOStagAndLemma(GIAentityNode * actionOrSubstanceEntity, Feature * currentFeature);
		//bool determineIfWordIsVerbContinuousCase(string * word);
	
#endif

//should move the following to GIAtranslatorRedistributeRelexRelations.h/.cpp:
#ifdef GIA_SUPPORT_ALIASES_RELEX_COMPATIBILITY
void redistributeRelexRelationsCollapseSubjectAndObjectGenerateAppos(Sentence * currentSentenceInList, bool GIAentityNodeArrayFilled[], GIAentityNode * GIAentityNodeArray[], int NLPfeatureParser, Feature * featureArrayTemp[]);
#endif
#ifdef GIA_SUPPORT_WHO_QUERY_ALIAS_ANSWERS
void redistributeRelexRelationsDetectNameQueries(Sentence * currentSentenceInList, bool GIAentityNodeArrayFilled[], GIAentityNode * GIAentityNodeArray[], Feature * featureArrayTemp[]);
#endif
#ifdef GIA_TRANSLATOR_INTERPRET_OF_AS_OBJECT_FOR_CONTINUOUS_VERBS
void redistributeRelexRelationsInterpretOfAsObjectForContinuousVerbs(Sentence * currentSentenceInList, bool GIAentityNodeArrayFilled[], GIAentityNode * GIAentityNodeArray[], int NLPdependencyRelationsType);
#endif

#endif
