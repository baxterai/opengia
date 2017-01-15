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
 * File Name: GIAtranslatorDefineReferencing.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2016 Baxter AI (baxterai.com)
 * Project: General Intelligence Algorithm
 * Project Version: 2o5b 21-October-2016
 * Requirements: requires text parsed by NLP Parser (eg Relex; available in .CFF format <relations>)
 * Description: Converts relation objects into GIA nodes (of type entity, action, condition etc) in GIA network/tree
 *
 *******************************************************************************/


#include "GIAtranslatorDefineReferencing.h"
#include "GIAdatabase.h"

//unordered_map<string, GIAentityNode*>* entityNodesActiveListNetworkIndexes
void identifyComparisonVariableAlternateMethod(GIAsentence* currentSentenceInList, bool GIAentityNodeArrayFilled[], GIAentityNode* GIAentityNodeArray[], int NLPfeatureParser)
{
	bool expectToFindComparisonVariable = false;
	if(currentSentenceInList->isQuestion)
	{
		expectToFindComparisonVariable = true;
		#ifdef GIA_TRANSLATOR_DEBUG
		//cout << "expectToFindComparisonVariable" << endl;
		#endif
	}

	if(expectToFindComparisonVariable)
	{
		#ifdef GIA_REDISTRIBUTE_STANFORD_RELATIONS_QUERY_VARIABLE_DEBUG_DO_NOT_MAKE_FINAL_CHANGES_YET
		if(NLPfeatureParser != GIA_NLP_PARSER_RELEX)	//ie if(NLPfeatureParser == GIA_NLP_PARSER_STANFORD_CORENLP)
		{
		#endif
			for(int i=0; i<MAX_NUMBER_OF_WORDS_PER_SENTENCE; i++)
			{
				if(GIAentityNodeArrayFilled[i])
				{
					GIAentityNode* entityNode = GIAentityNodeArray[i];
					if(entityNode->entityName == REFERENCE_TYPE_QUESTION_COMPARISON_VARIABLE)
					{
						entityNode->isQuery = true;
						setComparisonVariableNode(entityNode);
						setFoundComparisonVariable(true);
						#ifdef GIA_TRANSLATOR_DEBUG
						cout << "foundComparisonVariable" << endl;
						#endif
					}
				}
			}
		#ifdef GIA_REDISTRIBUTE_STANFORD_RELATIONS_QUERY_VARIABLE_DEBUG_DO_NOT_MAKE_FINAL_CHANGES_YET
		}
		#endif
		#ifdef GIA_SUPPORT_COMPARISON_VARIABLE_DEFINITION_VIA_ALTERNATE_METHOD_EG_SUPPORT_WHICH_QUERIES
		if(!getFoundComparisonVariable())
		{//define comparison variable; define required answer entity as the next noun after the question word/lemma eg "house/person"

			bool foundComparisonVariableAlternateMethod = false;

			bool foundQueryWordAcceptedByAlternateMethod = false;
			GIAfeature* currentFeatureInList = currentSentenceInList->firstFeatureInList;
			while(currentFeatureInList->next != NULL)
			{
				bool passed = false;
				for(int i=0; i<FEATURE_QUERY_WORD_ACCEPTED_BY_ALTERNATE_METHOD_NUMBER_OF_TYPES; i++)
				{
					/*
					//Not required because FEATURE_POS_TAG_WH_DETERMINER_WDT/FEATURE_RELEX_POS_TYPE_ADJECTIVE_NAME ensures that the correct which or what equivalent query is being asked:
					bool passedDependencyRelationCheck = false;
					if(NLPfeatureParser == GIA_NLP_PARSER_RELEX)
					{
						passedDependencyRelationCheck = true;
					}
					else
					{//ie if(NLPfeatureParser == GIA_NLP_PARSER_STANFORD_CORENLP)
						GIArelation* currentRelationInList = currentSentenceInList->firstRelationInList;
						while(currentRelationInList->next != NULL)
						{
							if(currentRelationInList->relationType == RELATION_TYPE_DETERMINER)	//only supported by Stanford
							{
								if(currentRelationInList->relationDependent == featureQueryWordAcceptedByAlternateMethodNameArray[i])
								{
									passedDependencyRelationCheck = true;
								}
							}
							currentRelationInList = currentRelationInList->next;
						}
					}

					if(passedDependencyRelationCheck)
					{
					*/
						#ifdef GIA_TRANSLATOR_DEBUG
						/*
						cout << "currentFeatureInList->word = " << currentFeatureInList->word << endl;
						cout << "currentFeatureInList->lemma = " << currentFeatureInList->lemma << endl;
						cout << "currentFeatureInList->type = " << currentFeatureInList->type << endl;
						cout << "currentFeatureInList->grammar = " << currentFeatureInList->grammar << endl;
						*/
						#endif

						#ifndef GIA_REDISTRIBUTE_STANFORD_RELATIONS_QUERY_VARIABLE_DEBUG_DO_NOT_MAKE_FINAL_CHANGES_YET
						if(NLPfeatureParser == GIA_NLP_PARSER_RELEX)
						{
						#endif
							if((currentFeatureInList->word == featureQueryWordAcceptedByAlternateMethodNameArray[i]) && (currentFeatureInList->lemma == featureQueryWordAcceptedByAlternateMethodNameArray[i]) && (currentFeatureInList->type == FEATURE_RELEX_POS_TYPE_ADJECTIVE_NAME) && (currentFeatureInList->grammar == featureQueryWordAcceptedByAlternateMethodNameArray[i]))
							{//eg 1	which	which	adj	which
								#ifdef GIA_TRANSLATOR_DEBUG
								//cout << "foundQueryWordAcceptedByAlternateMethod" << endl;
								#endif
								foundQueryWordAcceptedByAlternateMethod = true;
							}
						#ifndef GIA_REDISTRIBUTE_STANFORD_RELATIONS_QUERY_VARIABLE_DEBUG_DO_NOT_MAKE_FINAL_CHANGES_YET
						}
						else if(NLPfeatureParser == GIA_NLP_PARSER_STANFORD_CORENLP)
						{
							//cannot check the word value here, as the word recorded by the Stanford parser may be capitalised
							if((currentFeatureInList->lemma == featureQueryWordAcceptedByAlternateMethodNameArray[i]) && (currentFeatureInList->stanfordPOS == FEATURE_POS_TAG_WH_DETERMINER_WDT))
							{//eg lemma=which, POS=WHT
								#ifdef GIA_TRANSLATOR_DEBUG
								//cout << "foundQueryWordAcceptedByAlternateMethod" << endl;
								#endif
								foundQueryWordAcceptedByAlternateMethod = true;
							}
						}
						#endif
					/*
					}
					*/

				}
				if(foundQueryWordAcceptedByAlternateMethod)
				{
					//NB For relex the designation of query variable in the special case "What [time] is it?" is now handled by redistributeRelexRelationsCollapseSubjectAndObjectGenerateAppos - as of 3 July 2013 - it used to be handled here

					bool nounFound = false;	//finds the first noun after "which"[/"what"]
					#ifndef GIA_REDISTRIBUTE_STANFORD_RELATIONS_QUERY_VARIABLE_DEBUG_DO_NOT_MAKE_FINAL_CHANGES_YET
					if(currentFeatureInList->grammaticalWordType == GRAMMATICAL_WORD_TYPE_NOUN)
					{
						nounFound = true;
					}
					#else
					if(currentFeatureInList->type == FEATURE_RELEX_POS_TYPE_NOUN_NAME)
					{
						nounFound = true;
					}
					#endif
					if(nounFound && !foundComparisonVariableAlternateMethod)
					{
						foundComparisonVariableAlternateMethod = true;
						#ifdef GIA_TRANSLATOR_DEBUG
						//cout << "(nounFound && !foundComparisonVariableAlternateMethod): set foundQueryWordAcceptedByAlternateMethod" << endl;
						#endif
						/*
						string queryComparisonVariableName = currentFeatureInList->word
						bool entityAlreadyExistant = false;
						GIAentityNode* queryComparisonVariableEntityNode = findOrAddNetworkIndexEntityNodeByNameSimpleWrapper(&queryComparisonVariableName, &entityAlreadyExistant);
						//CHECK THIS; !applyNetworkIndexEntityAlreadyExistsFunction
						*/
						if(GIAentityNodeArrayFilled[currentFeatureInList->entityIndex])
						{
							GIAentityNode* queryComparisonVariableEntityNode = GIAentityNodeArray[currentFeatureInList->entityIndex];
							queryComparisonVariableEntityNode->isQuery = true;
							queryComparisonVariableEntityNode->isWhichOrEquivalentWhatQuery = true;
							#ifdef GIA_SUPPORT_WHICH_QUERY_ALIAS_ANSWERS
							queryComparisonVariableEntityNode->isNameQuery = true;
							#endif
							setFoundComparisonVariable(true);
							setComparisonVariableNode(queryComparisonVariableEntityNode);
							#ifdef GIA_TRANSLATOR_DEBUG
							cout << "foundComparisonVariable" << endl;
							cout << "queryComparisonVariableEntityNode->entityName = " << queryComparisonVariableEntityNode->entityName << endl;
							#endif
						}
						else
						{
							cout << "error: !GIAentityNodeArrayFilled[indexOfAlternateComparisonVariableEntityNode]" << endl;
						}
					}
				}

				currentFeatureInList = currentFeatureInList->next;
			}
		}
		#endif
	}
	/*
	else
	{
		if(foundComparisonVariableTemp)
		{
			cout << "error: expectToFindComparisonVariable && foundComparisonVariable" << endl;
			exit(0);
		}
	}
	*/
}



void identifyEntityTypes(GIAsentence* currentSentenceInList, GIAentityNode* GIAentityNodeArray[], int NLPdependencyRelationsType)
{
	GIArelation* currentRelationInList = currentSentenceInList->firstRelationInList;
	while(currentRelationInList->next != NULL)
	{
		#ifdef GIA_DO_NOT_PARSE_DISABLED_RELATIONS_OLD
		if(!(currentRelationInList->disabled))
		{
		#endif
			//possessive of substances [NB plural/singular indicates definite noun - eg a robin, the robin, the robins - which is therefore a substance (entity instance):

			//possessive of substances:

			bool passed = false;
			for(int i=0; i<RELATION_TYPE_POSSESSIVE_NUMBER_OF_TYPES; i++)
			{
				if(currentRelationInList->relationType == relationTypePossessiveNameArray[i])
				{
					passed = true;
				}
			}
			//if(currentRelationInList->relationType == RELATION_TYPE_POSSESSIVE)
			#ifndef GIA_TRANSLATOR_INTERPRET_PRENOMINAL_MODIFIER_PROPERTIES_TAKE_DEPENDENT_AS_PROPERTY_INSTEAD_OF_GOVERNOR
			for(int i=0; i<RELATION_TYPE_PRENOMINAL_MODIFIER_NUMBER_OF_TYPES; i++)
			{
				if(currentRelationInList->relationType == relationTypePrenominalModifierNameArray[i])
				{
					passed = true;
				}
			}
			#endif
			if(passed)
			{
				int relationGovernorIndex = currentRelationInList->relationGovernorIndex;
				int relationDependentIndex = currentRelationInList->relationDependentIndex;
				GIAentityNode* substanceEntity = GIAentityNodeArray[relationGovernorIndex];
				GIAentityNode* ownerEntity = GIAentityNodeArray[relationDependentIndex];
				ownerEntity->hasSubstanceTemp = true;
			}

			//possessive of substances:

			passed = false;
			for(int i=0; i<RELATION_TYPE_ADJECTIVE_NUMBER_OF_TYPES; i++)
			{
				if(currentRelationInList->relationType == relationTypeAdjectiveNameArray[i])
				{
					passed = true;
				}
			}
			#ifdef GIA_TRANSLATOR_INTERPRET_PRENOMINAL_MODIFIER_PROPERTIES_TAKE_DEPENDENT_AS_PROPERTY_INSTEAD_OF_GOVERNOR
			for(int i=0; i<RELATION_TYPE_PRENOMINAL_MODIFIER_NUMBER_OF_TYPES; i++)
			{
				if(currentRelationInList->relationType == relationTypePrenominalModifierNameArray[i])
				{
					passed = true;
				}
			}
			#endif
			//if((currentRelationInList->relationType == RELATION_TYPE_ADJECTIVE_AMOD) || (currentRelationInList->relationType == RELATION_TYPE_ADJECTIVE_PREDADJ) || (currentRelationInList->relationType == RELATION_TYPE_ADJECTIVE_ADVMOD))
			if(passed)
			{
				#ifndef GIA_USE_GENERIC_DEPENDENCY_RELATION_INTERPRETATION_REDISTRIBUTION
				bool passed2 = true;
				#ifdef GIA_STANFORD_DO_NOT_USE_UNTESTED_RELEX_OPTIMISATION_CODE_THAT_IS_PROBABLY_STANFORD_COMPATIBLE
				if(NLPdependencyRelationsType == GIA_DEPENDENCY_RELATIONS_TYPE_RELEX)
				{
				#endif
					bool passed2 = isAdjectiveNotConnectedToObjectOrSubject(currentSentenceInList, currentRelationInList, NLPdependencyRelationsType);
				#ifdef GIA_STANFORD_DO_NOT_USE_UNTESTED_RELEX_OPTIMISATION_CODE_THAT_IS_PROBABLY_STANFORD_COMPATIBLE
				}
				#endif

				if(passed2)
				{
				#endif
					int relationGovernorIndex = currentRelationInList->relationGovernorIndex;
					int relationDependentIndex = currentRelationInList->relationDependentIndex;
					GIAentityNode* thingEntity = GIAentityNodeArray[relationGovernorIndex];
					GIAentityNode* substanceEntity = GIAentityNodeArray[relationDependentIndex];
					thingEntity->hasSubstanceTemp = true;
					//substanceEntity->hasQualityTemp = true;	//[eg2 The locked door.. / Jim runs quickly / Mr. Smith is late {_amod/_advmod/_predadj}]
				#ifndef GIA_USE_GENERIC_DEPENDENCY_RELATION_INTERPRETATION_REDISTRIBUTION
				}
				#endif
			}

			//has subject:

			passed = false;
			for(int i=0; i<RELATION_TYPE_SUBJECT_NUMBER_OF_TYPES; i++)
			{
				if(currentRelationInList->relationType == relationTypeSubjectNameArray[i])
				{
					passed = true;
				}
			}
			//if(currentRelationInList->relationType == RELATION_TYPE_SUBJECT)
			if(passed)
			{
				int relationDependentIndex = currentRelationInList->relationDependentIndex;
				GIAentityNode* subjectEntity = GIAentityNodeArray[relationDependentIndex];
				subjectEntity->isSubjectTemp = true;

				int relationGovernorIndex = currentRelationInList->relationGovernorIndex;
				GIAentityNode* actionEntity = GIAentityNodeArray[relationGovernorIndex];
				actionEntity->isActionTemp = true;
			}

			//has object:

			passed = false;
			for(int i=0; i<RELATION_TYPE_OBJECT_NUMBER_OF_TYPES; i++)
			{
				if(currentRelationInList->relationType == relationTypeObjectNameArray[i])
				{
					passed = true;
				}
			}
			//if((currentRelationInList->relationType == RELATION_TYPE_OBJECT) || (currentRelationInList->relationType == RELATION_TYPE_OBJECT_TO))
			if(passed)
			{
				int relationDependentIndex = currentRelationInList->relationDependentIndex;
				GIAentityNode* objectEntity = GIAentityNodeArray[relationDependentIndex];
				objectEntity->isObjectTemp = true;

				int relationGovernorIndex = currentRelationInList->relationGovernorIndex;
				GIAentityNode* actionEntity = GIAentityNodeArray[relationGovernorIndex];
				actionEntity->isActionTemp = true;
			}
		#ifdef GIA_DO_NOT_PARSE_DISABLED_RELATIONS_OLD
		}
		#endif
		currentRelationInList = currentRelationInList->next;
	}
}

//updated 22 May 2012 with GIAnetworkIndexNodeArray+GIAentityNodeArray (and substances add)
void linkPronounReferencesRelex(GIAsentence* currentSentenceInList, bool GIAentityNodeArrayFilled[], GIAentityNode* GIAfeatureTempEntityNodeArray[], GIAentityNode* GIAentityNodeArray[], unordered_map<string, GIAentityNode*>* entityNodesActiveListNetworkIndexes, GIAfeature* featureArrayTemp[])
{
	#ifdef GIA_WARNINGS
	cout << "warning: linkPronounReferencesRelex{} is not robust - it requires further development" << endl;
	#endif

	for(int w=0; w<MAX_NUMBER_OF_WORDS_PER_SENTENCE; w++)
	{
		if(GIAentityNodeArrayFilled[w])
		{
			GIAentityNode* currentGIAEntityNode = GIAfeatureTempEntityNodeArray[w];
			#ifdef GIA_PRONOUN_REFERENCING_DEBUG
			cout << "currentGIAEntityNode->entityName = " << currentGIAEntityNode->entityName << endl;
			#endif
			for(int i=0; i< REFERENCE_TYPE_PERSON_NUMBER_OF_TYPES; i++)
			{
				#ifdef GIA_PRONOUN_REFERENCING_DEBUG
				cout << "i = " << i << endl;
				#endif
				if(((currentGIAEntityNode->entityName == referenceTypePossessiveNameArray[i]) || (currentGIAEntityNode->entityName == referenceTypePersonNameArray[i])) && (currentGIAEntityNode->grammaticalPronounTemp))
				{//pronoun required for currentGIAEntityNode
					#ifdef GIA_DEBUG
					//cout << "currentGIAEntityNode->entityName = " << currentGIAEntityNode->entityName << endl;
					#endif
					//now go for a search in tree for given / this sentence + previous sentence until find candidate reference source

					GIAentityNode* referenceSource = NULL;
					bool referenceSourceHasBeenFound = false;
					bool stillSentencesToSearch = true;
					GIAsentence* currentSentenceInWhichReferenceSourceIsBeingSearchedFor = currentSentenceInList;
					int s2 = 0;
					while(!referenceSourceHasBeenFound && stillSentencesToSearch)
					{
						#ifdef GIA_PRONOUN_REFERENCING_DEBUG
						cout << "s2 = " << s2 << endl;
						#endif
						GIArelation* currentRelationInWhichReferenceSourceIsBeingSearchedFor = currentSentenceInWhichReferenceSourceIsBeingSearchedFor->firstRelationInList;
						int maxWordLimit = 999999;
						if(s2 == 0)
						{
							maxWordLimit = w;
						}
						int w2 = 0;
						while((currentRelationInWhichReferenceSourceIsBeingSearchedFor->next != NULL) && (w2 < maxWordLimit))
						{

							long entityIndex = -1;
							bool entityAlreadyExistant = false;

							string entityName = currentRelationInWhichReferenceSourceIsBeingSearchedFor->relationDependent;
							#ifdef GIA_PRONOUN_REFERENCING_DEBUG
							cout << "w2 = " << w2 << endl;
							cout << "currentRelationInWhichReferenceSourceIsBeingSearchedFor = " << entityName << endl;
							#endif

							if(entityName != "")
							{
								bool entityAlreadyExistant = false;
								GIAentityNode* currentEntityInWhichReferenceSourceIsBeingSearchedFor = findOrAddNetworkIndexEntityNodeByNameSimpleWrapper(&entityName, &entityAlreadyExistant, entityNodesActiveListNetworkIndexes);
								//CHECK THIS; !applyNetworkIndexEntityAlreadyExistsFunction

								if(entityAlreadyExistant)
								{
									#ifdef GIA_PRONOUN_REFERENCING_DEBUG
									cout << "candidateReferenceSourceEntityName = " << entityName << endl;
									#endif

									bool entityPassesGrammaticalTestsForReference = true;

									//if(referenceTypePersonCrossReferenceNumberArray[i] != GRAMMATICAL_CATEGORY_UNDEFINED)
									//if(!((referenceTypePersonCrossReferenceNumberArray[i] == GRAMMATICAL_CATEGORY_UNDEFINED) && (referenceTypePersonCrossReferenceNumberArray[i] == GRAMMATICAL_CATEGORY_UNDEFINED)))
									//{
										if(currentEntityInWhichReferenceSourceIsBeingSearchedFor->grammaticalNumber != referenceTypePersonCrossReferenceNumberArray[i])
										{
											#ifdef GIA_PRONOUN_REFERENCING_DEBUG
											cout << "(currentEntityInWhichReferenceSourceIsBeingSearchedFor->grammaticalNumber != referenceTypePersonCrossReferenceNumberArray[i])" << endl;
											#endif
											entityPassesGrammaticalTestsForReference = false;
										}
									//}
									//if(referenceTypePersonCrossReferenceGenderArray[i] != GRAMMATICAL_CATEGORY_UNDEFINED)
									//if(!((referenceTypePersonCrossReferenceGenderArray[i] == GRAMMATICAL_CATEGORY_UNDEFINED) && (referenceTypePersonCrossReferenceGenderArray[i] == GRAMMATICAL_CATEGORY_UNDEFINED)))
									//{
										if(currentEntityInWhichReferenceSourceIsBeingSearchedFor->grammaticalGenderTemp != referenceTypePersonCrossReferenceGenderArray[i])
										{
											#ifdef GIA_PRONOUN_REFERENCING_DEBUG
											cout << "(currentEntityInWhichReferenceSourceIsBeingSearchedFor->grammaticalGenderTemp != referenceTypePersonCrossReferenceGenderArray[i])" << endl;
											#endif
											entityPassesGrammaticalTestsForReference = false;
										}
									//}
									//if(referenceTypePersonCrossReferenceDefiniteArray[i] != GRAMMATICAL_CATEGORY_UNDEFINED)
									//if(!((referenceTypePersonCrossReferenceDefiniteArray[i] == GRAMMATICAL_CATEGORY_UNDEFINED) && (referenceTypePersonCrossReferenceDefiniteArray[i] == GRAMMATICAL_CATEGORY_UNDEFINED)))
									//{
										if(currentEntityInWhichReferenceSourceIsBeingSearchedFor->grammaticalDefiniteTemp != referenceTypePersonCrossReferenceDefiniteArray[i])
										{
											#ifdef GIA_PRONOUN_REFERENCING_DEBUG
											cout << "(currentEntityInWhichReferenceSourceIsBeingSearchedFor->grammaticalDefiniteTemp != referenceTypePersonCrossReferenceDefiniteArray[i])" << endl;
											#endif
											entityPassesGrammaticalTestsForReference = false;
										}
									//}
									//if(referenceTypePersonCrossReferencePersonArray[i] != GRAMMATICAL_CATEGORY_UNDEFINED)
									//if(!((referenceTypePersonCrossReferencePersonArray[i] == GRAMMATICAL_CATEGORY_UNDEFINED) && (referenceTypePersonCrossReferencePersonArray[i] == GRAMMATICAL_CATEGORY_UNDEFINED)))
									//{
										if(currentEntityInWhichReferenceSourceIsBeingSearchedFor->grammaticalProperNounTemp != referenceTypePersonCrossReferencePersonArray[i])
										{
											#ifdef GIA_PRONOUN_REFERENCING_DEBUG
											cout << "(currentEntityInWhichReferenceSourceIsBeingSearchedFor->grammaticalProperNounTemp != referenceTypePersonCrossReferencePersonArray[i])" << endl;
											#endif
											entityPassesGrammaticalTestsForReference = false;
										}


										if(currentEntityInWhichReferenceSourceIsBeingSearchedFor->grammaticalPronounTemp)
										{
											#ifdef GIA_PRONOUN_REFERENCING_DEBUG
											cout << "(currentEntityInWhichReferenceSourceIsBeingSearchedFor->grammaticalPronounTemp == GRAMMATICAL_PRONOUN)" << endl;
											#endif
											entityPassesGrammaticalTestsForReference = false;
										}



									//}
									if(entityPassesGrammaticalTestsForReference)
									{
										#ifdef GIA_TRANSLATOR_DEBUG
										cout << "entityPassesGrammaticalTestsForReference" << endl;
										#endif

										#ifdef GIA_PRONOUN_REFERENCING_DEBUG
										cout << "referenceTypePersonCrossReferenceNumberArray[i] = " << referenceTypePersonCrossReferenceNumberArray[i] << endl;
										cout << "referenceTypePersonCrossReferenceGenderArray[i] = " << referenceTypePersonCrossReferenceGenderArray[i] << endl;
										cout << "referenceTypePersonCrossReferenceDefiniteArray[i] = " << referenceTypePersonCrossReferenceDefiniteArray[i] << endl;
										cout << "referenceTypePersonCrossReferencePersonArray[i] = " << referenceTypePersonCrossReferencePersonArray[i] << endl;
										cout << "currentEntityInWhichReferenceSourceIsBeingSearchedFor->grammaticalNumber = " << currentEntityInWhichReferenceSourceIsBeingSearchedFor->grammaticalNumber << endl;
										cout << "currentEntityInWhichReferenceSourceIsBeingSearchedFor->grammaticalGenderTemp = " << currentEntityInWhichReferenceSourceIsBeingSearchedFor->grammaticalGenderTemp << endl;
										cout << "currentEntityInWhichReferenceSourceIsBeingSearchedFor->grammaticalDefiniteTemp = " << currentEntityInWhichReferenceSourceIsBeingSearchedFor->grammaticalDefiniteTemp << endl;
										cout << "currentEntityInWhichReferenceSourceIsBeingSearchedFor->grammaticalProperNounTemp = " << currentEntityInWhichReferenceSourceIsBeingSearchedFor->grammaticalProperNounTemp << endl;
										#endif

										if(currentEntityInWhichReferenceSourceIsBeingSearchedFor->isSubjectTemp)
										{
											#ifdef GIA_PRONOUN_REFERENCING_DEBUG
											cout << "currentEntityInWhichReferenceSourceIsBeingSearchedFor->isSubjectTemp = " << currentEntityInWhichReferenceSourceIsBeingSearchedFor->isSubjectTemp << endl;
											#endif
											referenceSourceHasBeenFound = true;
											referenceSource = currentEntityInWhichReferenceSourceIsBeingSearchedFor;
										}
										else if((currentEntityInWhichReferenceSourceIsBeingSearchedFor->isObjectTemp) && (s2 > 0))
										{
											#ifdef GIA_PRONOUN_REFERENCING_DEBUG
											cout << "currentEntityInWhichReferenceSourceIsBeingSearchedFor->isObjectTemp = " << currentEntityInWhichReferenceSourceIsBeingSearchedFor->isObjectTemp << endl;
											#endif
											referenceSourceHasBeenFound = true;
											referenceSource = currentEntityInWhichReferenceSourceIsBeingSearchedFor;
										}
										else if((currentEntityInWhichReferenceSourceIsBeingSearchedFor->hasSubstanceTemp) && (s2 > 0))
										{
											#ifdef GIA_PRONOUN_REFERENCING_DEBUG
											cout << "currentEntityInWhichReferenceSourceIsBeingSearchedFor->hasSubstanceTemp = " << currentEntityInWhichReferenceSourceIsBeingSearchedFor->hasSubstanceTemp << endl;
											#endif
											referenceSourceHasBeenFound = true;
											referenceSource = currentEntityInWhichReferenceSourceIsBeingSearchedFor;
										}
									}
								}
								else
								{
									#ifdef GIA_PRONOUN_REFERENCING_DEBUG
									cout << "error: !entityAlreadyExistant" << endl;	//will be non-existant in the case of intermediary words like "the"
									//exit(0);
									#endif
								}
							}
							w2++;

							currentRelationInWhichReferenceSourceIsBeingSearchedFor = currentRelationInWhichReferenceSourceIsBeingSearchedFor->next;
						}

						if(currentSentenceInWhichReferenceSourceIsBeingSearchedFor->previous != NULL)
						{
							currentSentenceInWhichReferenceSourceIsBeingSearchedFor = currentSentenceInWhichReferenceSourceIsBeingSearchedFor->previous;
						}
						else
						{
							stillSentencesToSearch = false;
						}
						s2++;

					}

					if(referenceSourceHasBeenFound)
					{//remap entity; eg He to John
						#ifdef GIA_TRANSLATOR_DEBUG
						cout << "referenceSourceHasBeenFound: assigning " << GIAfeatureTempEntityNodeArray[w]->entityName << " to " << referenceSource->entityName << "." << endl;
						#endif

						disableEntity(GIAfeatureTempEntityNodeArray[w]);

					#ifdef GIA_USE_ORIGINAL_PRONOMINAL_COREFERENCE_RESOLUTION_IGNORE_SUBSTANCES_TAKE_NETWORK_INDEXES_ONLY
						GIAnetworkIndexNodeArray[w] = referenceSource;
						#ifdef GIA_USE_GENERIC_DEPENDENCY_RELATION_INTERPRETATION_SUBSTANCES
						referenceSource->isPronounReference = true;
						#else
						featureArrayTemp[w]->isPronounReference = true;
						#endif
						applyNetworkIndexEntityAlreadyExistsFunction(referenceSource, true, true);
					#else

						bool networkIndexHasASubstance = false;
						//now find the substance in the referenceSource networkIndex entity that matches the referenceSource sentence/entity index
						for(vector<GIAentityConnection*>::iterator connectionIter = referenceSource->associatedInstanceNodeList->begin(); connectionIter != referenceSource->associatedInstanceNodeList->end(); connectionIter++)
						{
							GIAentityNode* substance = (*connectionIter)->entity;
							#ifdef GIA_PRONOUN_REFERENCING_DEBUG
							cout << "substance->sentenceIndexTemp = " << substance->sentenceIndexTemp << endl;
							cout << "substance->entityIndexTemp = " << substance->entityIndexTemp << endl;
							//cout << "referenceSourceSentenceIndex = " << referenceSourceSentenceIndex << endl;
							//cout << "referenceSourceEntityNodeIndex = " << referenceSourceEntityNodeIndex << endl;
							#endif
							if(!networkIndexHasASubstance)
							{//take first instance/substance in list

								#ifdef GIA_TRANSLATOR_DEBUG
								cout << "NonPronoun/substance referenceSourceHasBeenFound: assigning " << GIAentityNodeArray[w]->entityName << " to " << referenceSource->entityName << "." << endl;
								#endif

								//found the substance in the referenceSource networkIndex entity that matches the referenceSource sentence/entity index
								//now only link them

								#ifdef GIA_USE_GENERIC_DEPENDENCY_RELATION_INTERPRETATION_SUBSTANCES
								substance->isPronounReference = true;
								referenceSource->isPronounReference = true;
								#else
								featureArrayTemp[w]->isPronounReference = true;
								#endif
								GIAentityNodeArray[w] = substance;
								#ifdef GIA_RECORD_WAS_REFERENCE_INFORMATION
								if(referenceSource->sentenceIndexTemp != currentSentenceInList->sentenceIndex)
								{//Added condition GIA 2f7a - 06 July 2014 (wasReference is only used for intersentence references)
									substance->wasReference = true;
									referenceSource->wasReference = true;
								}
								#endif
							}

							networkIndexHasASubstance = true;
						}
						if(!networkIndexHasASubstance)
						{
							#ifdef GIA_TRANSLATOR_DEBUG
							cout << "referenceSourceHasBeenFound: assigning " << GIAentityNodeArray[w]->entityName << " to " << referenceSource->entityName << "." << endl;
							#endif

							#ifdef GIA_USE_GENERIC_DEPENDENCY_RELATION_INTERPRETATION_SUBSTANCES
							referenceSource->isPronounReference = true;
							#else
							featureArrayTemp[w]->isPronounReference = true;
							#endif
							GIAentityNodeArray[w] = referenceSource;
							#ifdef GIA_RECORD_WAS_REFERENCE_INFORMATION
							if(referenceSource->sentenceIndexTemp != currentSentenceInList->sentenceIndex)
							{//Added condition GIA 2f7a - 06 July 2014 (wasReference is only used for intersentence references)
								referenceSource->wasReference = true;
							}
							#endif
							applyNetworkIndexEntityAlreadyExistsFunction(referenceSource, true, true);
						}
					#endif
					}
				}
			}
		}
	}
}


#ifdef GIA_USE_STANFORD_CORENLP
void linkPronounAndTextualContextReferencesStanfordCoreNLP(GIAsentence* currentSentenceInList, bool GIAentityNodeArrayFilled[], GIAentityNode* GIAfeatureTempEntityNodeArray[], GIAentityNode* GIAentityNodeArray[], unordered_map<string, GIAentityNode*>* entityNodesActiveListNetworkIndexes, GIAstanfordCoreNLPcoreference* firstCoreferenceInList, GIAfeature* featureArrayTemp[])
{
	#ifdef GIA_PRONOUN_REFERENCING_DEBUG
	//cout << "linkPronounAndTextualContextReferencesStanfordCoreNLP{}" << endl;
	#endif
	GIAstanfordCoreNLPcoreference* currentCoreferenceInList = firstCoreferenceInList;
	while(currentCoreferenceInList->next != NULL)
	{
		GIAstanfordCoreNLPmention* firstMentionInList = currentCoreferenceInList->firstMentionInList;
		GIAstanfordCoreNLPmention* currentMentionInList = firstMentionInList;
		GIAentityNode* referenceSource = NULL;
		bool foundReferenceSource = false;
		while(currentMentionInList->next != NULL)
		{
			int referenceSourceSentenceIndex;
			int referenceSourceEntityNodeIndex;

			if(!foundReferenceSource)
			{
				if(currentMentionInList->representative)
				{
					referenceSourceSentenceIndex = currentMentionInList->sentence;
					referenceSourceEntityNodeIndex = currentMentionInList->head;

					#ifdef GIA_PRONOUN_REFERENCING_DEBUG
					//cout << "referenceSourceSentenceIndex = " << referenceSourceSentenceIndex << endl;
					//cout << "\treferenceSourceEntityNodeIndex = " << referenceSourceEntityNodeIndex << endl;
					#endif

					#ifdef GIA_ENABLE_TEXTUAL_CONTEXT_REFERENCING_ONLY_ACCEPT_INTRASENTENCE_STANFORD_COREFERENCES
					if(referenceSourceSentenceIndex == currentSentenceInList->sentenceIndex)
					#else
					if(referenceSourceSentenceIndex <= currentSentenceInList->sentenceIndex)
					#endif
					{
						GIAsentence* currentSentenceInWhichReferenceSourceIsBeingSearchedFor = currentSentenceInList;
						bool stillExistsPreviousSentence = true;
						while(stillExistsPreviousSentence)
						{
							#ifdef GIA_PRONOUN_REFERENCING_DEBUG
							//cout << "currentSentenceInWhichReferenceSourceIsBeingSearchedFor->sentenceIndex = " <<  currentSentenceInWhichReferenceSourceIsBeingSearchedFor->sentenceIndex << endl;
							#endif
							if(currentSentenceInWhichReferenceSourceIsBeingSearchedFor->sentenceIndex == referenceSourceSentenceIndex)
							{
								GIAfeature* currentFeatureInList = currentSentenceInWhichReferenceSourceIsBeingSearchedFor->firstFeatureInList;
								while(currentFeatureInList->next != NULL)
								{
									#ifdef GIA_PRONOUN_REFERENCING_DEBUG
									//cout << "currentFeatureInList->entityIndex = " <<  currentFeatureInList->entityIndex << endl;
									#endif
									if(currentFeatureInList->entityIndex == referenceSourceEntityNodeIndex)
									{
										string entityName = currentFeatureInList->lemma;	//CHECK THIS; assumes [at least one instance of] the reference source will always occur as a relation argument/dependent (ie, will not find the reference source if it only occurs as a relation function/governer)

										bool entityAlreadyExistant = false;
										GIAentityNode* currentEntityInWhichReferenceSourceIsBeingSearchedFor = findOrAddNetworkIndexEntityNodeByNameSimpleWrapper(&entityName, &entityAlreadyExistant, entityNodesActiveListNetworkIndexes);
										//CHECK THIS; !applyNetworkIndexEntityAlreadyExistsFunction

										#ifdef GIA_PRONOUN_REFERENCING_DEBUG
										/*
										cout << "\tentityName = " << entityName << endl;
										cout << "\treferenceSourceSentenceIndex = " << referenceSourceSentenceIndex << endl;
										cout << "\treferenceSourceEntityNodeIndex = " << referenceSourceEntityNodeIndex << endl;
										*/
										#endif

										if(entityAlreadyExistant)
										{
											referenceSource = currentEntityInWhichReferenceSourceIsBeingSearchedFor;

											#ifdef GIA_PRONOUN_REFERENCING_DEBUG
											//cout << "\t\treferenceSource->entityName = " << referenceSource->entityName << endl;
											#endif
											foundReferenceSource = true;
										}

										//now search for this entity

									}
									currentFeatureInList = currentFeatureInList->next;
								}
							}

							if(currentSentenceInWhichReferenceSourceIsBeingSearchedFor->previous != NULL)
							{
								currentSentenceInWhichReferenceSourceIsBeingSearchedFor = currentSentenceInWhichReferenceSourceIsBeingSearchedFor->previous;
							}
							else
							{
								stillExistsPreviousSentence = false;
							}
						}
					}
				}
			}

			if(foundReferenceSource)
			{
				if(!(currentMentionInList->representative))
				{//continue only for references, eg pronoun (not for their source, eg name)

					if(currentMentionInList->sentence == currentSentenceInList->sentenceIndex)
					{
						int currentSentenceEntityNodeIndex = currentMentionInList->head;
						if(GIAentityNodeArrayFilled[currentSentenceEntityNodeIndex])
						{
							GIAfeature* referenceFeature = featureArrayTemp[currentSentenceEntityNodeIndex];

							bool coreferenceIsPronoun = false;
							//use stanfordPOS information to ensure that the reference is a pronoun - NB alternatively, could use referenceTypePersonNameArray and referenceTypePossessiveNameArray (as there is only a limited set of pronouns in english)
							for(int i=0; i<FEATURE_POS_TAG_INDICATES_PRONOUN_NUMBER_OF_TYPES; i++)
							{
								if(referenceFeature->stanfordPOS == featurePOSindicatesPronounTypeArray[i])
								{
									coreferenceIsPronoun = true;
								}
							}

							#ifdef GIA_STANFORD_CORE_NLP_CODEPENDENCIES_ONLY_USE_PRONOMINAL_COREFERENCE_RESOLUTION
							if(coreferenceIsPronoun)
							{
							#endif
								bool networkIndexHasASubstance = false;
								//now find the substance in the referenceSource networkIndex entity that matches the referenceSource sentence/entity index
								for(vector<GIAentityConnection*>::iterator connectionIter = referenceSource->associatedInstanceNodeList->begin(); connectionIter != referenceSource->associatedInstanceNodeList->end(); connectionIter++)
								{
									GIAentityNode* substance = (*connectionIter)->entity;
									#ifdef GIA_PRONOUN_REFERENCING_DEBUG
									/*
									cout << "substance->sentenceIndexTemp = " << substance->sentenceIndexTemp << endl;
									cout << "substance->entityIndexTemp = " << substance->entityIndexTemp << endl;
									cout << "referenceSourceSentenceIndex = " << referenceSourceSentenceIndex << endl;
									cout << "referenceSourceEntityNodeIndex = " << referenceSourceEntityNodeIndex << endl;
									*/
									#endif
									if((substance->sentenceIndexTemp == referenceSourceSentenceIndex) && (substance->entityIndexTemp == referenceSourceEntityNodeIndex))
									{
										#ifdef GIA_STANFORD_CORENLP_CODEPENDENCY_PRONOMINAL_REFERENCING_DEBUG
										cout << "NonPronoun/substance referenceSourceHasBeenFound: assigning " << GIAentityNodeArray[currentSentenceEntityNodeIndex]->entityName << " to " << referenceSource->entityName << "." << endl;
										#endif

										//found the substance in the referenceSource networkIndex entity that matches the referenceSource sentence/entity index
										//now only link them
										#ifdef GIA_STANFORD_CORE_NLP_CODEPENDENCIES_DO_NOT_USE_IF_REFERENCE_IS_NOT_DEFINITE_OR_PROPER_NOUN
										if(referenceFeature->grammaticalDefinite || referenceFeature->grammaticalRelexPersonOrStanfordProperNoun)
										{
										#endif
											GIAentityNodeArray[currentSentenceEntityNodeIndex] = substance;
											#ifdef GIA_RECORD_WAS_REFERENCE_INFORMATION
											if(referenceSourceSentenceIndex != currentSentenceInList->sentenceIndex)
											{//Added condition GIA 2f7a - 06 July 2014 (wasReference is only used for intersentence references)
												substance->wasReference = true;
												referenceSource->wasReference = true;
											}
											#endif
											if(coreferenceIsPronoun) //shifted inside if statement "if(referenceFeature->grammaticalDefinite || referenceFeature->grammaticalRelexPersonOrStanfordProperNoun)" 12 October 2012
											{
												#ifdef GIA_USE_GENERIC_DEPENDENCY_RELATION_INTERPRETATION_SUBSTANCES
												substance->isPronounReference = true;
												referenceSource->isPronounReference = true;
												#else
												featureArrayTemp[currentSentenceEntityNodeIndex]->isPronounReference = true;
												#endif
											}
										#ifdef GIA_STANFORD_CORE_NLP_CODEPENDENCIES_DO_NOT_USE_IF_REFERENCE_IS_NOT_DEFINITE_OR_PROPER_NOUN
										}
										#endif


									}
									networkIndexHasASubstance = true;
								}
								#ifndef GIA_USE_ORIGINAL_PRONOMINAL_COREFERENCE_RESOLUTION_IGNORE_SUBSTANCES_TAKE_NETWORK_INDEXES_ONLY
								if(!networkIndexHasASubstance)
								{
									#ifdef GIA_STANFORD_CORENLP_CODEPENDENCY_PRONOMINAL_REFERENCING_DEBUG
									cout << "referenceSourceHasBeenFound: assigning " << GIAentityNodeArray[currentSentenceEntityNodeIndex]->entityName << " to " << referenceSource->entityName << "." << endl;
									#endif

									if(coreferenceIsPronoun)
									{
										disableEntity(GIAfeatureTempEntityNodeArray[currentSentenceEntityNodeIndex]);
										#ifdef GIA_USE_GENERIC_DEPENDENCY_RELATION_INTERPRETATION_SUBSTANCES
										referenceSource->isPronounReference = true;
										#else
										featureArrayTemp[currentSentenceEntityNodeIndex]->isPronounReference = true;
										#endif
									}

									GIAentityNodeArray[currentSentenceEntityNodeIndex] = referenceSource;		//GIAnetworkIndexNodeArray[currentSentenceEntityNodeIndex] = referenceSource;
									#ifdef GIA_RECORD_WAS_REFERENCE_INFORMATION
									if(referenceSourceSentenceIndex != currentSentenceInList->sentenceIndex)
									{//Added condition GIA 2f7a - 06 July 2014 (wasReference is only used for intersentence references)
										referenceSource->wasReference = true;
									}
									#endif
									applyNetworkIndexEntityAlreadyExistsFunction(referenceSource, true, true);

								}
								#endif
							#ifdef GIA_STANFORD_CORE_NLP_CODEPENDENCIES_ONLY_USE_PRONOMINAL_COREFERENCE_RESOLUTION
							}
							#endif
						}
					}
				}
			}

			currentMentionInList = currentMentionInList->next;
		}
		currentCoreferenceInList = currentCoreferenceInList->next;
	}
}
#endif

#ifdef GIA_RECORD_SAME_REFERENCE_SET_INFORMATION

void fillExplicitReferenceSameSetTags(GIAsentence* currentSentenceInList)
{
	//eg the chicken which ate a pie rowed the boat. rcmod(chicken-2, ate-4) / nsubj(ate-4, chicken-2)		 [OLD: + the blue chicken... amod(chicken-3, blue-2)]

	GIArelation* currentRelationInList = currentSentenceInList->firstRelationInList;
 	while(currentRelationInList->next != NULL)
	{
		#ifdef GIA_DO_NOT_PARSE_DISABLED_RELATIONS_OLD
		if(!(currentRelationInList->disabled))
		{
		#endif
			if(currentRelationInList->relationType == RELATION_TYPE_RELATIVE_CLAUSE_MODIFIER)
			{
				GIArelation* currentRelationInList2 = currentSentenceInList->firstRelationInList;
 				while(currentRelationInList2->next != NULL)
				{
					#ifdef GIA_DO_NOT_PARSE_DISABLED_RELATIONS_OLD
					if(!(currentRelationInList2->disabled))
					{
					#endif
						if((currentRelationInList->relationDependentIndex == currentRelationInList2->relationGovernorIndex) && (currentRelationInList->relationGovernorIndex == currentRelationInList2->relationDependentIndex))
						{//found matching rcmod
							currentRelationInList2->rcmodIndicatesSameReferenceSet = true;

							#ifdef GIA_ADVANCED_REFERENCING_DEBUG
							cout << "fillExplicitReferenceSameSetTags:" << endl;
							cout << "currentRelationInList2->relationType = " << currentRelationInList2->relationType << endl;
							cout << "currentRelationInList2->relationGovernor = " << currentRelationInList2->relationGovernor << endl;
							cout << "currentRelationInList2->relationDependent = " << currentRelationInList2->relationDependent << endl;
							#endif

							//link subject and object into same reference set if required
							bool passedSubject = false;
							bool passedObject = false;
							/*
							if(currentRelationInList2->relationType == RELATION_TYPE_SUBJECT)
							{
								passedSubject = true;
							}
							else if(currentRelationInList2->relationType == RELATION_TYPE_OBJECT)
							{
								passedObject = true;
							}
							*/
							for(int i=0; i<RELATION_TYPE_SUBJECT_NUMBER_OF_TYPES; i++)
							{
								if(currentRelationInList2->relationType == relationTypeSubjectNameArray[i])
								{
									passedSubject = true;
								}
							}
							for(int i=0; i<RELATION_TYPE_OBJECT_NUMBER_OF_TYPES; i++)
							{
								if(currentRelationInList2->relationType == relationTypeObjectNameArray[i])
								{
									passedObject = true;
								}
							}

							GIArelation* currentRelationInList3 = currentSentenceInList->firstRelationInList;
 							while(currentRelationInList3->next != NULL)
							{
								if(currentRelationInList3->relationGovernorIndex == currentRelationInList2->relationGovernorIndex)
								{
									bool passedActionPartner = false;
									/*
									if(passedSubject)
									{
										if(currentRelationInList3->relationType == RELATION_TYPE_OBJECT)
										{
											passedActionPartner = true;
										}
									}
									else if(passedObject)
									{
										if(currentRelationInList3->relationType == RELATION_TYPE_SUBJECT)
										{
											passedActionPartner = true;
										}
									}
									*/
									if(passedSubject)
									{
										for(int i=0; i<RELATION_TYPE_OBJECT_NUMBER_OF_TYPES; i++)
										{
											if(currentRelationInList3->relationType == relationTypeObjectNameArray[i])
											{
												passedActionPartner = true;
											}
										}
									}
									else if(passedObject)
									{
										for(int i=0; i<RELATION_TYPE_SUBJECT_NUMBER_OF_TYPES; i++)
										{
											if(currentRelationInList3->relationType == relationTypeSubjectNameArray[i])
											{
												passedActionPartner = true;
											}
										}
									}

									if(passedActionPartner)
									{
										//found action subject pair
										currentRelationInList3->rcmodIndicatesSameReferenceSet = true;

										#ifdef GIA_ADVANCED_REFERENCING_DEBUG
										cout << "fillExplicitReferenceSameSetTags:" << endl;
										cout << "currentRelationInList3->relationType = " << currentRelationInList3->relationType << endl;
										cout << "currentRelationInList3->relationGovernor = " << currentRelationInList3->relationGovernor << endl;
										cout << "currentRelationInList3->relationDependent = " << currentRelationInList3->relationDependent << endl;
										#endif
									}
								}

								currentRelationInList3 = currentRelationInList3->next;
							}
						}
					#ifdef GIA_DO_NOT_PARSE_DISABLED_RELATIONS_OLD
					}
					#endif

					currentRelationInList2 = currentRelationInList2->next;
				}
			}

		#ifdef GIA_DO_NOT_PARSE_DISABLED_RELATIONS_OLD
		}
		#endif

		currentRelationInList = currentRelationInList->next;
	}
}


int identifyReferenceSets(unordered_map<string, GIAentityNode*>* sentenceNetworkIndexEntityNodesList, bool NLPdependencyRelationsType, vector<GIAentityNode*>* referenceSetDefiniteEntityList)
{
	#ifdef GIA_DEBUG
	//cout << "\n******************** identifyReferenceSets* ******************\n" << endl;
	#endif

	bool haveSentenceEntityIndexOfDeterminers = false;
	if(NLPdependencyRelationsType == GIA_DEPENDENCY_RELATIONS_TYPE_STANFORD)
	{
		haveSentenceEntityIndexOfDeterminers = true;
	}

	#ifdef GIA_USE_1N1ATEMP1TO8_CHANGES
	resetReferenceSets(sentenceNetworkIndexEntityNodesList);
	#endif

	int referenceSetID = 0;

	for(unordered_map<string, GIAentityNode*>::iterator networkIndexEntityNodesListIter = sentenceNetworkIndexEntityNodesList->begin(); networkIndexEntityNodesListIter != sentenceNetworkIndexEntityNodesList->end(); networkIndexEntityNodesListIter++)
	{
		GIAentityNode* entityNode = networkIndexEntityNodesListIter->second;
		#ifdef GIA_ADVANCED_REFERENCING_DEBUG
		cout << "\t identifyDefiniteReferenceSets: " << entityNode->entityName << endl;
		#endif
		identifyReferenceSetNetworkIndexEntityEntrance(entityNode, &referenceSetID, haveSentenceEntityIndexOfDeterminers, referenceSetDefiniteEntityList);
	}

	int numberReferenceSets = referenceSetID;
	return numberReferenceSets;

}

void resetReferenceSets(unordered_map<string, GIAentityNode*>* sentenceNetworkIndexEntityNodesList)
{
	for(unordered_map<string, GIAentityNode*>::iterator networkIndexEntityNodesListIter = sentenceNetworkIndexEntityNodesList->begin(); networkIndexEntityNodesListIter != sentenceNetworkIndexEntityNodesList->end(); networkIndexEntityNodesListIter++)
	{
		GIAentityNode* entityNode = networkIndexEntityNodesListIter->second;
		entityNode->referenceSetID = GIA_REFERENCE_SET_ID_UNDEFINED;
	}
}

void identifyReferenceSetNetworkIndexEntityEntrance(GIAentityNode* entityNode, int* referenceSetID, bool haveSentenceEntityIndexOfDeterminers, vector<GIAentityNode*>* referenceSetDefiniteEntityList)
{
	#ifdef GIA_ADVANCED_REFERENCING_DEBUG
	cout << "identifyReferenceSetEntrance{}: entityNode being traced = " << entityNode->entityName << endl;
	cout << "identifyReferenceSetEntrance{}: referenceSetID = " <<* referenceSetID << endl;
	#endif
	#ifdef GIA_ADVANCED_REFERENCING_DEBUG_TOO_LARGE_REFERENCE_SET
	cout << "identifyReferenceSetEntrance{}: " << entityNode->entityName << endl;
	#endif

	if(!(entityNode->entityVectorConnectionsArray[GIA_ENTITY_VECTOR_CONNECTION_TYPE_ASSOCIATED_INSTANCES].empty()))
	{
		for(vector<GIAentityConnection*>::iterator connectionIter = entityNode->entityVectorConnectionsArray[GIA_ENTITY_VECTOR_CONNECTION_TYPE_ASSOCIATED_INSTANCES].begin(); connectionIter < entityNode->entityVectorConnectionsArray[GIA_ENTITY_VECTOR_CONNECTION_TYPE_ASSOCIATED_INSTANCES].end(); connectionIter++)
		{
			GIAentityNode* currentInstance = (*connectionIter)->entity;
			#ifdef GIA_ADVANCED_REFERENCING_DEBUG
			//cout << "currentInstance->entityName = " << currentInstance->entityName << endl;
			#endif

			#ifdef GIA_USE_ADVANCED_REFERENCING_IDENTIFY_DEFINITE_SETS_ONLY
			//do: CHECKTHIS; may need to re-execute identifyEntityTypes on EntityNodeArray after finishing executing GIAtranslator.cpp convertSentenceSyntacticRelationsIntoGIAnetworkNodes
			#ifdef GIA_USE_ADVANCED_REFERENCING_IDENTIFY_SETS_WITH_SUBJECT_OR_OBJECT_ONLY
			if((currentInstance->isSubjectTemp) || (currentInstance->isObjectTemp))
			{
			#endif
				#ifdef GIA_ADVANCED_REFERENCING_DEBUG
				cout << "subj Found" << endl;
				#endif

				bool passDefiniteSetChecks = false;
				if(currentInstance->grammaticalDefiniteTemp)
				{
					passDefiniteSetChecks = true;
				}
				#ifdef GIA_USE_ADVANCED_REFERENCING_IDENTIFY_DEFINITE_SETS_ACCEPT_PROPERNOUNS
				if(currentInstance->grammaticalProperNounTemp)
				{
					passDefiniteSetChecks = true;
				}
				#endif
				#ifdef GIA_SUPPORT_SPECIFIC_CONCEPTS
				if(currentInstance->entityType == GIA_ENTITY_TYPE_TYPE_CONCEPT)	//&& !(currentInstance->grammaticalDefiniteTemp) - not required, as this is assumed the case already given (currentInstance->entityType == GIA_ENTITY_TYPE_TYPE_CONCEPT); NB "the red dogs" will not be designated as isConcept - only "red dogs" will
				{
					passDefiniteSetChecks = true;
				}
				#endif
				#ifdef GIA_IDENTIFY_REFERENCE_SET_NETWORK_INDEX_ENTITY_ENTRANCE_DO_NOT_ENTER_ON_AN_ACTION_NODE
				if(currentInstance->entityType == GIA_ENTITY_TYPE_TYPE_ACTION)
				{
					passDefiniteSetChecks = false;
				}
				#endif

				#ifdef GIA_TRANSLATOR_INTERPRET_PRENOMINAL_MODIFIER_SUBCLASSES_DISABLE_REFERENCING_OF_SUBCLASS_ARTIFICIAL_ENTITIES
				if(currentInstance->entityIndexTemp == GIA_TRANSLATOR_INTERPRET_PRENOMINAL_MODIFIER_SUBCLASSES_ARTIFICAL_ENTITY_INDEX)
				{
					passDefiniteSetChecks = false;
				}
				#endif

				if(passDefiniteSetChecks)
				{
			#endif
					#ifdef GIA_ADVANCED_REFERENCING_DEBUG_TOO_LARGE_REFERENCE_SET
					cout << "DEBUG: grammaticalDefiniteTemp Found: " << entityNode->entityName << endl;
					#endif

					#ifdef GIA_ADVANCED_REFERENCING_DEBUG
					cout << "grammaticalDefiniteTemp Found" << endl;
					#endif

					/*OLD:
					int minimumEntityIndexOfReferenceSet;
					if(haveSentenceEntityIndexOfDeterminers)
					{
						minimumEntityIndexOfReferenceSet = currentInstance->grammaticalIndexOfDeterminerTemp;
						cout << "\n1minimumEntityIndexOfReferenceSet = " << minimumEntityIndexOfReferenceSet << endl;
					}
					else
					{
						cout << "\n!haveSentenceEntityIndexOfDeterminers" << endl;
						minimumEntityIndexOfReferenceSet = currentInstance->entityIndexTemp;
					}
					*/
					int minimumEntityIndexOfReferenceSet = currentInstance->entityIndexTemp;

					//currentInstance->minimumEntityIndexOfReferenceSet = minimumEntityIndexOfReferenceSet;	//added 28 Sept 2013

					#ifdef GIA_ADVANCED_REFERENCING_DEBUG_TOO_LARGE_REFERENCE_SET
					cout << "minimumSentenceIndexOfReferenceSet1 = " << currentInstance->grammaticalIndexOfDeterminerTemp << endl;
					cout << "minimumSentenceIndexOfReferenceSet2 = " << currentInstance->entityIndexTemp << endl;
					#endif

					if(identifyReferenceSetDetermineNextCourseOfAction(currentInstance, true,* referenceSetID, minimumEntityIndexOfReferenceSet, false))
					{
						*referenceSetID	= *referenceSetID + 1;
						referenceSetDefiniteEntityList->push_back(currentInstance);
						#ifdef GIA_DEBUG
						//cout << "*referenceSetID++ = " <<* referenceSetID << endl;
						#endif
					}

			#ifdef GIA_USE_ADVANCED_REFERENCING_IDENTIFY_DEFINITE_SETS_ONLY

				}
			#ifdef GIA_USE_ADVANCED_REFERENCING_IDENTIFY_SETS_WITH_SUBJECT_OR_OBJECT_ONLY
			}
			#endif
			#endif

		}
	}
}

#endif

#ifdef GIA_USE_ADVANCED_REFERENCING

//based on answerQueryOrFindAndTagForHighlightingMatchingStructureInSemanticNetwork();
void createGIAcoreferenceInListBasedUponIdentifiedReferenceSets(unordered_map<string, GIAentityNode*>* sentenceNetworkIndexEntityNodesList, unordered_map<string, GIAentityNode*>* entityNodesActiveListNetworkIndexes, GIACoreference* firstGIACoreferenceInList, vector<GIAentityNode*>* referenceSetDefiniteEntityList, GIAsentence* currentSentenceInList)	//bool GIAentityNodeArrayFilled[], GIAentityNode* GIAentityNodeArray[]
{
	#ifdef GIA_ADVANCED_REFERENCING_DEBUG
	cout << "createGIAcoreferenceInListBasedUponIdentifiedReferenceSets{}" << endl;
	#endif

	#ifdef GIA_DATABASE_CLEAR_CACHE_EVERY_SENTENCE
	#ifdef GIA_USE_DATABASE
	int useDatabaseOriginal = getUseDatabase();
	if(getUseDatabase() == GIA_USE_DATABASE_TRUE_READ_ACTIVE)
	{
		initialiseDBentityNodesActiveListCompleteFastIndexDBcache();
	}
	#endif
	#endif

	GIACoreference* currentGIAcoreferenceInList = firstGIACoreferenceInList;

	int referenceSetID = 0;
	for(vector<GIAentityNode*>::iterator referenceSetDefiniteEntityIter = referenceSetDefiniteEntityList->begin(); referenceSetDefiniteEntityIter != referenceSetDefiniteEntityList->end(); referenceSetDefiniteEntityIter++)
	{
		GIAentityNode* referenceSetDefiniteEntity = *referenceSetDefiniteEntityIter;

		#ifdef GIA_ADVANCED_REFERENCING_DEBUG_SIMPLE2
		cout << "\n* ***************************************** referenceSetID = " << referenceSetID << endl;
		#endif

		GIAreferenceTraceParameters referenceTraceParameters;
		referenceTraceParameters.referenceSetID = referenceSetID;

		#ifdef GIA_SUPPORT_NLC_INTEGRATION_DEFINE_REFERENCE_CONTEXT_BY_TEXT_INDENTATION
		referenceTraceParameters.referenceSetDefiniteEntity = referenceSetDefiniteEntity;
		//referenceTraceParameters.firstSentenceInList = firstSentenceInList;
		#endif

		int maxNumberOfMatchedNodes = 0;
		GIAentityNode* queryEntityWithMaxNumberNodesMatched = NULL;
		GIAentityNode* networkEntityWithMaxNumberNodesMatched = NULL;
		bool foundAtLeastOneMatch = false;

		unordered_map<string, GIAentityNode*>* entityNodesActiveListNetworkIndexesQuery = sentenceNetworkIndexEntityNodesList;

		#ifdef GIA_SUPPORT_NLC_INTEGRATION_DISABLE_ADVANCED_REFERENCING_FOR_LOGICAL_CONDITIONS_CONCEPTS
		if(checkIfSentenceIsMathTextParsablePhrase(currentSentenceInList))
		{
			referenceTraceParameters.logicalConditionDisableTraceConcepts = true;
		}
		#endif

		#ifdef GIA_ENABLE_CONCEPT_ADVANCED_REFERENCING_ONLY
		referenceTraceParameters.traceConceptsOnly = true;
		#endif
		#ifdef GIA_ADVANCED_REFERENCING_SUPPORT_INTRASENTENCE_REFERENCING
		referenceTraceParameters.intrasentenceReference = false;
		#endif
		#ifdef GIA_SUPPORT_NLC_INTEGRATION_DEFINE_REFERENCE_CONTEXT_BY_TEXT_INDENTATION
		referenceTraceParameters.testReferenceSetContext = true;
		#endif
		#ifdef GIA_CREATE_NEW_CONCEPT_FOR_EVERY_REFERENCE_TO_A_CONCEPT
		referenceTraceParameters.doNotParseQuerySubnetsWithConcepts = true;
		#endif
		#ifdef GIA_ADVANCED_REFERENCING_DEBUG
		cout << "1. createGIAcoreferenceInListBasedUponIdentifiedReferenceSet (!intrasentenceReference)" << endl;
		#endif
		#ifdef GIA_DEBUG
		//cout << "!intrasentence start:" << endl;
		#endif
		createGIAcoreferenceInListBasedUponIdentifiedReferenceSet(sentenceNetworkIndexEntityNodesList, entityNodesActiveListNetworkIndexes, &referenceTraceParameters, &maxNumberOfMatchedNodes, &queryEntityWithMaxNumberNodesMatched, &networkEntityWithMaxNumberNodesMatched, &foundAtLeastOneMatch);
		#ifdef GIA_DEBUG
		//cout << "intrasentence start ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;
		#endif
		#ifdef GIA_ADVANCED_REFERENCING_SUPPORT_INTRASENTENCE_REFERENCING
		#ifdef GIA_ADVANCED_REFERENCING_DEBUG
		cout << "2. createGIAcoreferenceInListBasedUponIdentifiedReferenceSet (intrasentenceReference)" << endl;
		#endif
		#ifdef GIA_USE_DATABASE
		setUseDatabase(GIA_USE_DATABASE_FALSE);
		#endif
		referenceTraceParameters.intrasentenceReference = true;
		#ifdef GIA_SUPPORT_NLC_INTEGRATION_DEFINE_REFERENCE_CONTEXT_BY_TEXT_INDENTATION
		referenceTraceParameters.testReferenceSetContext = false;
		#endif
		#ifdef GIA_CREATE_NEW_CONCEPT_FOR_EVERY_REFERENCE_TO_A_CONCEPT
		referenceTraceParameters.doNotParseQuerySubnetsWithConcepts = false;	//unnecessary as sentences with concepts will never contain intrasentence referencing... (eg "black birds are really fast, and black birds are really tall" does not require intrasentence referencing; where as "a black bird lives is really fast, and the black bird is tall" requires intrasentence referencing)
		#endif
		bool foundAtLeastOneMatchIntraSentence = false;
		createGIAcoreferenceInListBasedUponIdentifiedReferenceSet(sentenceNetworkIndexEntityNodesList, sentenceNetworkIndexEntityNodesList, &referenceTraceParameters, &maxNumberOfMatchedNodes, &queryEntityWithMaxNumberNodesMatched, &networkEntityWithMaxNumberNodesMatched, &foundAtLeastOneMatchIntraSentence);	//always perform intrasentence reference detection last (as this takes priority)
		#ifdef GIA_DEBUG
		//cout << "intersentence end" << endl;
		#endif
		if(foundAtLeastOneMatchIntraSentence)
		{
			#ifdef GIA_ADVANCED_REFERENCING_DEBUG
			cout << "\nfoundAtLeastOneMatchIntraSentence" << endl;
			#endif
			foundAtLeastOneMatch = true;
			referenceTraceParameters.intrasentenceReference = true;		//already the case
			#ifdef GIA_SUPPORT_NLC_INTEGRATION_DEFINE_REFERENCE_CONTEXT_BY_TEXT_INDENTATION
			referenceTraceParameters.testReferenceSetContext = false;
			#endif
		}
		else
		{
			referenceTraceParameters.intrasentenceReference = false;
			#ifdef GIA_SUPPORT_NLC_INTEGRATION_DEFINE_REFERENCE_CONTEXT_BY_TEXT_INDENTATION
			referenceTraceParameters.testReferenceSetContext = true;
			#endif
		}
		#ifdef GIA_USE_DATABASE
		setUseDatabase(useDatabaseOriginal);
		#endif
		#endif

		#ifdef GIA_ADVANCED_REFERENCING_DEBUG
		cout << "\nfinished reference trace round 1" << endl;
		#endif

		//now perform the final optimised trace
		if(foundAtLeastOneMatch)
		{
			GIAqueryTraceParameters queryTraceParameters;	//irrelevant

			int numberOfMatchedNodesTemp = 0;
			int numberOfMatchedNodesRequiredSynonymnDetectionTemp = 0;

			#ifdef GIA_ADVANCED_REFERENCING_DEBUG
			cout << "(foundAtLeastOneMatch) xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" << endl;
			cout << "numberOfMatchedNodesTemp = " << numberOfMatchedNodesTemp << endl;
			cout << "networkEntityWithMaxNumberNodesMatched->entityName = " << networkEntityWithMaxNumberNodesMatched->entityName << endl;
			#endif
			#ifdef GIA_ADVANCED_REFERENCING_DEBUG_SIMPLE2
			cout << "(foundAtLeastOneMatch) xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" << endl;
			cout << "numberOfMatchedNodesTemp = " << numberOfMatchedNodesTemp << endl;
			cout << "networkEntityWithMaxNumberNodesMatched->entityName = " << networkEntityWithMaxNumberNodesMatched->entityName << endl;
			#endif

			//now set the matched nodes as already passed (required such that they are not retraced...)
			#ifdef GIA_ADVANCED_REFERENCING_DEBUG
			queryTraceParameters.level = 0;
			#endif
			#ifdef GIA_QUERY_SIMPLIFIED_SEARCH_REPLACE_ADVANCED_SEARCH
			bool result = testEntityNodeForQueryOrReferenceSet2(queryEntityWithMaxNumberNodesMatched, networkEntityWithMaxNumberNodesMatched, &numberOfMatchedNodesTemp, true, &numberOfMatchedNodesRequiredSynonymnDetectionTemp, TRACE_MODE_IS_QUERY_FALSE, &queryTraceParameters, &referenceTraceParameters);
			#else
			bool result = testEntityNodeForQueryOrReferenceSet(queryEntityWithMaxNumberNodesMatched, networkEntityWithMaxNumberNodesMatched, &numberOfMatchedNodesTemp, true, &numberOfMatchedNodesRequiredSynonymnDetectionTemp, TRACE_MODE_IS_QUERY_FALSE, &queryTraceParameters, &referenceTraceParameters);
			#endif

			//#ifdef GIA_USE_ADVANCED_REFERENCING	//assumed true
			//required to set entityCorrespondingBestMatch of  the first node (networkIndex) in the reference set trace. This should not be required as networkIndex entity nodes of the same name (ie not pronouns) don't need referencing... It is just done for algorithmic consistency sake (considering other networkIndex nodes in the reference set trace will have their entityCorrespondingBestMatch value set)
			queryEntityWithMaxNumberNodesMatched->entityCorrespondingBestMatch = networkEntityWithMaxNumberNodesMatched;		//this shouldn't be required for queries....
			//#endif

			#ifdef GIA_ADVANCED_REFERENCING_DEBUG
			cout << "(foundAtLeastOneMatch)" << endl;
			cout << "numberOfMatchedNodesTemp = " << numberOfMatchedNodesTemp << endl;
			#endif
			#ifdef GIA_ADVANCED_REFERENCING_DEBUG_SIMPLE2
			cout << "(foundAtLeastOneMatch)" << endl;
			cout << "numberOfMatchedNodesTemp = " << numberOfMatchedNodesTemp << endl;
			#endif

			//now reset the matched nodes as unpassed (required such that they are retracable using a the different path)
			int irrelevantInt;
			string irrelevantString = "";
			bool traceInstantiations = GIA_QUERY_TRACE_NETWORK_INDEX_NODES_DEFINING_INSTANTIATIONS_VALUE;
			#ifdef GIA_USE_1N1ATEMP1TO8_CHANGES
			traceEntityNode(queryEntityWithMaxNumberNodesMatched, GIA_QUERY_TRACE_ENTITY_NODES_FUNCTION_RESET_TESTEDFORQUERYCOMPARISONTEMP, &irrelevantInt, &irrelevantString, false, NULL, traceInstantiations);		//is this required?	//added 13 July 2012
			traceEntityNode(networkEntityWithMaxNumberNodesMatched, GIA_QUERY_TRACE_ENTITY_NODES_FUNCTION_RESET_TESTEDFORQUERYCOMPARISONTEMP, &irrelevantInt, &irrelevantString, false, NULL, traceInstantiations);					//added 13 July 2012
			#else
			traceEntityNode(queryEntityWithMaxNumberNodesMatched, GIA_QUERY_TRACE_ENTITY_NODES_FUNCTION_RESET_TESTEDFORQUERYCOMPARISON, &irrelevantInt, &irrelevantString, false, NULL, traceInstantiations);
			#endif

			//this routine should now record, for each query node, a corresponding (vector of) best match entity node [this 1-x mapping should be used in the final generation of GIACoreference* firstGIACoreferenceInList

			#ifdef GIA_ADVANCED_REFERENCING_SUPPORT_INTRASENTENCE_REFERENCING
			currentGIAcoreferenceInList = generateCoreferenceListBasedUponPreviouslyMatchedEntityNode(queryEntityWithMaxNumberNodesMatched, currentGIAcoreferenceInList, foundAtLeastOneMatchIntraSentence);
			#else
			currentGIAcoreferenceInList = generateCoreferenceListBasedUponPreviouslyMatchedEntityNode(queryEntityWithMaxNumberNodesMatched, currentGIAcoreferenceInList, BOOL_IRRELEVANT);
			#endif
			traceEntityNode(queryEntityWithMaxNumberNodesMatched, GIA_QUERY_TRACE_ENTITY_NODES_FUNCTION_RESET_TESTEDFORQUERYCOMPARISON, &irrelevantInt, &irrelevantString, false, NULL, true);					//added 15 July 2012	//changed traceInstantiations to true 13 October 2012
		}

		#ifdef GIA_ADVANCED_REFERENCING_DEBUG
		cout << "\nfinished reference trace round 2" << endl;
		#endif

		referenceSetID++;
	}

	#ifdef GIA_DATABASE_CLEAR_CACHE_EVERY_SENTENCE
	#ifdef GIA_USE_DATABASE
	if(getUseDatabase() == GIA_USE_DATABASE_TRUE_READ_ACTIVE)
	{
		clearDBentityNodesActiveListCompleteFastIndexDBcache();
	}
	#endif
	#endif
}


void createGIAcoreferenceInListBasedUponIdentifiedReferenceSet(unordered_map<string, GIAentityNode*>* entityNodesActiveListNetworkIndexesQuery, unordered_map<string, GIAentityNode*>* entityNodesActiveListNetworkIndexes, GIAreferenceTraceParameters* referenceTraceParameters, int* maxNumberOfMatchedNodes, GIAentityNode* *queryEntityWithMaxNumberNodesMatched, GIAentityNode* *networkEntityWithMaxNumberNodesMatched, bool* foundAtLeastOneMatch)
{
	int referenceSetID = referenceTraceParameters->referenceSetID;

	#ifdef GIA_ADVANCED_REFERENCING_DEBUG
	cout << "\ncreateGIAcoreferenceInListBasedUponIdentifiedReferenceSet(), referenceSetID = " << referenceSetID << endl;
	#endif

	GIAqueryTraceParameters queryTraceParameters;	//irrelevant

	unordered_map<string, GIAentityNode*>::iterator entityIterQuery = entityNodesActiveListNetworkIndexesQuery->begin();
	GIAentityNode* firstNodeNetworkIndexEntityNodesListQuery = entityIterQuery->second;

	for(entityIterQuery = entityNodesActiveListNetworkIndexesQuery->begin(); entityIterQuery != entityNodesActiveListNetworkIndexesQuery->end(); entityIterQuery++)
	{//for each node in query semantic net;

		GIAentityNode* currentQueryEntityNode = entityIterQuery->second;
		#ifdef GIA_QUERY_DO_NOT_SEARCH_DISABLED_NODES
		if(!(currentQueryEntityNode->disabled))
		{
		#endif

			#ifdef GIA_QUERY_SIMPLIFIED_SEARCH_ENFORCE_EXACT_MATCH
			int irrelevant;
			string printEntityNodeString = "";
			int maxNumberOfMatchedNodesPossible = 0;
			bool traceInstantiations = GIA_QUERY_TRACE_NETWORK_INDEX_NODES_DEFINING_INSTANTIATIONS_VALUE;
			traceEntityNode(currentQueryEntityNode, GIA_QUERY_TRACE_ENTITY_NODES_FUNCTION_DETERMINE_MAX_NUMBER_MATCHED_NODES_SAME_SET_ONLY, &maxNumberOfMatchedNodesPossible, NULL, false, referenceSetID, traceInstantiations);
			traceEntityNode(currentQueryEntityNode, GIA_QUERY_TRACE_ENTITY_NODES_FUNCTION_RESET_TESTEDFORQUERYCOMPARISONTEMP, &irrelevant, &printEntityNodeString, false, NULL, traceInstantiations);
			#endif

			#ifdef GIA_ADVANCED_REFERENCING_DEBUG
			cout << "LDreference Set Trace Start: currentQueryEntityNode->entityName = " << currentQueryEntityNode->entityName << endl;
			#endif

			/*
			//removed 15 July 2012 - networkIndex entities do not have assigned referenceSetIDs [as there may be more than one instance of a networkIndex entity, each having a different reference set id (all within a given sentence)]
			#ifdef GIA_ADVANCED_REFERENCING_DEBUG
			cout << "currentQueryEntityNode->referenceSetID = " << currentQueryEntityNode->referenceSetID << endl;
			cout << "referenceSetID = " << referenceSetID << endl;
			#endif
			if(currentQueryEntityNode->referenceSetID == referenceSetID)
			{
			*/
				bool saveNetwork = false;
				bool foundQueryEntityNodeName = false;
				long queryEntityNodeIndex = -1;
				string queryEntityNodeName = currentQueryEntityNode->entityName;
				#ifdef GIA_ADVANCED_REFERENCING_DEBUG
				cout << "referenceSetID = " << referenceSetID << endl;
				#endif

				GIAentityNode* networkIndexEntityMatchingCurrentQueryEntity = findOrAddNetworkIndexEntityNodeByName(NULL, entityNodesActiveListNetworkIndexes, &queryEntityNodeName, &foundQueryEntityNodeName, &queryEntityNodeIndex, false, NULL, NULL, false);

				if(foundQueryEntityNodeName)
				{

					#ifdef GIA_ADVANCED_REFERENCING_DEBUG
					cout << "\tcreateGIAcoreferenceInListBasedUponIdentifiedReferenceSet: entityNode = " << currentQueryEntityNode->entityName << endl;
					//cout << "\tfoundQueryEntityNodeName" << endl;
					//cout << "\tcurrentQueryEntityNode->entityName = " << currentQueryEntityNode->entityName << endl;
					//cout << "\tnetworkIndexEntityMatchingCurrentQueryEntity->entityName = " << networkIndexEntityMatchingCurrentQueryEntity->entityName << endl;
					//cout << "currentQueryEntityNode->isNetworkIndex = " << currentQueryEntityNode->isNetworkIndex << endl;
					//cout << "networkIndexEntityMatchingCurrentQueryEntity->isNetworkIndex = " << networkIndexEntityMatchingCurrentQueryEntity->isNetworkIndex << endl;
					#endif

					//now start matching structure search for all substances of the identical networkIndex node (to current query entity name) in Semantic Network

					int numberOfMatchedNodesTemp = 0;
					int numberOfMatchedNodesRequiredSynonymnDetectionTemp = 0;
					#ifdef GIA_ADVANCED_REFERENCING_DEBUG
					queryTraceParameters.level = 0;
					#endif
					#ifdef GIA_QUERY_SIMPLIFIED_SEARCH_REPLACE_ADVANCED_SEARCH
					bool exactMatch = testEntityNodeForQueryOrReferenceSet2(currentQueryEntityNode, networkIndexEntityMatchingCurrentQueryEntity, &numberOfMatchedNodesTemp, false, &numberOfMatchedNodesRequiredSynonymnDetectionTemp, TRACE_MODE_IS_QUERY_FALSE, &queryTraceParameters, referenceTraceParameters);
					#else
					bool exactMatch = testEntityNodeForQueryOrReferenceSet(currentQueryEntityNode, networkIndexEntityMatchingCurrentQueryEntity, &numberOfMatchedNodesTemp, false, &numberOfMatchedNodesRequiredSynonymnDetectionTemp, TRACE_MODE_IS_QUERY_FALSE, &queryTraceParameters, referenceTraceParameters);
					#endif

					bool matchFound = false;
					if(referenceTraceParameters->traceMode == TRACE_MODE_ONLY_RECORD_EXACT_MATCH)
					{
						if(exactMatch)
						{
							#ifdef GIA_ADVANCED_REFERENCING_DEBUG
							cout << "exactMatch trace found" << endl;
							cout << "numberOfMatchedNodesTemp = " << numberOfMatchedNodesTemp << endl;
							#endif
							matchFound = true;
						}
					}
					else
					{
						matchFound = true;
					}
					if(matchFound)
					{
						#ifdef GIA_ADVANCED_REFERENCING_SUPPORT_INTRASENTENCE_REFERENCING
						if((numberOfMatchedNodesTemp >= *maxNumberOfMatchedNodes) && (numberOfMatchedNodesTemp > 1))		//this is required		//NB need to match > 1 nodes (ie, not just match the networkIndex node)
						#else
						if(numberOfMatchedNodesTemp >* maxNumberOfMatchedNodes)
						#endif
						{
							#ifdef GIA_QUERY_SIMPLIFIED_SEARCH_ENFORCE_EXACT_MATCH
							cout << "maxNumberOfMatchedNodesPossible = " << maxNumberOfMatchedNodesPossible << endl;
							cout << "numberOfMatchedNodesTemp = " << numberOfMatchedNodesTemp << endl;
							if(numberOfMatchedNodesTemp == maxNumberOfMatchedNodesPossible)
							{
							#endif
								*foundAtLeastOneMatch = true;

								*maxNumberOfMatchedNodes = numberOfMatchedNodesTemp;
								*queryEntityWithMaxNumberNodesMatched = currentQueryEntityNode;
								*networkEntityWithMaxNumberNodesMatched = networkIndexEntityMatchingCurrentQueryEntity;

								#ifdef GIA_ADVANCED_REFERENCING_DEBUG
								cout << "\t\t numberOfMatchedNodesTemp = " << numberOfMatchedNodesTemp << endl;
								cout << "\t\t queryEntityWithMaxNumberNodesMatched->entityName = " << (*queryEntityWithMaxNumberNodesMatched)->entityName << endl;
								cout << "\t\t networkEntityWithMaxNumberNodesMatched->entityName = " << (*networkEntityWithMaxNumberNodesMatched)->entityName << endl;
								#endif

							#ifdef GIA_QUERY_SIMPLIFIED_SEARCH_ENFORCE_EXACT_MATCH
							}
							#endif
						}
					}

					//now reset the matched nodes as unpassed (required such that they are retracable using a the different path)
					int irrelevantInt;
					string irrelevantString = "";
					bool traceInstantiations = GIA_QUERY_TRACE_NETWORK_INDEX_NODES_DEFINING_INSTANTIATIONS_VALUE;
					traceEntityNode(currentQueryEntityNode, GIA_QUERY_TRACE_ENTITY_NODES_FUNCTION_RESET_TESTEDFORQUERYCOMPARISONTEMP, &irrelevantInt, &irrelevantString, false, NULL, traceInstantiations);
					traceEntityNode(networkIndexEntityMatchingCurrentQueryEntity, GIA_QUERY_TRACE_ENTITY_NODES_FUNCTION_RESET_TESTEDFORQUERYCOMPARISONTEMP, &irrelevantInt, &irrelevantString, false, NULL, traceInstantiations);
				}
			/*
			}
			*/
		#ifdef GIA_QUERY_DO_NOT_SEARCH_DISABLED_NODES
		}
		#endif
	}
}

GIACoreference* generateCoreferenceListBasedUponPreviouslyMatchedEntityNode(GIAentityNode* entityNode, GIACoreference* currentGIAcoreferenceInList, bool intrasentenceReference)
{
	bool pass = false;
	if(!(entityNode->testedForQueryComparison))
	{
		#ifdef GIA_ADVANCED_REFERENCING_DEBUG
		cout << "generateCoreferenceListBasedUponPreviouslyMatchedEntityNode{}: entityNode being traced: = " << entityNode->entityName << endl;
		#endif

		if(entityNode->entityCorrespondingBestMatch != NULL)
		{
			if(!(entityNode->entityNodeDefiningThisInstance->empty()))
			{//do not reference networkIndex entities - condition added 16 July 2012

				#ifdef GIA_ADVANCED_REFERENCING_DEBUG
				cout << "\taddingEntityCorrespondingBestMatch. entityNode being traced: = " << entityNode->entityName << endl;
				cout << "entityNode->entityName = " << entityNode->entityName << endl;
				cout << "entityNode->entityCorrespondingBestMatch->entityName = " << entityNode->entityCorrespondingBestMatch->entityName << endl;
				cout << "entityNode->entityCorrespondingBestMatch->idInstance = " << entityNode->entityCorrespondingBestMatch->idInstance << endl;
				cout << "entityNode->entityIndexTemp = " << entityNode->entityIndexTemp << endl;
				#endif


				//now add the GIAcoReference to the list...
				GIAMention* sourceMention = currentGIAcoreferenceInList->firstMentionInList;
				sourceMention->representative = true;
				sourceMention->idActiveList = entityNode->entityCorrespondingBestMatch->idActiveList;
				sourceMention->entityIndex = entityNode->entityCorrespondingBestMatch->entityIndexTemp; 	//this is only used for intrasentence references
				sourceMention->entityName = entityNode->entityCorrespondingBestMatch->entityName;

				#ifdef GIA_ADVANCED_REFERENCING_DEBUG_SIMPLE2
				cout << "\taddingEntityCorrespondingBestMatch. entityNode being traced: = " << entityNode->entityName << endl;
				cout << "entityNode->entityName = " << entityNode->entityName << endl;
				cout << "entityNode->entityCorrespondingBestMatch->entityName = " << entityNode->entityCorrespondingBestMatch->entityName << endl;
				cout << "entityNode->entityCorrespondingBestMatch->idInstance = " << entityNode->entityCorrespondingBestMatch->idInstance << endl;
				cout << "entityNode->entityIndexTemp = " << entityNode->entityIndexTemp << endl;
				cout << "sourceMention->entityName = " << sourceMention->entityName << endl;
				#endif


				GIAMention* referenceMention = new GIAMention();
				referenceMention->representative = false;
				referenceMention->idActiveList = entityNode->idActiveList;
				#ifdef GIA_ADVANCED_REFERENCING_DEBUG
				//cout << "\t\t entityNode->entityIndexTemp = " << entityNode->entityIndexTemp << endl;
				#endif
				referenceMention->entityIndex = entityNode->entityIndexTemp;
				referenceMention->entityName = entityNode->entityName;

				#ifdef GIA_ADVANCED_REFERENCING_SUPPORT_INTRASENTENCE_REFERENCING
				if(intrasentenceReference)
				{
					sourceMention->intrasentenceReference = true;
					referenceMention->intrasentenceReference = true;
					#ifdef GIA_ADVANCED_REFERENCING_DEBUG
					//cout << "sourceMention->entityIndex = " << sourceMention->entityIndex << endl;
					#endif
				}
				#endif
				sourceMention->next = referenceMention;

				GIAMention* newMention  = new GIAMention();
				referenceMention->next = newMention;

				GIACoreference* newCoreference = new GIACoreference();
				currentGIAcoreferenceInList->next = newCoreference;
				currentGIAcoreferenceInList = currentGIAcoreferenceInList->next;
			}
		}

		entityNode->testedForQueryComparison = true;

		for(int i=0; i<GIA_ENTITY_NUMBER_OF_VECTOR_CONNECTION_TYPES; i++)
		{
			for(vector<GIAentityConnection*>::iterator connectionIter = entityNode->entityVectorConnectionsArray[i].begin(); connectionIter != entityNode->entityVectorConnectionsArray[i].end(); connectionIter++)
			{
				#ifdef GIA_ADVANCED_REFERENCING_SUPPORT_INTRASENTENCE_REFERENCING
				currentGIAcoreferenceInList = generateCoreferenceListBasedUponPreviouslyMatchedEntityNode((*connectionIter)->entity, currentGIAcoreferenceInList, intrasentenceReference);
				#else
				currentGIAcoreferenceInList = generateCoreferenceListBasedUponPreviouslyMatchedEntityNode((*connectionIter)->entity, currentGIAcoreferenceInList, BOOL_IRRELEVANT);
				#endif
			}
		}
	}

	#ifdef GIA_ADVANCED_REFERENCING_DEBUG
	cout << "exit: generateCoreferenceListBasedUponPreviouslyMatchedEntityNode{}" << endl;
	#endif

	return currentGIAcoreferenceInList;

}




void linkAdvancedReferencesGIA(GIAsentence* currentSentenceInList, bool GIAentityNodeArrayFilled[], GIAentityNode* GIAentityNodeArray[], unordered_map<string, GIAentityNode*>* entityNodesActiveListNetworkIndexes, GIACoreference* firstCoreferenceInList, GIAfeature* featureArrayTemp[], GIAentityNode* GIAfeatureTempEntityNodeArray[], GIAentityNode* GIAnetworkIndexNodeArray[])
{
	#ifdef GIA_ADVANCED_REFERENCING_DEBUG
	cout << "linkAdvancedReferencesGIA{}" << endl;
	#endif
	GIACoreference* currentCoreferenceInList = firstCoreferenceInList;
	while(currentCoreferenceInList->next != NULL)
	{
		#ifdef GIA_ADVANCED_REFERENCING_DEBUG
		cout << "currentCoreferenceInList" << endl;
		#endif

		if(currentCoreferenceInList->firstMentionInList != NULL)
		{
			GIAMention* firstMentionInList = currentCoreferenceInList->firstMentionInList;

			GIAMention* currentMentionInList = firstMentionInList;
			GIAMention* sourceMentionInList = NULL;
			GIAentityNode* referenceSource = NULL;
			#ifdef GIA_ADVANCED_REFERENCING_PREVENT_DOUBLE_LINKS
			GIAentityNode* referenceSourceNetworkIndex = NULL;
			#endif
			bool foundReferenceSource = false;
			int intrasentenceReferenceSourceIndex = -1;
			while(currentMentionInList->next != NULL)
			{
				#ifdef GIA_ADVANCED_REFERENCING_DEBUG
				cout << "currentMentionInList" << endl;
				cout << "currentMentionInList->idActiveList = " << currentMentionInList->idActiveList << endl;
				cout << "currentMentionInList->entityName = " << currentMentionInList->entityName << endl;
				cout << "currentMentionInList->entityIndex = " << currentMentionInList->entityIndex << endl;
				#endif

				if(!foundReferenceSource)
				{
					#ifdef GIA_DEBUG
					//cout << "!foundReferenceSource" << endl;
					#endif

					if(currentMentionInList->representative)
					{
						#ifdef GIA_DEBUG
						//cout << "(currentMentionInList->representative)" << endl;
						#endif

						#ifdef GIA_ADVANCED_REFERENCING_SUPPORT_INTRASENTENCE_REFERENCING
						if(currentMentionInList->intrasentenceReference)
						{
							int referenceSourceEntityIndex = currentMentionInList->entityIndex;
							//referenceSource = GIAentityNodeArray[referenceSourceEntityIndex];
							intrasentenceReferenceSourceIndex = referenceSourceEntityIndex;
							foundReferenceSource = true;
							#ifdef GIA_ADVANCED_REFERENCING_DEBUG
							cout << "\t\t referenceSourceEntityIndex->entityIndexTemp = " << referenceSourceEntityIndex << endl;
							#endif
						}
						else
						{
						#endif
							bool entityNameFound = false;
							#ifdef GIA_DEBUG
							//cout << "findOrAddNetworkIndexEntityNodeByNameSimpleWrapper" << endl;
							#endif

							GIAentityNode* referenceSourceNetworkIndexEntity = findOrAddNetworkIndexEntityNodeByNameSimpleWrapper(&(currentMentionInList->entityName), &entityNameFound, entityNodesActiveListNetworkIndexes);
							if(entityNameFound)
							{
								#ifdef GIA_DEBUG
								//cout << "entityNameFound" << endl;
								#endif
								#ifdef GIA_SUPPORT_MORE_THAN_ONE_NODE_DEFINING_AN_INSTANCE	//should this condition be enforced?
								#ifdef GIA_USE_DATABASE
								#ifndef GIA_DATABASE_TEST_MODE_LOAD_ALL_ENTITIES_AND_CONNECTIONS_TO_ACTIVE_LIST_UPON_READ
								if(getUseDatabase() == GIA_USE_DATABASE_TRUE_READ_ACTIVE)
								{
									DBreadVectorConnections(referenceSourceNetworkIndexEntity, GIA_ENTITY_VECTOR_CONNECTION_TYPE_ASSOCIATED_INSTANCES);		//read the associated instance vector connections from the database for the networkIndex node of the reference node (which has not necessarily already been loaded in the case of GIA_SUPPORT_MORE_THAN_ONE_NODE_DEFINING_AN_INSTANCE) - enabling the reference node to be found linkAdvancedReferencesGIA (added 28 November 2012b)
								}
								#endif
								#endif
								#endif

								//now find the substance in the referenceSource networkIndex entity that matches the referenceSource idActiveList (there is no networkIndex linking; as networkIndex nodes are identical for reference and referenceSource)
								for(vector<GIAentityConnection*>::iterator connectionIter = referenceSourceNetworkIndexEntity->associatedInstanceNodeList->begin(); connectionIter != referenceSourceNetworkIndexEntity->associatedInstanceNodeList->end(); connectionIter++)
								{
									GIAentityNode* instance = (*connectionIter)->entity;

									#ifdef GIA_ADVANCED_REFERENCING_DEBUG
									cout << "\t\t referenceSource->entityIndexTemp = " << instance->entityIndexTemp << endl;
									cout << "\t\t referenceSource->sentenceIndexTemp = " << instance->sentenceIndexTemp << endl;
									#endif

									if(instance->idActiveList == currentMentionInList->idActiveList)		//NB these activeList IDs [idActiveList] are not official - they are only used for referencing - and are overwritten
									{
										#ifdef GIA_ADVANCED_REFERENCING_DEBUG
										cout << "foundReferenceSource: instance->entityName = " << instance->entityName << endl;
										cout << "foundReferenceSource: instance->idActiveList = " << instance->idActiveList << endl;
										cout << "foundReferenceSource: instance->idInstance = " << instance->idInstance << endl;
										#endif
										#ifdef GIA_ADVANCED_REFERENCING_DEBUG_SIMPLE2
										cout << "foundReferenceSource: instance->entityName = " << instance->entityName << endl;
										cout << "foundReferenceSource: instance->idActiveList = " << instance->idActiveList << endl;
										cout << "foundReferenceSource: instance->idInstance = " << instance->idInstance << endl;
										#endif

										referenceSource = instance;
										#ifdef GIA_ADVANCED_REFERENCING_PREVENT_DOUBLE_LINKS
										referenceSourceNetworkIndex = referenceSourceNetworkIndexEntity;
										#endif
										foundReferenceSource = true;
										sourceMentionInList = currentMentionInList;

										//#ifdef GIA_SUPPORT_MORE_THAN_ONE_NODE_DEFINING_AN_INSTANCE	//should this condition be enforced?
										#ifdef GIA_USE_DATABASE
										#ifndef GIA_DATABASE_TEST_MODE_LOAD_ALL_ENTITIES_AND_CONNECTIONS_TO_ACTIVE_LIST_UPON_READ
										if(getUseDatabase() == GIA_USE_DATABASE_TRUE_READ_ACTIVE)
										{
											for(int i=0; i<GIA_ENTITY_NUMBER_OF_VECTOR_CONNECTION_TYPES; i++)
											{
												DBreadVectorConnections(referenceSource, i);	//read all vector connections for the reference (this is required because writeVectorConnection() presumes entityVectorConnectionsReferenceListLoadedArray[i] to be true in all cases - ie, in case the reference is ammended with new connections by GIATranslator which it is very likely to be the case) (added 28 November 2012b)
											}
										}
										#endif
										#endif
										//#endif
									}
								}
							}
						#ifdef GIA_ADVANCED_REFERENCING_SUPPORT_INTRASENTENCE_REFERENCING
						}
						#endif
					}
				}

				if(foundReferenceSource)
				{
					#ifdef GIA_ADVANCED_REFERENCING_DEBUG
					//cout << "foundReferenceSource" << endl;
					#endif

					if(!(currentMentionInList->representative))
					{//continue only for references, eg pronoun (not for their source, eg name)

						#ifdef GIA_ADVANCED_REFERENCING_SUPPORT_INTRASENTENCE_REFERENCING
						if(currentMentionInList->intrasentenceReference)
						{
							int referenceEntityIndex = currentMentionInList->entityIndex;

							//create a new substance and share it between the reference and the reference source
							/*Removed 1 October 2013
							#ifdef GIA_RECORD_WAS_REFERENCE_INFORMATION
							GIAentityNodeArray[referenceEntityIndex]->wasReference = true;	//assign to networkIndex
							#endif
							#ifdef GIA_ADVANCED_REFERENCING_PREVENT_DOUBLE_LINKS
							GIAentityNodeArray[referenceEntityIndex]->wasReferenceTemp = true;
							#endif
							*/
							GIAentityNodeArray[referenceEntityIndex] = addInstanceToInstanceDefinition(GIAentityNodeArray[referenceEntityIndex], GIA_ENTITY_TYPE_TYPE_SUBSTANCE);
							GIAentityNodeArray[intrasentenceReferenceSourceIndex] = GIAentityNodeArray[referenceEntityIndex];

							/*Removed GIA 2f7a - 06 July 2014 (wasReference is only used for intersentence references)
							#ifdef GIA_RECORD_WAS_REFERENCE_INFORMATION
							GIAentityNodeArray[intrasentenceReferenceSourceIndex]->wasReference = true;	//added 1 October 2013
							#endif
							*/
							/*Removed 1 October 2013
							#ifdef GIA_ADVANCED_REFERENCING_PREVENT_DOUBLE_LINKS
							GIAentityNodeArray[intrasentenceReferenceSourceIndex]->wasReferenceTemp = true;	//added 1 October 2013
							#endif
							*/

							#ifdef GIA_ADVANCED_REFERENCING_DEBUG
							cout << "!(currentMentionInList->representative): currentMentionInList->entityName = " << currentMentionInList->entityName << endl;
							cout << "referenceEntityIndex = " << referenceEntityIndex << endl;
							cout << "intrasentenceReferenceSourceIndex = " << intrasentenceReferenceSourceIndex << endl;
							#endif

							#ifdef GIA_ADVANCED_REFERENCING_DEBUG_SIMPLE
							cout << "linkAdvancedReferencesGIA: GIAentityNodeArray[referenceEntityIndex]->entityName = " << GIAentityNodeArray[referenceEntityIndex]->entityName << endl;
							cout << "linkAdvancedReferencesGIA: GIAentityNodeArray[intrasentenceReferenceSourceIndex]->entityName = " << GIAentityNodeArray[intrasentenceReferenceSourceIndex]->entityName << endl;
							#endif
						}
						else
						{
						#endif
							#ifdef GIA_DEBUG
							//cout << "!intrasentenceReference" << endl;
							#endif
							int referenceEntityIndex = currentMentionInList->entityIndex;

							#ifdef GIA_ADVANCED_REFERENCING_DEBUG
							cout << "!(currentMentionInList->representative): currentMentionInList->entityName = " << currentMentionInList->entityName << endl;
							cout << "referenceEntityIndex = " << referenceEntityIndex << endl;
							#endif

							/*//2f19a 23-July-2014:
							#ifndef GIA_TRANSLATOR_ONLY_MERGE_ENTITY_NODES_WHEN_LINK_PREESTABLISHED_REFERENCES_GIA
							//copy reference aliases to referenceSource
							//required for; A red dog is fat. The name of the red dog is Tom.
							GIAentityNode* reference = GIAentityNodeArray[referenceEntityIndex];
							#ifdef GIA_ADVANCED_REFERENCING_DEBUG_SIMPLE2
							cout << "reference->entityName = " << reference->entityName << endl;
							#endif
							if(reference->entityType == GIA_ENTITY_TYPE_TYPE_NETWORK_INDEX)
							{
								cout << "linkAdvancedReferencesGIA{}: reference->isNetworkIndex" << endl;
							}
							if(reference->entityName != referenceSource->entityName)	//this may be required because the reference (with referenceEntityIndex as established by advanced referencing) is still a networkIndex and has not a substance created	//this will be required depending on which node was declared the primary (alias or non alias) when the  entities where merged during the temporary execution of convertSentenceSemanticRelationsIntoGIAnetworkNodes() on the sentence (sentenceNetworkIndexEntityNodesList) for the creation of GIA advanced referencing coreference sets
							{//advanced referencing has found an alias for the reference, merge it with the referenceSource
								referenceSource->aliasList.push_back(reference->entityName);
								#ifdef GIA_ADVANCED_REFERENCING_DEBUG_SIMPLE2
								cout << "linkAdvancedReferencesGIA{}: add reference name (alias) to reference source alias list: " << reference->entityName << endl;
								#endif
							}
							//for(int i((reference->aliasList).size() > 0)
							for(vector<string>::iterator aliasIter = reference->aliasList.begin(); aliasIter != reference->aliasList.end(); aliasIter++)	//this will be required depending on which node was declared the primary (alias or non alias) when the  entities where merged during the temporary execution of convertSentenceSemanticRelationsIntoGIAnetworkNodes() on the sentence (sentenceNetworkIndexEntityNodesList) for the creation of GIA advanced referencing coreference sets
							{//advanced referencing has found an alias for the reference, merge it with the referenceSource
								string referenceAlias = *aliasIter;
								#ifdef GIA_ADVANCED_REFERENCING_DEBUG_SIMPLE2
								cout << "referenceAlias = " << referenceAlias << endl;
								#endif
								if(referenceAlias != referenceSource->entityName)
								{
									referenceSource->aliasList.push_back(referenceAlias);
									#ifdef GIA_ADVANCED_REFERENCING_DEBUG_SIMPLE2
									cout << "linkAdvancedReferencesGIA{}: add reference alias to reference source alias list: " << referenceAlias << endl;
									#endif
								}
							}
							//what about; A red dog is fat. The name of the red dog is Tom. Tom rides the bike. (merge must copy aliases across)
							#endif
							*/

							#ifdef GIA_ADVANCED_REFERENCING_PREPOSITIONS
							if(GIAentityNodeArrayFilled[referenceEntityIndex])
							{
							#endif
								#ifdef GIA_ADVANCED_REFERENCING_DEBUG
								cout << "linkAdvancedReferencesGIA: reference->entityName = " << GIAentityNodeArray[referenceEntityIndex]->entityName << endl;
								#endif
							#ifdef GIA_ADVANCED_REFERENCING_PREPOSITIONS
							}
							else
							{
								GIAentityNodeArrayFilled[referenceEntityIndex] = true;	//preposition reference
								GIAfeatureTempEntityNodeArray[referenceEntityIndex] = referenceSource;		//added for GIA 1n7c 31-July-2012 to correct bug as resultant of advanced referencing - fill in array
								featureArrayTemp[referenceEntityIndex] = new GIAfeature();				//added for GIA 1n7c 31-July-2012 to correct bug as resultant of advanced referencing - fill in array
								GIAnetworkIndexNodeArray[referenceEntityIndex] = referenceSource;			//added for GIA 1n7c 31-July-2012 to correct bug as resultant of advanced referencing - fill in array
							}
							#endif


							GIAentityNodeArray[referenceEntityIndex] = referenceSource;
							#ifdef GIA_ADVANCED_REFERENCING_PREVENT_DOUBLE_LINKS
							referenceSource->wasReferenceTemp = true;
							#endif
							#ifdef GIA_RECORD_WAS_REFERENCE_INFORMATION
							referenceSource->wasReference = true;
							#ifdef GIA_ADVANCED_REFERENCING_PREVENT_DOUBLE_LINKS
							referenceSourceNetworkIndex->wasReference = true;
							#endif
							#endif
							#ifdef GIA_SUPPORT_PREDETERMINERS
							if(referenceSource->grammaticalPredeterminerTemp == GRAMMATICAL_PREDETERMINER_UNDEFINED)
							{
								referenceSource->grammaticalPredeterminerTemp = featureArrayTemp[referenceEntityIndex]->grammaticalPredeterminer;	//only update the default (sentence independent) predeterminer of reference if no predeterminer found previously - NB the default (sentence independent) predeterminer is used by GIAxmlConversion only at present and shouldnt be used at all by !GIA_DISABLE_CROSS_SENTENCE_REFERENCING
							}
							#ifndef GIA_DISABLE_CROSS_SENTENCE_REFERENCING
							referenceSource->grammaticalPredeterminerTempSentenceArray.insert(make_pair(currentSentenceInList->sentenceIndex, featureArrayTemp[referenceEntityIndex]->grammaticalPredeterminer));	//added 2i34a
							#endif
							#endif

							#ifdef GIA_ADVANCED_REFERENCING_DEBUG_SIMPLE
							cout << "linkAdvancedReferencesGIA: referenceSource->entityName = " << referenceSource->entityName << endl;
							cout << "linkAdvancedReferencesGIA: GIAentityNodeArray[referenceEntityIndex]->entityName = " << GIAentityNodeArray[referenceEntityIndex]->entityName << endl;
							/*
							cout << "GIAentityNodeArray[referenceEntityIndex]->wasReferenceTemp = " << GIAentityNodeArray[referenceEntityIndex]->wasReferenceTemp << endl;
							if(GIAentityNodeArray[referenceEntityIndex]->entityType == GIA_ENTITY_TYPE_TYPE_SUBSTANCE)
							{
								cout << "GIAentityNodeArray[referenceEntityIndex]->isSubstance" << endl;
							}
							*/
							#endif


							#ifdef GIA_USE_DATABASE
							if(getUseDatabase() == GIA_USE_DATABASE_TRUE_READ_ACTIVE)
							{
								bool foundReferenceSourceInActiveList = false;
								GIAentityNode* tempNode = findEntityNodesActiveListCompleteFastIndexDBactive(&(referenceSource->entityName), referenceSource->idInstance, &foundReferenceSourceInActiveList);
								if(!foundReferenceSourceInActiveList)	//OR findEntityNodesActiveListCompleteFastIndexDBactive(referenceSource) OR if(!entityInActiveListComplete(referenceSource->entityName, referenceSource->idInstance))
								{
									addInstanceEntityNodeToActiveLists(referenceSource);
									//referenceSource->modified = true;	//used to re-write the node to the database (in case it has been updated)
								}
							}
							#endif

						#ifdef GIA_ADVANCED_REFERENCING_SUPPORT_INTRASENTENCE_REFERENCING
						}
						#endif


					}
				}

				currentMentionInList = currentMentionInList->next;
			}
		}
		currentCoreferenceInList = currentCoreferenceInList->next;
	}
}

#endif


#ifdef GIA_TRANSLATOR_DREAM_MODE_LINK_SPECIFIC_CONCEPTS_AND_ACTIONS
void identifyReferenceSetsSpecificConceptsAndLinkWithConcepts(vector<GIAentityNode*>* entityNodesActiveListComplete)
{
	#ifdef GIA_DREAMMODE_REFERENCING_DEBUG
	cout << "identifyReferenceSetsSpecificConceptsAndLinkWithConcepts" << endl;
	#endif
	int referenceSetID = 0;

	for(vector<GIAentityNode*>::iterator entityNodesActiveListCompleteIter = entityNodesActiveListComplete->begin(); entityNodesActiveListCompleteIter != entityNodesActiveListComplete->end(); entityNodesActiveListCompleteIter++)
	{
		GIAentityNode* currentSpecificConcept = *entityNodesActiveListCompleteIter;
		#ifdef GIA_DREAMMODE_REFERENCING_DEBUG
		cout << "\t identifyReferenceSetsSpecificConcepts currentSpecificConcept = : " << currentSpecificConcept->entityName << endl;
		#endif

		if(!(currentSpecificConcept->disabled))
		{
			if(currentSpecificConcept->entityType == GIA_ENTITY_TYPE_TYPE_CONCEPT)
			{//implies !(currentSpecificConcept->entityType == GIA_ENTITY_TYPE_TYPE_NETWORK_INDEX)
				#ifdef GIA_DREAMMODE_REFERENCING_DEBUG
				cout << "isConcept Found" << endl;
				#endif

				int minimumEntityIndexOfReferenceSet = currentSpecificConcept->entityIndexTemp;

				#ifdef GIA_DREAMMODE_REFERENCING_DEBUG
				cout << "minimumSentenceIndexOfReferenceSet1 = " << currentSpecificConcept->grammaticalIndexOfDeterminerTemp << endl;
				cout << "minimumSentenceIndexOfReferenceSet2 = " << currentSpecificConcept->entityIndexTemp << endl;
				#endif

				if(identifyReferenceSetDetermineNextCourseOfAction(currentSpecificConcept, true, referenceSetID, minimumEntityIndexOfReferenceSet, false))
				{
					bool traceModeIsQuery = false;

					GIAreferenceTraceParameters referenceTraceParameters;
					referenceTraceParameters.referenceSetID = referenceSetID;
					referenceTraceParameters.linkSpecificConceptsAndActions = true;

					#ifdef GIA_QUERY_SIMPLIFIED_SEARCH_ENFORCE_EXACT_MATCH
					int irrelevant;
					string printEntityNodeString = "";
					int maxNumberOfMatchedNodesPossible = 0;
					bool traceInstantiations = GIA_QUERY_TRACE_NETWORK_INDEX_NODES_DEFINING_INSTANTIATIONS_VALUE;
					traceEntityNode(firstNodeNetworkIndexEntityNodesListQuery, GIA_QUERY_TRACE_ENTITY_NODES_FUNCTION_DETERMINE_MAX_NUMBER_MATCHED_NODES_SAME_SET_ONLY, &maxNumberOfMatchedNodesPossible, NULL, false, referenceSetID, traceInstantiations);
					traceEntityNode(currentQueryEntityNode, GIA_QUERY_TRACE_ENTITY_NODES_FUNCTION_RESET_TESTEDFORQUERYCOMPARISONTEMP, &irrelevant, &printEntityNodeString, false, NULL, traceInstantiations);
					#endif

					for(vector<GIAentityNode*>::iterator entityNodesActiveListCompleteIter = entityNodesActiveListComplete->begin(); entityNodesActiveListCompleteIter != entityNodesActiveListComplete->end(); entityNodesActiveListCompleteIter++)
					{
						GIAentityNode* entityNode = *entityNodesActiveListCompleteIter;
						#ifdef GIA_DREAMMODE_REFERENCING_DEBUG
						cout << "\t identifyReferenceSetsSpecificConcepts: " << entityNode->entityName << endl;
						#endif

						if(!(entityNode->disabled))
						{
							if(!(entityNode->entityType == GIA_ENTITY_TYPE_TYPE_NETWORK_INDEX))
							{
								GIAqueryTraceParameters queryTraceParameters;		//not used

								int numberOfMatchedNodesTemp = 0;
								int numberOfMatchedNodesRequiredSynonymnDetectionTemp = 0;
								//bool exactMatch = testEntityNodeForQueryOrReferenceSet2(currentSpecificConcept, entityNode, &numberOfMatchedNodesTemp, false, &numberOfMatchedNodesRequiredSynonymnDetectionTemp, traceModeIsQuery, &queryTraceParameters, &referenceTraceParameters);
								bool exactMatch = testReferencedEntityNodeForExactNameMatch2(currentSpecificConcept, entityNode, &numberOfMatchedNodesTemp, false, &numberOfMatchedNodesRequiredSynonymnDetectionTemp, traceModeIsQuery, &queryTraceParameters, &referenceTraceParameters);

								if(exactMatch)
								{
									#ifdef GIA_DEBUG
									//cout << "exactMatch" << endl;
									#endif
									if(numberOfMatchedNodesTemp > 0)
									{
										#ifdef GIA_QUERY_SIMPLIFIED_SEARCH_ENFORCE_EXACT_MATCH
										if(numberOfMatchedNodesTemp == maxNumberOfMatchedNodesPossible)
										{
										#endif
											#ifdef GIA_RECORD_SAME_REFERENCE_SET_INFORMATION
											bool sameReferenceSet = false;
											#else
											bool sameReferenceSet = IRRELEVANT_SAME_REFERENCE_SET_VALUE_NO_ADVANCED_REFERENCING;
											#endif

											#ifdef GIA_TRANSLATOR_DREAM_MODE_LINK_SPECIFIC_CONCEPTS_AND_ACTIONS_ADVANCED
											if(entityNode->entityType == GIA_ENTITY_TYPE_TYPE_CONCEPT)
											{
												//eg3 Blue birds are tall. The happy eagle is a blue bird.
												#ifdef GIA_DEBUG
												//cout << "exactMatch: numberOfMatchedNodesTemp = " << numberOfMatchedNodesTemp << endl;
												//cout << "currentSpecificConcept = " << currentSpecificConcept->entityName << endl;
												//cout << "entityNode: = " << entityNode->entityName << endl;
												#endif

												/*
												//this method may not be appropriate for GIA_USE_ADVANCED_REFERENCING; if concepts advanced reference each other in the future:
												if(!(entityNode->entityNodeDefinitionReverseList->empty())
												{
													GIAentityNode* instanceEntity = (entityNode->entityNodeDefinitionReverseList->begin())->entity;	//take the first entity, and ensure its sentenceID is identical to that of its substance; indicated it was the original definition declared in the sentence

												}
												*/
												GIAentityNode* instanceEntity = NULL;;
												for(vector<GIAentityConnection*>::iterator definitionNodeReverseListIterator = entityNode->entityNodeDefinitionReverseList->begin(); definitionNodeReverseListIterator < entityNode->entityNodeDefinitionReverseList->end(); definitionNodeReverseListIterator++)
												{
													if((*definitionNodeReverseListIterator)->entity->sentenceIndexTemp == entityNode->sentenceIndexTemp)
													{
														instanceEntity = (*definitionNodeReverseListIterator)->entity;
														#ifdef GIA_DEBUG
														//cout << "instanceEntity = " << instanceEntity->entityName << endl;
														#endif
													}
												}
												if(instanceEntity != NULL)
												{
													addDefinitionToEntity(instanceEntity, currentSpecificConcept, sameReferenceSet);
													#ifdef GIA_DREAMMODE_REFERENCING_DEBUG
													cout << "identifyReferenceSetsSpecificConceptsAndLinkWithConcepts{}: addDefinitionToEntity" << endl;
													#endif
												}
											}
											else
											{
											#endif
												//eg1 Blue pies have bikes. The blue pie is happy.
												//eg2 The yellow banana is a fruit. The yellow fruit is tasty.

												//found instance in network matching concept...
												addDefinitionToEntity(entityNode, currentSpecificConcept, sameReferenceSet);
												#ifdef GIA_DREAMMODE_REFERENCING_DEBUG
												cout << "identifyReferenceSetsSpecificConceptsAndLinkWithConcepts{}: addDefinitionToEntity" << endl;
												cout << "entityNode = " << entityNode->entityName << endl;
												cout << "currentSpecificConcept = " << currentSpecificConcept->entityName << endl;
												cout << "numberOfMatchedNodesTemp = " << numberOfMatchedNodesTemp << endl;
												#endif
											#ifdef GIA_TRANSLATOR_DREAM_MODE_LINK_SPECIFIC_CONCEPTS_AND_ACTIONS_ADVANCED
											}
											#endif
										#ifdef GIA_QUERY_SIMPLIFIED_SEARCH_ENFORCE_EXACT_MATCH
										}
										#endif
									}
								}
								else
								{
									#ifdef GIA_DEBUG
									//cout << "!exactMatch" << endl;
									#endif
								}

								//now reset the matched nodes as unpassed (required such that they are retracable using a the different path)
								int irrelevant;
								string printEntityNodeString = "";
								bool traceInstantiations = GIA_QUERY_TRACE_NETWORK_INDEX_NODES_DEFINING_INSTANTIATIONS_VALUE;
								traceEntityNode(currentSpecificConcept, GIA_QUERY_TRACE_ENTITY_NODES_FUNCTION_RESET_TESTEDFORQUERYCOMPARISONTEMP, &irrelevant, &printEntityNodeString, false, NULL, traceInstantiations);
								traceEntityNode(entityNode, GIA_QUERY_TRACE_ENTITY_NODES_FUNCTION_RESET_TESTEDFORQUERYCOMPARISONTEMP, &irrelevant, &printEntityNodeString, false, NULL, traceInstantiations);
							}
						}
					}

					referenceSetID	= referenceSetID + 1;
				}
			}
		}
	}
}
#endif

#ifdef GIA_RECORD_SAME_REFERENCE_SET_INFORMATION
bool identifyReferenceSetDetermineNextCourseOfAction(GIAentityNode* entityNode, bool sameReferenceSet, int referenceSetID, int minimumEntityIndexOfReferenceSet, bool isProperty)
{
	bool result = false;
	if(sameReferenceSet)
	{
		bool referenceSetAlreadyAssigned = false;
		#ifdef GIA_USE_1N1ATEMP1TO8_CHANGES
		if(entityNode->referenceSetID != GIA_REFERENCE_SET_ID_UNDEFINED)		//do not retrace reference sets
		#else
		if(entityNode->referenceSetID == referenceSetID)				//do not retrace reference sets
		#endif
		{
			referenceSetAlreadyAssigned = true;
		}

		#ifdef GIA_ADVANCED_REFERENCING_DEBUG_INTRASENTENCE_EXTRA
		//if(entityNode->entityName == "fruit")
		//{
			cout << "\nentityNode->entityName = " << entityNode->entityName << endl;
			cout << "entityNode->referenceSetID = " << entityNode->referenceSetID << "(" << referenceSetAlreadyAssigned << ")" << endl;
			cout << "entityNode->entityType = " << entityNode->entityType << endl;
			cout << "minimumEntityIndexOfReferenceSet = " << minimumEntityIndexOfReferenceSet << endl;
			cout << "entityNode->entityIndexTemp = " << entityNode->entityIndexTemp << endl;
			cout << "entityNode->minimumEntityIndexOfReferenceSet = " << entityNode->minimumEntityIndexOfReferenceSet << endl;
		//}
		#endif

		bool pass = true;
		#ifdef GIA_ADVANCED_REFERENCING_ASSERT_MINIMUM_SENTENCE_INDEX_OF_REFERENCE_SET
		/*
		NB1 entityNode->minimumEntityIndexOfReferenceSet is only assigned when referenceSetAlreadyAssigned (referenceSetID != GIA_REFERENCE_SET_ID_UNDEFINED)
		NB2 (!referenceSetAlreadyAssigned || (minimumEntityIndexOfReferenceSet < entityNode->minimumEntityIndexOfReferenceSet)): only replace reference set id when definining an earlier (ie larger) reference set in the sentence
		NB3 (entityNode->entityIndexTemp >= minimumEntityIndexOfReferenceSet) || wasPropertyLink: all entities in reference set must occur after minimumEntityIndexOfReferenceSet in the sentence, unless it is a property eg "the blue cars"
		word order must be used carefully,
		eg1; "placed in the book of the house". For reference set to be assigned: (the node must not already be assigned a reference set OR the minimumEntityIndexOfReferenceSet is less than that used during the node's previous reference set assignment) AND the node must occur after minimumEntityIndexOfReferenceSet
		     imagine if house was parsed first by GIA which it is not;
		     eg reference set 1 identification: the house (!referenceSetAlreadyAssigned  && entityNode->entityIndexTemp >= minimumEntityIndexOfReferenceSet)
		     eg reference set 1 reidentification: the book of the house (referenceSetAlreadyAssigned for "house", but; minimumEntityIndexOfReferenceSet < entityNode->minimumEntityIndexOfReferenceSet && entityNode->entityIndexTemp >= minimumEntityIndexOfReferenceSet) {overwrites smaller reference set 'the house'}
		*/
		if(!(!referenceSetAlreadyAssigned || (minimumEntityIndexOfReferenceSet < entityNode->minimumEntityIndexOfReferenceSet)))
		{
			pass = false;
		}
		if(!((entityNode->entityIndexTemp >= minimumEntityIndexOfReferenceSet) || isProperty))
		{
			pass = false;
		}
		#ifdef GIA_SET_ENTITY_ENTITY_AND_SENTENCE_INDICIES_NORMALLY
		//added 2f19e 24-July-2014
		if(entityNode->entityType == GIA_ENTITY_TYPE_TYPE_NETWORK_INDEX)
		{
			pass = false;
		}
		#endif
		#else
		if(referenceSetAlreadyAssigned)
		{
			pass = false;
		}
		#endif
		#ifdef GIA_ADVANCED_REFERENCING_ENSURE_QUANTITY_MATCHES
		#ifdef GIA_SUPPORT_NUMBER_OF
		if(entityNode->isNumberOf)
		{
			pass = false;	//added 2m2b - do not create reference set for number of references (prevents gia advanced referencing of number of expressions, and enables gia advanced referencing of subexpressions eg "mountain" in "the number of blue birds near the mountain")
		}
		#endif		
		#endif
		if(pass)
		{
			#ifdef GIA_ADVANCED_REFERENCING_DEBUG_INTRASENTENCE_EXTRA
			cout << "\tpass" << endl;
			#endif
			result =  true;
			identifyReferenceSet(entityNode, referenceSetID, minimumEntityIndexOfReferenceSet);
		}
	}

	return result;
}

void identifyReferenceSet(GIAentityNode* entityNode, int referenceSetID, int minimumEntityIndexOfReferenceSet)
{
	#ifdef GIA_ADVANCED_REFERENCING_DEBUG
	cout << "identifyReferenceSet{}: entityNode being traced = " << entityNode->entityName << endl;
	cout << "identifyReferenceSet{}: referenceSetID = " << referenceSetID << endl;
	cout << "identifyReferenceSet{}: entityType = " << entityNode->entityType << endl;
	#endif
	#ifdef GIA_ADVANCED_REFERENCING_DEBUG_TOO_LARGE_REFERENCE_SET
	cout << "identifyReferenceSet{}: " << entityNode->entityName << endl;
	#endif

	entityNode->referenceSetID = referenceSetID;
	entityNode->minimumEntityIndexOfReferenceSet = minimumEntityIndexOfReferenceSet;

	#ifdef GIA_ADVANCED_REFERENCING_IDENTIFY_DEFINITE_SETS_ACCEPT_PROPERNOUNS_ISOLATE
	if(!(entityNode->grammaticalProperNounTemp))
	{
	#endif
		#ifdef GIA_DEBUG
		//cout << "\tentityNode->referenceSetID = " << entityNode->referenceSetID << endl;
		//cout << "\tentityNode->minimumEntityIndexOfReferenceSet = " << entityNode->minimumEntityIndexOfReferenceSet << endl;
		#endif
		for(int i=0; i<GIA_ENTITY_NUMBER_OF_VECTOR_CONNECTION_TYPES; i++)
		{
			if(!(entityNode->entityVectorConnectionsArray[i].empty()))
			{
				for(vector<GIAentityConnection*>::iterator connectionIter = entityNode->entityVectorConnectionsArray[i].begin(); connectionIter < entityNode->entityVectorConnectionsArray[i].end(); connectionIter++)
				{
					bool isProperty = false;
					if(i == GIA_ENTITY_VECTOR_CONNECTION_TYPE_PROPERTIES)
					{
						isProperty = true;
					}
					identifyReferenceSetDetermineNextCourseOfAction((*connectionIter)->entity, ((*connectionIter)->sameReferenceSet), referenceSetID, minimumEntityIndexOfReferenceSet, isProperty);
				}
			}
		}
	#ifdef GIA_ADVANCED_REFERENCING_IDENTIFY_DEFINITE_SETS_ACCEPT_PROPERNOUNS_ISOLATE
	}
	#endif
}
#endif


/*
	#ifdef GIA_ADVANCED_REFERENCING_PREVENT_DOUBLE_LINKS
	//required to reset wasReferenceTemp for next time
	for(int w=0; w<MAX_NUMBER_OF_WORDS_PER_SENTENCE; w++)
	{
		//cout << w << endl;
		if(GIAentityNodeArrayFilled[w])
		{
			if(GIAentityNodeArray[w]->wasReferenceTemp)
			{
				GIAentityNode* reference = GIAentityNodeArray[w];
				for(int i=0; i<GIA_ENTITY_NUMBER_OF_VECTOR_CONNECTION_TYPES; i++)
				{
					for(vector<GIAentityConnection*>::iterator connectionIter = reference->entityVectorConnectionsArray[i].begin(); connectionIter != reference->entityVectorConnectionsArray[i].end(); connectionIter++)
					{
						//connect reference ambient node to referenceSource
						GIAentityNode* entityConnectedToReference = (*connectionIter)->entity;
						if(entityConnectedToReference->wasReferenceTemp)
						{
							//disconnect reference sources from each other, as their connection between each other will be redeclared in current context
							int iInverted = inverseVectorConnectionsArray[i];
							for(vector<GIAentityConnection*>::iterator connectionIter2 = entityConnectedToReference->entityVectorConnectionsArray[iInverted].begin(); connectionIter2 != entityConnectedToReference->entityVectorConnectionsArray[iInverted].end(); connectionIter2++)
							{
								GIAentityNode* entityConnectedToEntityConnectedToReference = (*connectionIter2)->entity;
								if(reference->idActiveList == entityConnectedToEntityConnectedToReference->idActiveList)	//OR (reference == entityConnectedToEntityConnectedToReference)?
								{
									(*connectionIter2)->entity = referenceSource;
									#ifdef GIA_USE_DATABASE
									(*connectionIter2)->modified = true;
									//referenceSource->modified = true;		//this shouldnt be required...
									#endif
								}
							}

							//connect referenceSource to reference ambient node
							writeVectorConnection(referenceSource, entityConnectedToReference, i, (*connectionIter)->sameReferenceSet);

						}

						//connect referenceSource to reference ambient node
						writeVectorConnection(referenceSource, entityConnectedToReference, i, (*connectionIter)->sameReferenceSet);
					}
				}

				GIAentityNodeArray[w]->wasReferenceTemp = false;
			}
		}
	}

	//required to reset wasReferenceTemp for next time
	for(int w=0; w<MAX_NUMBER_OF_WORDS_PER_SENTENCE; w++)
	{
		//cout << w << endl;
		if(GIAentityNodeArrayFilled[w])
		{
			GIAentityNodeArray[w]->wasReferenceTemp = false;
		}
	}
	#endif
*/


/*
void identifyEntityTypesLocal(GIArelation* currentRelationInList, int NLPdependencyRelationsType, GIAentityNode* governor, GIAentityNode* dependent)
{
	//possessive of substances [NB plural/singular indicates definite noun - eg a robin, the robin, the robins - which is therefore a substance (entity instance):

	//possessive of substances:

	bool passed = false;
	for(int i=0; i<RELATION_TYPE_POSSESSIVE_NUMBER_OF_TYPES; i++)
	{
		if(currentRelationInList->relationType == relationTypePossessiveNameArray[i])
		{
			passed = true;
		}
	}
	//if(currentRelationInList->relationType == RELATION_TYPE_POSSESSIVE)
	#ifndef GIA_TRANSLATOR_INTERPRET_PRENOMINAL_MODIFIER_PROPERTIES_TAKE_DEPENDENT_AS_PROPERTY_INSTEAD_OF_GOVERNOR
	for(int i=0; i<RELATION_TYPE_PRENOMINAL_MODIFIER_NUMBER_OF_TYPES; i++)
	{
		if(currentRelationInList->relationType == relationTypePrenominalModifierNameArray[i])
		{
			passed = true;
		}
	}
	#endif
	if(passed)
	{
		dependent->hasSubstanceTemp = true;
		#ifdef GIA_ENABLE_REFERENCE_LINKING_BASED_UPON_PRONOUNS_RELEX_USE_ORIGINAL_KNOWN_WORKING_CODE
		dependent->hasSubstanceTemp2 = true;	//only required for linkPronounReferencesRelex{}. Not necessary otherwise, as this is set in GIAtranslatorOperations.cpp
		#endif
	}

	//possessive of substances:

	passed = false;
	for(int i=0; i<RELATION_TYPE_ADJECTIVE_NUMBER_OF_TYPES; i++)
	{
		if(currentRelationInList->relationType == relationTypeAdjectiveNameArray[i])
		{
			passed = true;
		}
	}
	#ifdef GIA_TRANSLATOR_INTERPRET_PRENOMINAL_MODIFIER_PROPERTIES_TAKE_DEPENDENT_AS_PROPERTY_INSTEAD_OF_GOVERNOR
	for(int i=0; i<RELATION_TYPE_PRENOMINAL_MODIFIER_NUMBER_OF_TYPES; i++)
	{
		if(currentRelationInList->relationType == relationTypePrenominalModifierNameArray[i])
		{
			passed = true;
		}
	}
	#endif
	//if((currentRelationInList->relationType == RELATION_TYPE_ADJECTIVE_AMOD) || (currentRelationInList->relationType == RELATION_TYPE_ADJECTIVE_PREDADJ) || (currentRelationInList->relationType == RELATION_TYPE_ADJECTIVE_ADVMOD))
	if(passed)
	{
		bool passed2 = true;
		#ifdef GIA_STANFORD_DO_NOT_USE_UNTESTED_RELEX_OPTIMISATION_CODE_THAT_IS_PROBABLY_STANFORD_COMPATIBLE
		if(NLPdependencyRelationsType == GIA_DEPENDENCY_RELATIONS_TYPE_RELEX)
		{
		#endif
			passed2 = isAdjectiveNotConnectedToObjectOrSubject(currentSentenceInList, currentRelationInList, NLPdependencyRelationsType);
		#ifdef GIA_STANFORD_DO_NOT_USE_UNTESTED_RELEX_OPTIMISATION_CODE_THAT_IS_PROBABLY_STANFORD_COMPATIBLE
		}
		#endif

		if(passed2)
		{
			governor->hasSubstanceTemp = true;
			#ifdef GIA_ENABLE_REFERENCE_LINKING_BASED_UPON_PRONOUNS_RELEX_USE_ORIGINAL_KNOWN_WORKING_CODE
			governor->hasSubstanceTemp2 = true;	//only required for linkPronounReferencesRelex{}. Not necessary otherwise, as this is set in GIAtranslatorOperations.cpp
			#endif
		}
	}

	//has subject:

	passed = false;
	for(int i=0; i<RELATION_TYPE_SUBJECT_NUMBER_OF_TYPES; i++)
	{
		if(currentRelationInList->relationType == relationTypeSubjectNameArray[i])
		{
			passed = true;
		}
	}
	//if(currentRelationInList->relationType == RELATION_TYPE_SUBJECT)
	if(passed)
	{
		dependent->isSubjectTemp = true;
		#ifdef GIA_ENABLE_REFERENCE_LINKING_BASED_UPON_PRONOUNS_RELEX_USE_ORIGINAL_KNOWN_WORKING_CODE
		dependent->isSubjectTemp2 = true;	//only required for linkPronounReferencesRelex{}. Not necessary otherwise, as this is set in GIAtranslatorOperations.cpp
		#endif
	}

	//has object:

	passed = false;
	for(int i=0; i<RELATION_TYPE_OBJECT_NUMBER_OF_TYPES; i++)
	{
		if(currentRelationInList->relationType == relationTypeObjectNameArray[i])
		{
			passed = true;
		}
	}
	//if((currentRelationInList->relationType == RELATION_TYPE_OBJECT) || (currentRelationInList->relationType == RELATION_TYPE_OBJECT_TO))
	if(passed)
	{
		dependent->isObjectTemp = true;
		#ifdef GIA_ENABLE_REFERENCE_LINKING_BASED_UPON_PRONOUNS_RELEX_USE_ORIGINAL_KNOWN_WORKING_CODE
		dependent->isObjectTemp2 = true;	//only required for linkPronounReferencesRelex{}. Not necessary otherwise, as this is set in GIAtranslatorOperations.cpp
		#endif
	}

}

void identifyEntityTypes(GIAsentence* currentSentenceInList, GIAentityNode* GIAentityNodeArray[], int NLPdependencyRelationsType)
{
	GIArelation* currentRelationInList = currentSentenceInList->firstRelationInList;
	while(currentRelationInList->next != NULL)
	{
		#ifdef GIA_DO_NOT_PARSE_DISABLED_RELATIONS_OLD
		if(!(currentRelationInList->disabled))
		{
		#endif
			int relationGovernorIndex = currentRelationInList->relationGovernorIndex;
			int relationDependentIndex = currentRelationInList->relationDependentIndex;
			GIAentityNode* governorTemp = GIAentityNodeArray[relationGovernorIndex];
			GIAentityNode* dependentTemp = GIAentityNodeArray[relationDependentIndex];
			identifyEntityTypesLocal(currentRelationInList, NLPdependencyRelationsType, &governorTemp, &dependentTemp);
		#ifdef GIA_DO_NOT_PARSE_DISABLED_RELATIONS_OLD
		}
		#endif
		currentRelationInList = currentRelationInList->next;
	}
}
*/
