/*******************************************************************************
 *
 * This file is part of BAIPROJECT.
 *
 * BAIPROJECT is licensed under the GNU Affero General Public License
 * version 3, as published by the Free Software Foundation. The use of
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
 * File Name: GIAnlg.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2017 Baxter AI (baxterai.com)
 * Project: General Intelligence Algorithm
 * Project Version: 3d3c 17-July-2017
 * Requirements: requires GIA translated data, and NLG2 to be installed
 * Description: GIA natural language generation (using NLG2)
 *
 *******************************************************************************/


#ifndef HEADER_GIA_NLG
#define HEADER_GIA_NLG

#include "GIAglobalDefs.hpp"
#include "GIAentityNodeClass.hpp"
#include "GIAtranslatorOperations.hpp"
#include "GIAtranslatorDefineGrammar.hpp"

class GIANLGentity
{
public:

	GIANLGentity(void);
	~GIANLGentity(void);

	string entityGrammatisedText;

	GIANLGentity* next;
};

//#define GIA_NLG_EXPECT_TRANSLATOR_QUERY_ACTION_AND_CONDITION_SAME_REFERENCE_SET_ASSIGNMENT_BUG_FIXED

#define GIA_NLG_POSSESSIVE_ADVANCED
#ifdef GIA_NLG_POSSESSIVE_ADVANCED
	#define GIA_NLG_POSSESSIVE_ADVANCED_ENTITY_POSSESSIVEENDING_TYPE_DEPENDENT_ON_PROPERNOUNS
	#define GIA_NLG_POSSESSIVE_ADVANCED_ENTITY_POSSESSIVEENDING_TYPE_DETERMINER_CHARACTER 's'
#endif

#define GIA_NLG_REPRESENT_WHO_WHAT_QUERIES_ADVANCED

#define GIA_NLG_GENERATE_LANGUAGE_MAX_NUM_ITERATIONS (2)	//takes into account connections (/2)

#define GIA_NLG_RELATIONSHIP_ENTITY_CONJUNCTION_AND_IMPLICIT ", "
#define GIA_NLG_RELATIONSHIP_ENTITY_CONJUNCTION_AND "and "

#define GIA_NLG_RELATIONSHIP_ENTITY_AUXILIARY_TYPE_PROPERTY_SUBSTANCE (RELATION_ENTITY_HAVE)
#define GIA_NLG_RELATIONSHIP_ENTITY_AUXILIARY_TYPE_PROPERTY_QUALITY (RELATION_ENTITY_BE)
#define GIA_NLG_RELATIONSHIP_ENTITY_AUXILIARY_TYPE_DEFINITION (RELATION_ENTITY_BE)
#define GIA_NLG_RELATIONSHIP_ENTITY_AUXILIARY_TYPE_CONDITION (RELATION_ENTITY_BE)

//basic tense generation (no tense modifiers as yet; eg GRAMMATICAL_TENSE_MODIFIER_PROGRESSIVE)
#define GIA_NLG_RELATIONSHIP_ENTITY_AUXILIARY_BE_SINGULAR_PRESENT "is "
#define GIA_NLG_RELATIONSHIP_ENTITY_AUXILIARY_BE_SINGULAR_PAST "was "
#define GIA_NLG_RELATIONSHIP_ENTITY_AUXILIARY_BE_SINGULAR_FUTURE "will be "
#define GIA_NLG_RELATIONSHIP_ENTITY_AUXILIARY_BE_PLURAL_PRESENT "are "
#define GIA_NLG_RELATIONSHIP_ENTITY_AUXILIARY_BE_PLURAL_PAST "were "
#define GIA_NLG_RELATIONSHIP_ENTITY_AUXILIARY_BE_PLURAL_FUTURE "will be "

#define GIA_NLG_RELATIONSHIP_ENTITY_AUXILIARY_HAVE_SINGULAR_PRESENT "has "
#define GIA_NLG_RELATIONSHIP_ENTITY_AUXILIARY_HAVE_SINGULAR_PAST "had "
#define GIA_NLG_RELATIONSHIP_ENTITY_AUXILIARY_HAVE_SINGULAR_FUTURE "will have "
#define GIA_NLG_RELATIONSHIP_ENTITY_AUXILIARY_HAVE_PLURAL_PRESENT "have "
#define GIA_NLG_RELATIONSHIP_ENTITY_AUXILIARY_HAVE_PLURAL_PAST "had "
#define GIA_NLG_RELATIONSHIP_ENTITY_AUXILIARY_HAVE_PLURAL_FUTURE "will have "

static string entityRelationshipTenseNumerosityCrossReferenceBeAuxiliaryArray[GRAMMATICAL_TENSE_NUMBER_OF_TYPES][GRAMMATICAL_NUMBER_NUMBER_OF_TYPES] = {{"", "", GIA_NLG_RELATIONSHIP_ENTITY_AUXILIARY_BE_SINGULAR_PRESENT, GIA_NLG_RELATIONSHIP_ENTITY_AUXILIARY_BE_PLURAL_PRESENT}, {"", "", GIA_NLG_RELATIONSHIP_ENTITY_AUXILIARY_BE_SINGULAR_PRESENT, GIA_NLG_RELATIONSHIP_ENTITY_AUXILIARY_BE_PLURAL_PRESENT}, {"", "", GIA_NLG_RELATIONSHIP_ENTITY_AUXILIARY_BE_SINGULAR_PAST, GIA_NLG_RELATIONSHIP_ENTITY_AUXILIARY_BE_PLURAL_PAST}, {"", "", GIA_NLG_RELATIONSHIP_ENTITY_AUXILIARY_BE_SINGULAR_FUTURE, GIA_NLG_RELATIONSHIP_ENTITY_AUXILIARY_BE_PLURAL_FUTURE}};
static string entityRelationshipTenseNumerosityCrossReferenceHaveAuxiliaryArray[GRAMMATICAL_TENSE_NUMBER_OF_TYPES][GRAMMATICAL_NUMBER_NUMBER_OF_TYPES] = {{"", "", GIA_NLG_RELATIONSHIP_ENTITY_AUXILIARY_HAVE_SINGULAR_PRESENT, GIA_NLG_RELATIONSHIP_ENTITY_AUXILIARY_HAVE_PLURAL_PRESENT}, {"", "", GIA_NLG_RELATIONSHIP_ENTITY_AUXILIARY_HAVE_SINGULAR_PRESENT, GIA_NLG_RELATIONSHIP_ENTITY_AUXILIARY_HAVE_PLURAL_PRESENT}, {"", "", GIA_NLG_RELATIONSHIP_ENTITY_AUXILIARY_HAVE_SINGULAR_PAST, GIA_NLG_RELATIONSHIP_ENTITY_AUXILIARY_HAVE_PLURAL_PAST}, {"", "", GIA_NLG_RELATIONSHIP_ENTITY_AUXILIARY_HAVE_SINGULAR_FUTURE, GIA_NLG_RELATIONSHIP_ENTITY_AUXILIARY_HAVE_PLURAL_FUTURE}};

static bool entityVectorConnectionGoToParentArray[GIA_ENTITY_NUMBER_OF_VECTOR_CONNECTION_TYPES] = {false, true, false, true, false, true, false, false, true, false, false, false};
static bool entityVectorConnectionGoToChildArray[GIA_ENTITY_NUMBER_OF_VECTOR_CONNECTION_TYPES] = {true, false, true, false, true, false, false, false, false, true, false, false};


#define GIA_ENTITY_RELATIONSHIP_CONDITION_QUERY_NUMBER_OF_TYPES (4)
static string entityRelationshipConditionQueryArray[GIA_ENTITY_RELATIONSHIP_CONDITION_QUERY_NUMBER_OF_TYPES] = {"_%how", "_%attime", "_%atlocation", "_%because"};	//this needs to map to condition names in redistributeStanfordRelationsCreateQueryVarsHowWhenWhereWhy (note they are lowercase as NLP will convert uppercase words to lowercase in lemma)
static string entityRelationshipConditionQueryCrossReferenceConditionArray[GIA_ENTITY_RELATIONSHIP_CONDITION_QUERY_NUMBER_OF_TYPES] = {"how", "at", "at", "because"};

								
#define GIA_NLG_RELATIONSHIP_ENTITY_AUXILIARY_ACTION_PRESENT_APPEND "s"
//#define GIA_NLG_RELATIONSHIP_ENTITY_AUXILIARY_ACTION_PAST "did"

#define GIA_NLG_MORPH_PLURALITY_APPEND "s"
#define GIA_NLG_REFERENCE_SET_RCMOD_SAME_REFERENCE_SET "that "	//"which "
#define GIA_NLG_RELATIONSHIP_ENTITY_ACTION_REVERSE "by "

#define GIA_NLG_SUPPORT_PERSON_AND_GENDER
#define GIA_NLG_SUPPORT_TIME_CONDITIONS	//CHECKTHIS
#define GIA_NLG_TEXT_SPACE (STRING_SPACE)

#define NLG_NUMBER_OF_VOWELS (5)
static char vowelArray[NLG_NUMBER_OF_VOWELS] = {'a','e','i','o','u'};

class GIAnlgClass
{
	private: SHAREDvarsClass SHAREDvars;
	private: GIAentityNodeClassClass GIAentityNodeClass;
	private: GIAtranslatorOperationsClass GIAtranslatorOperations;
	
	#ifdef GIA_NLG
	public: string generateLanguageFromQuery(GIAentityNode* comparisonVariableNode, GIAentityNode* queryAnswerNode);
	//public: string generateLanguageFromWhichQuery(GIAentityNode* comparisonVariableNode, GIAentityNode* queryAnswerNode);
		private: string generateLanguageFromNLGentityList(GIANLGentity* firstNLGentityInContext);		
		private: bool generateLanguageFromTextIteration(GIAentityConnection* currentConnection, GIANLGentity** currentNLGentity, const bool parseSameReferenceSetOnly, const int interationIndex, const bool isRelationshipReverseIterationAction=false, const bool isRelationshipReverseIterationProperty=false, const bool isRelationshipReverseIterationPropertyPossessive=false);
			private: bool generateLanguageFromTextIterationPerformChecks(GIAentityConnection* connection, const bool parseQualities=false);
			private: bool generateRelationshipEntityLanguage(GIAentityConnection* relationshipConnection, GIANLGentity** currentNLGentity, const bool sameReferenceSet, bool addAuxiliaryToQualities=false, bool addRCmodToProperties=true);
			private: bool generateRelationshipEntityLanguageActionReverse(GIAentityConnection* relationshipConnection, GIANLGentity** currentNLGentity, const bool sameReferenceSet);
				private: bool compareRelationshipConnectionType(GIAentityConnection* relationshipConnection, const int entityType);
				private: string generateMorphologyAction(GIAentityConnection* relationshipConnection);
				private: string generateMorphologyActionReverse(GIAentityConnection* relationshipConnection);
				private: string generateMorphologyCondition(GIAentityConnection* relationshipConnection);
				private: string generateMorphologyRelationshipAuxiliaryBe(GIAentityConnection* relationshipConnection);
				private: string generateMorphologyRelationshipAuxiliaryHave(GIAentityConnection* relationshipConnection);
			private: bool generateNounEntityLanguage(GIAentityNode* nounEntity, GIANLGentity** currentNLGentity, const bool definite, const bool parseSameReferenceSetOnly, const bool possessive=false, const bool determiner=true);
				private: string calcDeterminate(GIAentityNode* entityNode, const bool definite);
				private: bool generateQualityPrependText(GIAentityNode* currentEntity, GIANLGentity** currentNLGentityInSection, const bool testSameReferenceSet, const bool generateNewNLGentities);
					private: bool generateConjunctionOfNLGentitiesInSection(const int qualityCountMax, vector<GIANLGentity*>* NLGentitiesInSection);
					//private: bool generateConjunctionOfNLGentitiesInSection(int qualityCountMax, GIANLGentity* firstNLGentityInSection);
				private: string calcNounWord(GIAentityNode* entityNode, const bool possessive);

	private: string generatePlurality(const string entityName, int grammaticalNumber);

	#endif

};



#endif
