/*******************************************************************************
 *
 * This file is part of BAIPROJECT.
 *
 * BAIPROJECT is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License version 3
 * only, as published by the Free Software Foundation. The use of
 * intermediary programs or interfaces including file i/o is considered
 * remote network interaction. This does not imply such arrangements
 * do not constitute derivative works.
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
 * File Name: GIAnlpParser.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2014 Baxter AI (baxterai.com)
 * Project: General Intelligence Algorithm
 * Project Version: 2g8a 13-September-2014
 * Requirements: requires text parsed by NLP Parser (eg Relex; available in .CFF format <relations>)
 * Description: Parses tabular subsections (Eg <relations>) of RelEx CFF/Stanford Parser File
 *
 *******************************************************************************/


#ifndef HEADER_GIA_NLP_PARSER
#define HEADER_GIA_NLP_PARSER

#include "GIAsentenceClass.h"
#include "GIAglobalDefs.h"

#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>
#include <cstdlib>	//for random number generation
#include <cmath>
#include <string>
using namespace std;

#define RELEX_DEPENDENCY_RELATION_PREPENDITION "_"

void GIATHparseStanfordParseWordsAndPOStagsText(string * POStagsText, Sentence * currentSentenceInList, int * maxNumberOfWordsInSentence, bool createFeaturesGIA2only);
	bool findReplicateRelation(Sentence * currentSentenceInList, Relation * relation);
		bool compareRelations(Relation * relation1, Relation * relation2);
	#ifdef GIA2_SUPPORT_QUERIES
	bool findString(string entityName, string stringToFind);
	#endif
	#ifdef GIA_USE_CORPUS_DATABASE
	string createSameReferenceSetRecord2(bool sameReferenceSet);
	#endif
void GIATHparseStanfordParserRelationsText(string * relationsText, Sentence * currentSentenceInList, int * maxNumberOfWordsInSentence, bool featuresNotPreviouslyFilled, bool parseGIA2file, bool NLPrelexCompatibilityMode);
	void convertStanfordRelationToRelex(Relation * currentRelationInList, Sentence * currentSentenceInList);
		string convertPrepositionToRelex2(string * preposition, bool * prepositionFound);

void GIATHparseRelexFeaturesText(string * featuresText, Sentence * currentSentenceInList, int * maxNumberOfWordsInSentence);
void GIATHparseRelexRelationsText(string * relationsText, Sentence * currentSentenceInList, int * maxNumberOfWordsInSentence, bool NLPrelexCompatibilityMode);

#ifdef GIA_OUTPUT_INTERNAL_RELATIONS_IN_RELEX_FORMAT
string generateRelexCFFfeatureTagContent(Feature * firstFeatureInList);
string generateRelexCFFrelationTagContent(Relation * firstRelationInList);
#endif


#endif
