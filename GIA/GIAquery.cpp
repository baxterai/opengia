/*******************************************************************************
 *
 * File Name: GIAquery.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2012 Baxter AI (baxterai.com)
 * Project: General Intelligence Algorithm
 * Project Version: 1l3a 31-May-2012
 * Requirements: requires a GIA network created for both existing knowledge and the query (question)
 * Description: locates (and tags for highlighting) a given query GIA network (subnet) within a larger GIA network of existing knowledge, and identifies the exact answer if applicable (if a comparison variable has been defined within the GIA query network)
 * ?Limitations: will only locate a exact answer (based upon a comparison node) if it provides the maximum number of matched nodes 
 *
 *******************************************************************************/


#include "GIAquery.h"
#include "GIAdatabase.h"
#ifdef USE_WORDNET
	#include "GIAwordnet.h"
	#include "wn.h"
#endif


GIAQueryTraceParameters::GIAQueryTraceParameters(void)
{
	foundAnswer = false;
	queryAnswerNode = NULL;
	queryAnswerContext = "";
	#ifdef GIA_QUERY_SUPPORT_MULTIPLE_ANSWERS
	numberAnswersFound = 0;
	numberOfMatchedNodesAtPreviousAnswerNode = 0;	
	#endif
	thisIsInstanceAndPreviousNodeWasDefinition = false;
	#ifdef GIA_QUERY_ALLOW_ANSWER_OF_NON_IDENTICAL_CONDITION_TYPES
	nonMatchingSourceConditions = false;
	#endif
	
	#ifdef GIA_QUERY_MULTIPLE_ANSWERS_DEBUG
	level = 0;
	#endif	
	
	/*
	queryTraceParametersTemp.isCondition;					//not required for testEntityNodeForQuery
	queryTraceParametersTemp.sourceEntityNode;				//not required for testEntityNodeForQuery
	queryTraceParametersTemp.sourceContext;					//not required for testEntityNodeForQuery
	*/		
}
GIAQueryTraceParameters::~GIAQueryTraceParameters(void)
{
}

GIAQueryTraceParameters::GIAQueryTraceParameters(GIAQueryTraceParameters * queryTraceParametersToCopy)
{
	
	detectComparisonVariable = queryTraceParametersToCopy->detectComparisonVariable;		//never changes
	comparisonVariableNode = queryTraceParametersToCopy->comparisonVariableNode;			//never changes
						
	foundAnswer = false;
	queryAnswerNode = NULL;
	queryAnswerContext = "";	
	#ifdef GIA_QUERY_SUPPORT_MULTIPLE_ANSWERS
	//numberAnswersFound = 0;				//not used for queryTraceParametersToCopyTemp
	//numberOfMatchedNodesAtPreviousAnswerNode = 0;		//not used for queryTraceParametersToCopyTemp
	/*
	vector<GIAEntityNode*> queryAnswerNodes;	
	//vector<string> queryAnswerContexts;
	*/
	#endif
	
	thisIsInstanceAndPreviousNodeWasDefinition = queryTraceParametersToCopy->thisIsInstanceAndPreviousNodeWasDefinition;
	#ifdef GIA_QUERY_ALLOW_ANSWER_OF_NON_IDENTICAL_CONDITION_TYPES
	#ifndef GIA_QUERY_TRACE_PAST_NON_IDENTICAL_CONDITION_TYPES
	nonMatchingSourceConditions = queryTraceParametersToCopy->nonMatchingSourceConditions;
	#endif
	#endif
	
	isCondition = queryTraceParametersToCopy->isCondition;
	sourceEntityNode = queryTraceParametersToCopy->sourceEntityNode;
	sourceContext = queryTraceParametersToCopy->sourceContext;

	#ifdef GIA_QUERY_MULTIPLE_ANSWERS_DEBUG
	level = queryTraceParametersToCopy->level;
	#endif	
	
}



GIAReferenceTraceParameters::GIAReferenceTraceParameters(void)
{
}
GIAReferenceTraceParameters::~GIAReferenceTraceParameters(void)
{
}


GIAEntityNode * answerQueryOrFindAndTagForHighlightingMatchingStructureInSemanticNetwork(unordered_map<string, GIAEntityNode*> *entityNodesActiveListConcepts, unordered_map<string, GIAEntityNode*> *entityNodesActiveListConceptsQuery, bool detectComparisonVariable, GIAEntityNode* comparisonVariableNode, bool * foundAnswer, GIAEntityNode* queryAnswerNode, double * numberOfMatchedNodes, string * queryAnswerContext)
{
	bool traceModeIsQuery = TRACE_MODE_IS_QUERY_TRUE;
	
	int numberOfMatchedNodesTempMax = 0;
	int numberOfMatchedNodesRequiredSynonymnDetectionTempAtMax;
	bool foundAnAnswer = false;	//this is not really used, and is more of an artefact...
	
	#ifdef GIA_QUERY_DEBUG
	if(detectComparisonVariable)
	{
		cout << "answerQueryOrFindAndTagForHighlightingMatchingStructureInSemanticNetwork" << endl;
		cout << "detectComparisonVariable" << endl;
		cout << "\tcomparisonVariableNode->entityName = " << comparisonVariableNode->entityName << endl;
	}
	#endif
	
	GIAEntityNode * networkEntityWithMaxNumberNodesMatched = NULL;
	GIAEntityNode * queryEntityWithMaxNumberNodesMatched = NULL;
	
	bool foundAtLeastOneMatch = false;
		
	for(unordered_map<string, GIAEntityNode*>::iterator entityIterQuery = entityNodesActiveListConceptsQuery->begin(); entityIterQuery != entityNodesActiveListConceptsQuery->end(); entityIterQuery++) 
	{//for each node in query semantic net;
		
		#ifdef GIA_QUERY_DEBUG
		cout << "\n\t\t\t**********************Query Trace Start: entityIterQuery->second->entityName = " << entityIterQuery->second->entityName << endl;
		#endif
		GIAEntityNode* currentQueryEntityNode = entityIterQuery->second;
		
		bool foundQueryEntityNodeName = false;
		long queryEntityNodeIndex = -1;
		string queryEntityNodeName = currentQueryEntityNode->entityName;
		//cout << "saf1" << endl;
		
		GIAEntityNode * conceptEntityMatchingCurrentQueryEntity = findOrAddConceptEntityNodeByName(NULL, entityNodesActiveListConcepts, &queryEntityNodeName, &foundQueryEntityNodeName, &queryEntityNodeIndex, false, NULL, NULL, false);
		
		//cout << "saf2" << endl;
		
		if(foundQueryEntityNodeName)
		{
			#ifdef GIA_QUERY_DEBUG
			cout << "foundQueryEntityNodeName" << endl;
			cout << "\tcurrentQueryEntityNode->entityName = " << currentQueryEntityNode->entityName << endl;
			#endif
				
			//now start matching structure search for all properties of the identical concept node (to current query entity name) in Semantic Network
			
			int numberOfMatchedNodesTemp = 0;	
			int numberOfMatchedNodesRequiredSynonymnDetectionTemp = 0;			
				
			GIAQueryTraceParameters queryTraceParametersTemp;
			queryTraceParametersTemp.detectComparisonVariable = detectComparisonVariable;
			queryTraceParametersTemp.comparisonVariableNode = comparisonVariableNode;

			GIAReferenceTraceParameters referenceTraceParameters;	//irrelevant
					
			testEntityNodeForQueryOrReferenceSet(currentQueryEntityNode, conceptEntityMatchingCurrentQueryEntity, &numberOfMatchedNodesTemp, false, &numberOfMatchedNodesRequiredSynonymnDetectionTemp, traceModeIsQuery, &queryTraceParametersTemp, &referenceTraceParameters);
			//queryAnswerNodeTemp = testEntityNodeForQuery(currentQueryEntityNode, conceptEntityMatchingCurrentQueryEntity, detectComparisonVariable, comparisonVariableNode, &foundAnswerTemp, queryAnswerNodeTemp, &numberOfMatchedNodesTemp, false, &queryPreviousAnswerNodeTemp, &queryAnswerContextTemp, false, false);
			//NB entityNode->isAnswerContextToQuery is identical to entityNode->testedForQueryComparison
			
			//cout << "here" << endl;
			
			#ifdef GIA_QUERY_DEBUG
			cout << "queryTraceParametersTemp.foundAnswer = " << queryTraceParametersTemp.foundAnswer << endl;
			cout << "numberOfMatchedNodesTemp = " << numberOfMatchedNodesTemp << endl;
			#endif
			
			bool bestAnswerCandidate = determineIfBestAnswerCandidate(traceModeIsQuery, queryTraceParametersTemp.foundAnswer, foundAnAnswer, numberOfMatchedNodesTemp, numberOfMatchedNodesTempMax, numberOfMatchedNodesRequiredSynonymnDetectionTemp, numberOfMatchedNodesRequiredSynonymnDetectionTempAtMax);
			//NB are only interested in answers if they give the max or equal to max node matches.. (otherwise answers are now disgarded; as of GIA1l...)
			if(bestAnswerCandidate)
			{	
				foundAtLeastOneMatch = true;	
						
				numberOfMatchedNodesTempMax = numberOfMatchedNodesTemp;
				numberOfMatchedNodesRequiredSynonymnDetectionTempAtMax = numberOfMatchedNodesRequiredSynonymnDetectionTemp;
				
				networkEntityWithMaxNumberNodesMatched = conceptEntityMatchingCurrentQueryEntity;
				queryEntityWithMaxNumberNodesMatched = currentQueryEntityNode;
				
				#ifdef GIA_QUERY_DEBUG
				cout << "bestAnswerCandidate" << endl;
				#endif
								
				if(queryTraceParametersTemp.foundAnswer)
				{//if comparisonVariable is identified within the query, then an exact answer is required... 
					
					foundAnAnswer = true;
					#ifdef GIA_QUERY_DEBUG
					cout << "found answer during query Round 1" << endl;
					#endif
				}				
			}

			//now reset the matched nodes as unpassed (required such that they are retracable using a the different path)
			int irrelevant;
			string printEntityNodeString = "";
			bool traceInstantiations = true;	//clear all (why is this still required if GIA_QUERY_TRACE_INSTANTIATIONS is off? - it is based on testing, but unknown as to why)		
			traceEntityNode(currentQueryEntityNode, GIA_QUERY_TRACE_ENTITY_NODES_FUNCTION_RESET_TESTEDFORQUERYCOMPARISONTEMP, &irrelevant, &printEntityNodeString, false, NULL, traceInstantiations);		
			traceEntityNode(conceptEntityMatchingCurrentQueryEntity, GIA_QUERY_TRACE_ENTITY_NODES_FUNCTION_RESET_TESTEDFORQUERYCOMPARISONTEMP, &irrelevant, &printEntityNodeString, false, NULL, traceInstantiations);		
		}
	}
	
	#ifdef GIA_QUERY_DEBUG
	cout << "finished query round 1" << endl;
	#endif
	#ifdef GIA_QUERY_MULTIPLE_ANSWERS_DEBUG
	cout << "\n\n\nfinished query round 1" << endl;
	#endif
	
	if(foundAtLeastOneMatch)
	{

		//cout << "asf2" << endl;
		//cout << "queryEntityWithMaxNumberNodesMatched->entityName = " << queryEntityWithMaxNumberNodesMatched->entityName << endl; 
		int numberOfMatchedNodesTemp = 0;
		int numberOfMatchedNodesRequiredSynonymnDetectionTemp = 0;
		
		GIAQueryTraceParameters queryTraceParameters;
		queryTraceParameters.detectComparisonVariable = detectComparisonVariable;
		queryTraceParameters.comparisonVariableNode = comparisonVariableNode;

		GIAReferenceTraceParameters referenceTraceParameters;	//irrelevant

		//cout << "asf3" << endl;

		testEntityNodeForQueryOrReferenceSet(queryEntityWithMaxNumberNodesMatched, networkEntityWithMaxNumberNodesMatched, &numberOfMatchedNodesTemp, true, &numberOfMatchedNodesRequiredSynonymnDetectionTemp, traceModeIsQuery, &queryTraceParameters, &referenceTraceParameters);
		//queryAnswerNodeTemp = testEntityNodeForQuery(queryEntityWithMaxNumberNodesMatched, networkEntityWithMaxNumberNodesMatched, detectComparisonVariable, comparisonVariableNode, &foundAnswerTemp, queryAnswerNodeTemp, &numberOfMatchedNodesTemp, true, &queryAnswerContextTemp, false, false);

		#ifdef GIA_QUERY_DEBUG
		cout << "numberOfMatchedNodesTemp = " << numberOfMatchedNodesTemp << endl;
		#endif
		
		if(detectComparisonVariable)
		{
			if(queryTraceParameters.foundAnswer)
			{
				#ifdef GIA_QUERY_DEBUG
				cout << "found answer during query Round 2" << endl;
				#endif

				queryAnswerNode = queryTraceParameters.queryAnswerNode;
				*queryAnswerContext = queryTraceParameters.queryAnswerContext;
				*foundAnswer = true;
				
				#ifndef GIA_DO_NOT_PRINT_RESULTS
				vector<string>::iterator entityAnswerContextsIter = queryTraceParameters.queryAnswerContexts.begin();
				for(vector<GIAEntityNode*>::iterator entityAnswerIter = queryTraceParameters.queryAnswerNodes.begin(); entityAnswerIter != queryTraceParameters.queryAnswerNodes.end(); entityAnswerIter++) 
				{//for each node in answer list;
					cout << "(Multiple) Answer: " << (*entityAnswerIter)->entityName << endl;
					cout << "(Multiple) Answer Context: " << (*entityAnswerContextsIter) << endl;
					entityAnswerContextsIter++;
				}
				#endif
			}
		}

		*numberOfMatchedNodes = (double)numberOfMatchedNodesTemp;
	}

	#ifdef GIA_QUERY_DEBUG
	cout << "finished query round 2" << endl;
	#endif
	return queryAnswerNode;
				
}




int testReferencedEntityNodeForExactNameMatch(GIAEntityNode * queryEntityNode, GIAEntityNode * entityNode, int * numberOfMatchedNodes, bool knownBestMatch, int * numberOfMatchedNodesRequiredSynonymnDetection, bool traceModeIsQuery, GIAQueryTraceParameters * queryTraceParameters, GIAReferenceTraceParameters * referenceTraceParameters)
{
	int result = EXACT_MATCH_OUT_OF_BOUNDS;
	string sourceContextCurrent = queryTraceParameters->sourceContext;
	//cout << "IE-2" << endl;
				
	if(((entityNode->testedForQueryComparison) || (entityNode->testedForQueryComparisonTemp)) && !((queryEntityNode->testedForQueryComparison) || (queryEntityNode->testedForQueryComparisonTemp)))
	{
		//KB entity traced, but query entity not traced... implies have chosen wrong trace path
		result = MATCH_FAIL_COMPLETELY_MISMATCHED_TRACE_PATHS;
	}
	else if(((queryEntityNode->testedForQueryComparison) || (queryEntityNode->testedForQueryComparisonTemp)) && !((entityNode->testedForQueryComparison) || (entityNode->testedForQueryComparisonTemp)))
	{
		//query entity traced, but KB entity not traced... implies have chosen wrong trace path
		result = MATCH_FAIL_COMPLETELY_MISMATCHED_TRACE_PATHS;
	}
	else if(!(entityNode->testedForQueryComparison) && !(entityNode->testedForQueryComparisonTemp))	//added '!(entityNode->testedForQueryComparisonTemp)' 18 May 2012
	{	
		bool compareEntityNamesResult = false;
		if(queryEntityNode->entityName == entityNode->entityName)
		{
			compareEntityNamesResult = true;
		}
		#ifdef GIA_USE_SYNONYMN_DETECTION
		else
		{
			if(compareEntityNames(queryEntityNode, entityNode))
			{
				compareEntityNamesResult = true;
				*numberOfMatchedNodesRequiredSynonymnDetection = *numberOfMatchedNodesRequiredSynonymnDetection + 1;
			}
		}
		#endif

		if(traceModeIsQuery)
		{
			//cout << "IE-1" << endl;
			//cout << "\tqueryEntityNode = " << queryEntityNode->entityName << endl;
			//cout << "\tentityNode = " << entityNode->entityName << endl;
			//cout << "queryTraceParameters->queryAnswerContext = " << queryTraceParameters->queryAnswerContext << endl;

			bool foundMatch = false;

			if(compareEntityNamesResult)
			{
				//cout << "IE0" << endl;

				if(queryTraceParameters->detectComparisonVariable)
				{
					if(queryTraceParameters->comparisonVariableNode->hasQuantity && queryEntityNode->hasQuantity && entityNode->hasQuantity)
					{//exact match found [NB if a quantity, the queryEntityNode's entityName will not have the comparisonVariable name (_$qVar) specified, and therefore a matched entity node entityName is required]
						foundMatch = true;
						#ifdef GIA_QUERY_DEBUG
						cout << "detectComparisonVariable && (queryEntityNode->entityName == entityNode->entityName) && (comparisonVariableNode->hasQuantity && queryEntityNode->hasQuantity && entityNode->hasQuantity)" << endl;					
						cout << "\t foundMatch:" << entityNode->entityName << endl;
						cout << "entityNode->quantityNumberString = " << entityNode->quantityNumberString << endl;
						#endif
					}
					#ifdef GIA_SUPPORT_COMPARISON_VARIABLE_DEFINITION_VIA_ALTERNATE_METHOD_EG_SUPPORT_WHICH_QUERIES
					else if(queryEntityNode->isQuery)				
					{//added support for which query (alternate method of comparison node detection/designation/definition) 
						foundMatch = true;
						#ifdef GIA_QUERY_DEBUG
						cout << "detectComparisonVariable && (queryEntityNode->entityName == entityNode->entityName) && (queryEntityNode->isQuery)" << endl;					
						cout << "\t foundMatch:" << entityNode->entityName << endl;
						#endif					
					}
					#endif
				}
				else
				{
					//if not detecting a comparison variable, then not looking for an exact answer...
				}
				//cout << "IE1" << endl;
			}
			else if(queryTraceParameters->detectComparisonVariable)
			{
				//cout << "IE2" << endl;	
						
				if(queryEntityNode->entityName == queryTraceParameters->comparisonVariableNode->entityName)
				{//exact match found
					//cout << "IE2z" << endl;	
					foundMatch = true;
					#ifdef GIA_QUERY_DEBUG
					cout << "detectComparisonVariable && (queryEntityNode->entityName == comparisonVariableNode->entityName)" << endl;
					cout << "\t foundMatch:" << queryEntityNode->entityName << endl;
					#endif	

					//cout << "IE2a" << endl;		
					
					#ifdef GIA_SUPPORT_COMPARISON_VARIABLE_DEFINITION_VIA_ALTERNATE_METHOD_EG_SUPPORT_WHICH_QUERIES_ADVANCED
					if(queryEntityNode->isWhichQuery)
					{
						/*
						if a 'which' query, then verify that the entityNode is defined by the comparisonVariableNode [ie has a definition corresponding to the comparisonVariableNode]
						eg1 a dog eats the mud. dogs are animals. / which animal eats the mud?	[answer: 'dog' - which is an instance of 'dog' concept node, where the 'dog' concept node is defined by 'animal' 
							NB answer context text = "eat mud is done by dog" ['eat' is the first node traced, and 'dog' is the answer found'. NB the reason 'mud' is added to the answer context text, is because it is the actionObject, which is parsed after actionSubject in testEntityNodeForQuery {ie, after answer 'dog' has already been found}] 
								for this example, need to then verify that the answer 'dog' is defined in the primary semantic network as an animal

						*/
						if(!verifyThatAnswerEntityIsDefinedByComparisonVariableNode(entityNode, queryTraceParameters->comparisonVariableNode->entityName))
						{
							foundMatch = false;
						}
						else
						{
							//cout << "verifyThatAnswerEntityIsDefinedByComparisonVariableNode" << endl;
						}
					}
					#endif									
				}
				//cout << "IE2b" << endl;
			}
			//cout << "IE2c" << endl;

			if(foundMatch)
			{	
				//cout << "IE3" << endl;

				if(knownBestMatch)	//condition added 18 May 2012: only trace the best path (max number of nodes)
				{
					entityNode->isAnswerToQuery = true;
				}
				
				/*artefact:
				#ifndef GIA_QUERY_USE_LONG_CONTEXT_TRACE
				generateTexualContextWithPreviousNodeForwards(&(queryTraceParameters->queryAnswerContext), sourceContextCurrent, entityNode, queryTraceParameters->sourceEntityNode);
				#endif				
				*/
				
				if(queryTraceParameters->foundAnswer)
				{
					cout << "error: query error 1a: answer already found on this trace branch" << endl;
				}
				queryTraceParameters->foundAnswer = true;
				queryTraceParameters->queryAnswerNode = entityNode;
				
				#ifdef GIA_QUERY_DEBUG
				cout << "foundAnswer:" << entityNode->entityName << endl;
				#endif
				//CHECKTHIS; need to take into account vector of answers (not just a single answer)

				result = EXACT_MATCH_PASS;

				#ifndef GIA_QUERY_TRACE_PAST_ANSWER	//changed to Temp 21 May 2012	
				entityNode->testedForQueryComparisonTemp = true;	
				*numberOfMatchedNodes = *numberOfMatchedNodes + 1;
				#endif	
				
				#ifdef GIA_QUERY_SUPPORT_MULTIPLE_ANSWERS
				if(!knownBestMatch)				
				{
					bool answerAlreadyAddedToMultipleAnswers = false;
					for(vector<GIAEntityNode*>::iterator entityAnswerIter = queryTraceParameters->queryAnswerNodes.begin(); entityAnswerIter != queryTraceParameters->queryAnswerNodes.end(); entityAnswerIter++)
					{
						if(((*entityAnswerIter)->entityName == entityNode->entityName) && ((*entityAnswerIter)->idInstance == entityNode->idInstance))
						{
							answerAlreadyAddedToMultipleAnswers = true;
							#ifdef GIA_QUERY_MULTIPLE_ANSWERS_DEBUG
							cout << "2answerAlreadyAddedToMultipleAnswers: " << entityNode->entityName << endl;
							#endif
						}
					}
					if(!answerAlreadyAddedToMultipleAnswers)
					{													
						queryTraceParameters->queryAnswerNodes.push_back(entityNode);
						queryTraceParameters->queryAnswerContexts.push_back("");
						#ifdef GIA_QUERY_MULTIPLE_ANSWERS_DEBUG
						for(int level=0; level<queryTraceParameters->level+1; level++)
						{
							cout << "\t";
						}  					
						cout << "addingAnswer:" << entityNode->entityName << endl;
						#endif	
					}
				}			
				#endif		
				
				#ifdef GIA_QUERY_DEBUG
				cout << "\nfoundmatch AnumberOfMatchedNodes = " << *numberOfMatchedNodes << "\n" << endl; 			
				#endif
			}

			//cout << "IE4" << endl;

		#ifdef GIA_QUERY_ALLOW_ANSWER_OF_NON_IDENTICAL_CONDITION_TYPES
			bool nonMatchingConditions = false;
			if(!compareEntityNamesResult && queryTraceParameters->isCondition)		//now supports unimplemented preposition reduction (need to modify compareEntityNames() to support synonomous prepositions), 	OLD: before 21 May 2012: if((queryEntityNode->entityName != entityNode->entityName) && queryTraceParameters->isCondition)
			{
				nonMatchingConditions = true;
			}		
			#ifdef GIA_QUERY_TRACE_PAST_NON_IDENTICAL_CONDITION_TYPES
			#ifdef GIA_QUERY_TRACE_PAST_ANSWER
			if(compareEntityNamesResult || nonMatchingConditions || foundMatch)	//allow trace past the answer		
			#else
			if(compareEntityNamesResult || nonMatchingConditions)	//redundant (implied/assumed true considering query node will not equal entity node if found answer): && !(queryTraceParameters->foundAnswer)  //only trace if matching entity names [or if it is a condition; allows for non-matching conditions to be compared], and do not trace past the answer			
			#endif		
			{
			#else
			#ifdef GIA_QUERY_TRACE_PAST_ANSWER
			if((compareEntityNamesResult || nonMatchingConditions || foundMatch) && !(queryTraceParameters->nonMatchingSourceConditions))	//do not continue trace if non-matching source conditions	//allow trace past the answer		
			#else
			if((compareEntityNamesResult || nonMatchingConditions) && (!(queryTraceParameters->nonMatchingSourceConditions)))	//redundant (implied/assumed true considering query node will not equal entity node if found answer): && !(queryTraceParameters->foundAnswer)	//do not continue trace if non-matching source conditions	//only trace if matching entity names [or if it is a condition; allows for non-matching conditions to be compared], and do not trace past the answer			
			#endif
			{
				queryTraceParameters->nonMatchingSourceConditions = nonMatchingConditions;
			#endif
		#else
			#ifdef GIA_QUERY_TRACE_PAST_ANSWER
			if(compareEntityNamesResult || foundMatch)	//allow trace past the answer		
			#else
			if(compareEntityNamesResult)	//redundant (implied/assumed true considering query node will not equal entity node if found answer): && !(queryTraceParameters->foundAnswer)			
			#endif		
			{
		#endif	
				//cout << "IE5" << endl;
			
				if(testEntityNodeForQueryOrReferenceSet(queryEntityNode, entityNode, numberOfMatchedNodes, knownBestMatch, numberOfMatchedNodesRequiredSynonymnDetection, traceModeIsQuery, queryTraceParameters, referenceTraceParameters))
				{
					result = EXACT_MATCH_PASS;
				}
				else
				{
					result = EXACT_MATCH_FAIL;
				}
			}
			#ifndef GIA_QUERY_TRACE_PAST_NON_IDENTICAL_CONDITION_TYPES
			#ifdef GIA_QUERY_TRACE_PAST_ANSWER	//changed to Temp 21 May 2012	
			else
			{
				//cout << "IE5b" << endl;
				
				if(foundMatch)
				{
					entityNode->testedForQueryComparisonTemp = true;			
					*numberOfMatchedNodes = *numberOfMatchedNodes + 1;
				}
			}
			#endif
			#endif
			
			#ifdef GIA_QUERY_USE_LONG_CONTEXT_TRACE
			if(queryTraceParameters->foundAnswer)
			{
				if(knownBestMatch)	//is this condition required?
				{
					generateTexualContextBackwards(&(queryTraceParameters->queryAnswerContext), sourceContextCurrent, entityNode);
					#ifdef GIA_QUERY_MULTIPLE_ANSWERS_DEBUG
					cout << "queryTraceParameters->queryAnswerContext = " << queryTraceParameters->queryAnswerContext << endl;
					#endif
				}
				
				#ifdef GIA_QUERY_SUPPORT_MULTIPLE_ANSWERS
				if(!knownBestMatch)
				{
					/*
					string queryAnswerContextTemp = queryTraceParameters->queryAnswerContexts.back();
					generateTexualContextBackwards(&queryAnswerContextTemp, sourceContextCurrent, entityNode);	
					*/
					for(vector<string>::iterator entityAnswerContextsIter = queryTraceParameters->queryAnswerContexts.begin(); entityAnswerContextsIter != queryTraceParameters->queryAnswerContexts.end(); entityAnswerContextsIter++)
					{
						generateTexualContextBackwards(&(*entityAnswerContextsIter), sourceContextCurrent, entityNode);	
						#ifdef GIA_QUERY_MULTIPLE_ANSWERS_DEBUG
						cout << "queryTraceParameters->queryAnswerContexts = " << (*entityAnswerContextsIter) << endl;
						#endif
					}
					#endif	
				}				
			}	
			#endif
			
			#ifdef GIA_QUERY_DEBUG
			if(foundMatch)
			{
				cout << "\n\tfoundmatch BnumberOfMatchedNodes = " << *numberOfMatchedNodes << "\n" << endl; 
			}
			#endif
			
			//cout << "IE6" << endl;

		}
		#ifdef GIA_USE_ADVANCED_REFERENCING
		else
		{
			if((queryEntityNode->referenceSetID == referenceTraceParameters->referenceSetID) || !(referenceTraceParameters->traceModeAssertSameReferenceSetID))	//only trace paths of same reference set ID
			{
				if(compareEntityNamesResult)
				{
					if(testEntityNodeForQueryOrReferenceSet(queryEntityNode, entityNode, numberOfMatchedNodes, knownBestMatch, numberOfMatchedNodesRequiredSynonymnDetection, traceModeIsQuery, queryTraceParameters, referenceTraceParameters))
					{
						result = EXACT_MATCH_PASS;
					}
					else
					{
						result = EXACT_MATCH_FAIL;
					}
				}
				else
				{
					result = EXACT_MATCH_FAIL;
				}
			}
			else
			{
				 result = EXACT_MATCH_OUT_OF_BOUNDS;
			}
		}
		#endif
	}
	else
	{
		 result = EXACT_MATCH_OUT_OF_BOUNDS;
	}

	return result;
}

					
					
					

bool testEntityNodeForQueryOrReferenceSet(GIAEntityNode * queryEntityNode, GIAEntityNode * entityNode, int * numberOfMatchedNodes, bool knownBestMatch, int * numberOfMatchedNodesRequiredSynonymnDetection, bool traceModeIsQuery, GIAQueryTraceParameters * queryTraceParameters, GIAReferenceTraceParameters * referenceTraceParameters)
{	
	bool exactMatch = true;
	
	bool pass = false;

	if(!(entityNode->testedForQueryComparison) && !(entityNode->testedForQueryComparisonTemp) && !(queryEntityNode->testedForQueryComparison) && !(queryEntityNode->testedForQueryComparisonTemp))
	{
		#ifdef GIA_QUERY_MULTIPLE_ANSWERS_DEBUG
		queryTraceParameters->level = queryTraceParameters->level+1;
		int currentLevel = queryTraceParameters->level;	
		#endif
		
		/* this is set elsewhere;
		if(knownBestMatch)
		{
			queryEntityNode->entityCorrespondingBestMatches.push_back(entityNode);
		}
		*/
		
		entityNode->testedForQueryComparison = true;
		queryEntityNode->testedForQueryComparison = true;

		if(traceModeIsQuery)
		{
			#ifdef GIA_QUERY_DO_NOT_ASSIGN_MATCH_POINTS_FOR_NON_IDENTICAL_CONDITION_TYPES
			if(!(queryTraceParameters->nonMatchingSourceConditions))
			{
			#endif
				//cout << "sdvb" << endl;
				#ifdef GIA_QUERY_TRACE_INSTANTIATIONS
				*numberOfMatchedNodes = *numberOfMatchedNodes + 1;
				#else
				if(!(queryTraceParameters->thisIsInstanceAndPreviousNodeWasDefinition))
				{
					*numberOfMatchedNodes = *numberOfMatchedNodes + 1;
				}
				#endif
			#ifdef GIA_QUERY_DO_NOT_ASSIGN_MATCH_POINTS_FOR_NON_IDENTICAL_CONDITION_TYPES
			}
			#endif
		}
		else
		{
			*numberOfMatchedNodes = *numberOfMatchedNodes + 1;
		}
		
		#ifdef GIA_QUERY_DEBUG	
		cout << "\ntestEntityNodeForQueryOrReferenceSet:" << endl;
		cout << "entityNode = " << entityNode->entityName << endl;
		#endif
				
		#ifdef GIA_QUERY_DEBUG
		//cout << "\tqueryEntityNode->entityName = " << queryEntityNode->entityName << endl;
		if(entityNode->isProperty)
		{
			cout << "entityNode = " << entityNode->entityName << " (is property)" << endl;		
		}
		else if(entityNode->isAction)
		{
			cout << "entityNode = " << entityNode->entityName << " (is action)" << endl;		
		}
		else if(entityNode->isCondition)
		{
			cout << "entityNode = " << entityNode->entityName << " (is condition)" << endl;		
		}			
		else if(entityNode->hasAssociatedInstance)
		{
			cout << "entityNode = " << entityNode->entityName << " (has associated instance)" << endl;	
		}
		else if(entityNode->hasAssociatedInstanceIsAction)
		{
			cout << "entityNode = " << entityNode->entityName << " (has associated property is action)" << endl;
		}
		else if(entityNode->hasAssociatedInstanceIsCondition)
		{
			cout << "entityNode = " << entityNode->entityName << " (has associated property is condition)" << endl;
		} 		 
		else if(entityNode->hasAssociatedTime)
		{
			cout << "entityNode = " << entityNode->entityName << " (has associated time)" << endl;	
		}
		else
		{
			cout << "entityNode = " << entityNode->entityName << " (undefined/concept)" << endl;
		}
		cout << "numberOfMatchedNodes = " << *numberOfMatchedNodes << endl;
		#endif
		
		
		
		/*
		cout << "\tentityNode->isAction = " << entityNode->isAction << endl;
		cout << "\tentityNode->isProperty = " << entityNode->isProperty << endl;
		cout << "\tentityNode->hasAssociatedInstance = " << entityNode->hasAssociatedInstance << endl;
		cout << "\tentityNode->hasAssociatedInstanceIsAction = " << entityNode->hasAssociatedInstanceIsAction << endl;
		*/	
		
		/*NOT FINISHED AND WILL NOT BE IMPLEMENTED - this is only required where there exists a discrepancy between the way in which the query net and the text net have been formed;
		//special: having and being connections to conditions....
		if(traceModeIsQuery)
		{
			if(queryTraceParameters->nonMatchingSourceConditions)
			{
				if(queryTraceParameters->detectComparisonVariable)
				{
					if(queryEntityNode->conditionObjectEntity != NULL)
					{	
						queryTraceParameters->isCondition = false;
						queryTraceParameters->sourceEntityNode = entityNode;
									
						//NB entityNode and queryEntityNode are conditions			
						vector<GIAEntityNode*>::iterator connectionIter;
						for(connectionIter = entityNode->EntityNodeDefinitionList.begin(); connectionIter != entityNode->EntityNodeDefinitionList.end(); connectionIter++) 
						{
							queryTraceParameters->sourceContext = "being ";
							//cout << "\t 2A sourceIsConditionAndHasComparisonVariableAttached" << endl;
							int exactMatchTemp = testReferencedEntityNodeForExactNameMatch(*connectionIterQuery, *connectionIter, &numberOfMatchedNodesTemp, traceMode, traceModeAssertSameReferenceSetID, referenceSetID, false, &numberOfMatchedNodesRequiredSynonymnDetectionTemp, traceModeIsQuery, queryTraceParameters);
							
							queryTraceParameters->queryAnswerNode = queryTraceParametersTemp
						}

						for(connectionIter = entityNode->PropertyNodeList.begin(); connectionIter != entityNode->PropertyNodeList.end(); connectionIter++) 
						{
							//cout << "a31" << endl;
							queryTraceParameters->sourceContext = "having ";
							//cout << "\t 2B sourceIsConditionAndHasComparisonVariableAttached" << endl;
							int exactMatchTemp = testReferencedEntityNodeForExactNameMatch(*connectionIterQuery, *connectionIter, &numberOfMatchedNodesTemp, traceMode, traceModeAssertSameReferenceSetID, referenceSetID, false, &numberOfMatchedNodesRequiredSynonymnDetectionTemp, traceModeIsQuery, queryTraceParameters);
						}
					}			
				}		
			}
		}
		*/
				
		for(int i=0; i<GIA_ENTITY_NUMBER_OF_VECTOR_CONNECTION_TYPES; i++)
		{
			bool pass = true;
			#ifndef GIA_QUERY_TRACE_INSTANTIATIONS
			if((i == GIA_ENTITY_VECTOR_CONNECTION_TYPE_NODE_DEFINING_INSTANCE) && (traceModeIsQuery))	//check: do not trace instantinations for queries only
			{
				pass = false;
			}
			#endif
			if(pass)
			{	
				//cout << "i = " << i << endl;
							
				for(vector<GIAEntityConnection*>::iterator connectionIterQuery = queryEntityNode->entityVectorConnectionsArray[i].begin(); connectionIterQuery != queryEntityNode->entityVectorConnectionsArray[i].end(); connectionIterQuery++) 
				{
					bool alreadyFoundAnAnswer = false;
					if(traceModeIsQuery)
					{
						queryTraceParameters->sourceContext = entityVectorConnectionSourceContextArray[i];
						/*
						if(knownBestMatch)
						{
							cout << "********* \t\t i=  " << i << ", queryTraceParameters->sourceContext = " << queryTraceParameters->sourceContext << endl;
						}
						*/
						
						queryTraceParameters->isCondition = entityVectorConnectionIsConditionArray[i];
						queryTraceParameters->sourceEntityNode = entityNode;	
						if(queryTraceParameters->foundAnswer)
						{
							alreadyFoundAnAnswer = true;
						}
						#ifndef GIA_QUERY_TRACE_INSTANTIATIONS
						if(i == GIA_ENTITY_VECTOR_CONNECTION_TYPE_ASSOCIATED_INSTANCES)	//check: do not trace instantinations for queries only
						{
							queryTraceParameters->thisIsInstanceAndPreviousNodeWasDefinition = true;
						}
						else
						{
							queryTraceParameters->thisIsInstanceAndPreviousNodeWasDefinition = false;
						}
						#endif					
					}

					bool foundExactMatchFail = false;
					bool foundExactMatchPass = false;

					int numberOfMatchedNodesTempMax = 0;
					int numberOfMatchedNodesRequiredSynonymnDetectionTempAtMax = 0;
					GIAEntityNode * queryEntityCorrespondingBestMatch;
					
					#ifdef GIA_USE_DATABASE
					if(getUseDatabase())
					{					
						DBreadVectorConnections(entityNode, i);		//this is important, as it will read all of the vector connections from the database for this node (conferred 25 May 2012)
					}
					#endif
					
					#ifdef GIA_QUERY_MULTIPLE_ANSWERS_DEBUG
					for(int level=0; level<currentLevel; level++)
					{
						cout << "\t";
					}  										
					cout << "A. SDGG connectionIterQuery = " << (*connectionIterQuery)->entity->entityName << endl;
					#endif	
					
					//for(vector<GIAEntityConnection*>::iterator connectionIter = entityNode->entityVectorConnectionsArray[i].begin(); connectionIter != entityNode->entityVectorConnectionsArray[i].end(); connectionIter++)
					for(vector<GIAEntityConnection*>::reverse_iterator connectionIter = entityNode->entityVectorConnectionsArray[i].rbegin(); connectionIter != entityNode->entityVectorConnectionsArray[i].rend(); connectionIter++)	//always search from end position first (to take the latest/newest reference/answer, if equal number of matched nodes is detected) 
					{
						#ifdef GIA_QUERY_MULTIPLE_ANSWERS_DEBUG
						for(int level=0; level<currentLevel; level++)
						{
							cout << "\t";
						}  										
						cout << "A2. SDGG connectionIter = " << (*connectionIter)->entity->entityName << endl;
						#endif	
										
						//cout << "connectionIter = " << (*connectionIter)->entity->entityName << endl;
						//cout << "connectionIterQuery = " << (*connectionIterQuery)->entity->entityName << endl;
						
						GIAQueryTraceParameters queryTraceParametersTemp(queryTraceParameters);

						int numberOfMatchedNodesTemp = 0;
						int numberOfMatchedNodesRequiredSynonymnDetectionTemp = 0;
						
						//cout << "fin-1" << endl;
						int exactMatchTemp = testReferencedEntityNodeForExactNameMatch((*connectionIterQuery)->entity, (*connectionIter)->entity, &numberOfMatchedNodesTemp, false, &numberOfMatchedNodesRequiredSynonymnDetectionTemp, traceModeIsQuery, &queryTraceParametersTemp, referenceTraceParameters);
						if(exactMatchTemp == EXACT_MATCH_PASS)
						{
							foundExactMatchPass = true;
						}
						else if((exactMatchTemp == EXACT_MATCH_FAIL) || (exactMatchTemp == MATCH_FAIL_COMPLETELY_MISMATCHED_TRACE_PATHS))
						{
							foundExactMatchFail = true;
						}
						//cout << "fin0" << endl;

						if(exactMatchTemp != MATCH_FAIL_COMPLETELY_MISMATCHED_TRACE_PATHS)
						{
							//cout << "fin1" << endl;
							
							bool bestAnswerCandidate = determineIfBestAnswerCandidate(traceModeIsQuery, queryTraceParametersTemp.foundAnswer, alreadyFoundAnAnswer, numberOfMatchedNodesTemp, numberOfMatchedNodesTempMax, numberOfMatchedNodesRequiredSynonymnDetectionTemp, numberOfMatchedNodesRequiredSynonymnDetectionTempAtMax);
							if(bestAnswerCandidate)
							{			
								queryEntityCorrespondingBestMatch = (*connectionIter)->entity;
								numberOfMatchedNodesTempMax = numberOfMatchedNodesTemp;
								numberOfMatchedNodesRequiredSynonymnDetectionTempAtMax = numberOfMatchedNodesRequiredSynonymnDetectionTemp;
							}
							//cout << "fin2" << endl;
							
							#ifdef GIA_QUERY_SUPPORT_MULTIPLE_ANSWERS
							if(knownBestMatch)
							{//only are concerned about recording multiple answers for known best match...												
								if(traceModeIsQuery)
								{	
									//if(queryTraceParametersTemp.detectComparisonVariable)
									//{ 						
										if(queryTraceParametersTemp.foundAnswer)
										{
											#ifdef GIA_QUERY_MULTIPLE_ANSWERS_DEBUG
											for(int level=0; level<currentLevel; level++)
											{
												cout << "\t";
											}  										
											cout << "queryTraceParametersTemp.foundAnswer: answer = " << queryTraceParametersTemp.queryAnswerNode->entityName << endl;
											#endif

											/*
											//temp;
											#ifdef GIA_QUERY_MULTIPLE_ANSWERS_DEBUG
											for(vector<GIAEntityNode*>::iterator entityAnswerIter = queryTraceParametersTemp.queryAnswerNodes.begin(); entityAnswerIter != queryTraceParametersTemp.queryAnswerNodes.end(); entityAnswerIter++)
											{				
												for(int level=0; level<currentLevel; level++)
												{
													cout << "\t";
												}  
												cout << "Multiple Answer Found:" << (*entityAnswerIter)->entityName << endl;												
											}
											#endif
											*/

											if(alreadyFoundAnAnswer)
											{
												cout << "error: query error 1b: answer already found on alternate trace branch" << endl;							
											}
											else
											{
												//cout << "qerty1b" << endl;
												if(numberOfMatchedNodesTemp > queryTraceParameters->numberOfMatchedNodesAtPreviousAnswerNode)		//do not record deficient answers [those are known to provide less node matches than the previously recorded answer(s)]
												{
													#ifdef GIA_QUERY_MULTIPLE_ANSWERS_DEBUG
													vector<string>::iterator entityAnswerContextsIter = queryTraceParameters->queryAnswerContexts.begin();
													for(vector<GIAEntityNode*>::iterator entityAnswerIter = queryTraceParameters->queryAnswerNodes.begin(); entityAnswerIter != queryTraceParameters->queryAnswerNodes.end(); entityAnswerIter++)
													{		
														for(int level=0; level<currentLevel; level++)
														{
															cout << "\t";
														}  
														cout << "numberOfMatchedNodesTemp = " << numberOfMatchedNodesTemp << ", numberOfMatchedNodesAtPreviousAnswerNode = " << queryTraceParameters->numberOfMatchedNodesAtPreviousAnswerNode << endl;
													
														for(int level=0; level<currentLevel; level++)
														{
															cout << "\t";
														}  
														cout << "Multiple Answer Cleared:" << (*entityAnswerIter)->entityName << endl;
														for(int level=0; level<currentLevel; level++)
														{
															cout << "\t";
														}														
														cout << "Multiple Answer Context Cleared:" << (*entityAnswerContextsIter) << endl;
														entityAnswerContextsIter++;												
													}
													#endif

													//cout << "qerty2" << endl;
													//current answer provides better match... clear previous answer nodes...
													queryTraceParameters->queryAnswerNodes.clear();
													queryTraceParameters->queryAnswerContexts.clear();
													queryTraceParameters->numberAnswersFound = 0;
												}

												if(numberOfMatchedNodesTemp >= queryTraceParameters->numberOfMatchedNodesAtPreviousAnswerNode)
												{
													//cout << "\tStart" << endl;
													vector<string>::iterator entityAnswerContextsIterTemp = queryTraceParametersTemp.queryAnswerContexts.begin();
													for(vector<GIAEntityNode*>::iterator entityAnswerIterTemp = queryTraceParametersTemp.queryAnswerNodes.begin(); entityAnswerIterTemp != queryTraceParametersTemp.queryAnswerNodes.end(); entityAnswerIterTemp++)
													{	
														bool answerAlreadyAddedToMultipleAnswers = false;
														vector<string>::iterator entityAnswerContextsIter = queryTraceParameters->queryAnswerContexts.begin();
														for(vector<GIAEntityNode*>::iterator entityAnswerIter = queryTraceParameters->queryAnswerNodes.begin(); entityAnswerIter != queryTraceParameters->queryAnswerNodes.end(); entityAnswerIter++)
														{
															if(((*entityAnswerIter)->entityName == (*entityAnswerIterTemp)->entityName) && ((*entityAnswerIter)->idInstance == (*entityAnswerIterTemp)->idInstance))	//((*entityAnswerContextsIter) == (*entityAnswerContextsIterTemp)) ? 
															{
																answerAlreadyAddedToMultipleAnswers = true;
																#ifdef GIA_QUERY_MULTIPLE_ANSWERS_DEBUG
																cout << "answerAlreadyAddedToMultipleAnswers: " << (*entityAnswerIterTemp)->entityName << endl;
																cout << "answerAlreadyAddedToMultipleAnswers context: " << (*entityAnswerContextsIterTemp) << endl;
																#endif
															}
															/*
															#ifdef GIA_QUERY_MULTIPLE_ANSWERS_DEBUG
															else if((*entityAnswerIter)->entityName == (*entityAnswerIterTemp)->entityName)
															{
																cout << "ASF" << endl;
															}
															#endif
															*/
															entityAnswerContextsIter++;
														}
														if(!answerAlreadyAddedToMultipleAnswers)
														{					
															queryTraceParameters->queryAnswerNodes.push_back(*entityAnswerIterTemp);
															queryTraceParameters->queryAnswerContexts.push_back(*entityAnswerContextsIterTemp);
															queryTraceParameters->numberAnswersFound = queryTraceParameters->numberAnswersFound + 1;
															
															#ifdef GIA_QUERY_MULTIPLE_ANSWERS_DEBUG
															for(int level=0; level<currentLevel; level++)
															{
																cout << "\t";
															}  
															cout << "Multiple Answer Found:" << (*entityAnswerIterTemp)->entityName << endl;
															for(int level=0; level<currentLevel; level++)
															{
																cout << "\t";
															}															
															cout << "Multiple Answer Context Found:" << (*entityAnswerContextsIterTemp) << endl;
															#endif																
														}
														entityAnswerContextsIterTemp++;
													}
													//cout << "\tEnd" << endl;
													queryTraceParameters->numberOfMatchedNodesAtPreviousAnswerNode = numberOfMatchedNodesTemp;	
												}
											}
										}
									//}
								}
							}
							#endif
							//cout << "fin3" << endl;
							
							//now reset the matched nodes as unpassed (required such that they are retracable using a the different path)
							int irrelevantInt;
							string irrelevantString = "";
							bool traceInstantiations = true;		//clear all (why is this still required if GIA_QUERY_TRACE_INSTANTIATIONS is off? - it is based on testing, but unknown as to why)			
							traceEntityNode((*connectionIter)->entity, GIA_QUERY_TRACE_ENTITY_NODES_FUNCTION_RESET_TESTEDFORQUERYCOMPARISONTEMP, &irrelevantInt, &irrelevantString, false, NULL, traceInstantiations);
							traceEntityNode((*connectionIterQuery)->entity, GIA_QUERY_TRACE_ENTITY_NODES_FUNCTION_RESET_TESTEDFORQUERYCOMPARISONTEMP, &irrelevantInt, &irrelevantString, false, NULL, traceInstantiations);
						}
						/*
						else
						{
							cout << "MATCH_FAIL_COMPLETELY_MISMATCHED_TRACE_PATHS" << endl;
						}
						*/
						
						//cout << "fin4" << endl;
					}
					
					#ifdef GIA_QUERY_MULTIPLE_ANSWERS_DEBUG
					for(int level=0; level<currentLevel; level++)
					{
						cout << "\t";
					}  
					cout << "B. SDGG connectionIterQuery = " << (*connectionIterQuery)->entity->entityName << endl;
					#endif
															
					//cout << "fin5" << endl;
					
					bool exactMatchFoundTemp = false;
					if(!foundExactMatchFail && foundExactMatchPass)
					{	
						exactMatchFoundTemp = true;	
					}

					bool matchFound = determineMatchParameters(exactMatchFoundTemp, traceModeIsQuery, referenceTraceParameters->traceMode, numberOfMatchedNodesTempMax, &exactMatch);

					if(matchFound)
					{	
						//cout << "matchFound i = " << i << endl;
						//cout << "matchFound" << endl;
						//cout << "numberOfMatchedNodes = " << *numberOfMatchedNodes << endl;
						#ifdef GIA_USE_ADVANCED_REFERENCING
						if(knownBestMatch)
						{
							//cout << "knownBestMatch" << endl;
							(*connectionIterQuery)->entity->entityCorrespondingBestMatch = queryEntityCorrespondingBestMatch;		//this shouldn't be required for queries....
						}
						#endif
						//now set the matched nodes as already passed (required such that they are not retraced...)	

						int numberOfMatchedNodesTemp = *numberOfMatchedNodes;
						int numberOfMatchedNodesRequiredSynonymnDetectionTemp = *numberOfMatchedNodesRequiredSynonymnDetection;
								
						int exactMatchTemp = testReferencedEntityNodeForExactNameMatch((*connectionIterQuery)->entity, queryEntityCorrespondingBestMatch, &numberOfMatchedNodesTemp, knownBestMatch, &numberOfMatchedNodesRequiredSynonymnDetectionTemp, traceModeIsQuery, queryTraceParameters, referenceTraceParameters);			//numberOfMatchedNodesTemp, numberOfMatchedNodesRequiredSynonymnDetectionTemp			
						
						*numberOfMatchedNodes = numberOfMatchedNodesTemp;
						*numberOfMatchedNodesRequiredSynonymnDetection = numberOfMatchedNodesRequiredSynonymnDetectionTemp;						
						//cout << "matchFoundEND" << endl;	
					}
					
					//cout << "fin6" << endl;
					
					#ifdef GIA_QUERY_MULTIPLE_ANSWERS_DEBUG
					for(int level=0; level<currentLevel; level++)
					{
						cout << "\t";
					}  										
					cout << "C. SDGG connectionIterQuery = " << (*connectionIterQuery)->entity->entityName << endl;
					#endif	
											
				}
			}
		}

		//cout << "a7" << endl;
				
		//cout << "a8" << endl;	
		#ifdef GIA_QUERY_DEBUG
		if(entityNode->isProperty)
		{
			cout << "Exiting: entityNode = " << entityNode->entityName << " (is property)" << endl;		
		}	
		else if(entityNode->isAction)
		{
			cout << "Exiting: entityNode = " << entityNode->entityName << " (is action)" << endl;		
		}
		else if(entityNode->isCondition)
		{
			cout << "Exiting: entityNode = " << entityNode->entityName << " (is condition)" << endl;		
		}					
		else if(entityNode->hasAssociatedInstance)
		{
			cout << "Exiting: entityNode = " << entityNode->entityName << " (has associated property)" << endl;	
		}
		else if(entityNode->hasAssociatedInstanceIsAction)
		{
			cout << "Exiting: entityNode = " << entityNode->entityName << " (has associated property is action)" << endl;
		} 
		else if(entityNode->hasAssociatedInstanceIsCondition)
		{
			cout << "Exiting: entityNode = " << entityNode->entityName << " (has associated property is condition)" << endl;
		} 		
		else if(entityNode->hasAssociatedTime)
		{
			cout << "Exiting: entityNode = " << entityNode->entityName << " (has associated time)" << endl;	
		}
		else
		{
			cout << "Exiting: entityNode = " << entityNode->entityName << endl;
		}
		#endif
		
		entityNode->testedForQueryComparison = false;
		entityNode->testedForQueryComparisonTemp = true;		
		queryEntityNode->testedForQueryComparison = false;
		queryEntityNode->testedForQueryComparisonTemp = true;	
									
	}
	
	
	return exactMatch;
	//cout << "fin7" << endl;
	
		
}

bool determineIfBestAnswerCandidate(bool traceModeIsQuery, int queryTraceParametersTempFoundAnswer, bool alreadyFoundAnAnswer, bool numberOfMatchedNodesTemp, int numberOfMatchedNodesTempMax, int numberOfMatchedNodesRequiredSynonymnDetectionTemp, int numberOfMatchedNodesRequiredSynonymnDetectionTempAtMax)
{
	bool bestAnswerCandidate = false;

	if(numberOfMatchedNodesTemp > numberOfMatchedNodesTempMax)
	{//first traces (ie traces of newest instances/properties) take priority
		bestAnswerCandidate = true;
	}
	else if(traceModeIsQuery && !alreadyFoundAnAnswer && queryTraceParametersTempFoundAnswer && (numberOfMatchedNodesTemp == numberOfMatchedNodesTempMax))
	{//answer found, where not previously found
		//traces with answers take priority (if equal number of matched nodes)
		bestAnswerCandidate = true;
	}
	else if((numberOfMatchedNodesRequiredSynonymnDetectionTemp < numberOfMatchedNodesRequiredSynonymnDetectionTempAtMax) && (numberOfMatchedNodesTemp == numberOfMatchedNodesTempMax))
	{
		//traces with least degree of synonymn detection required take priority (if equal number of matched nodes)
		bestAnswerCandidate = true;
	}
					
	return bestAnswerCandidate;
}	

bool determineMatchParameters(bool exactMatchFoundTemp, bool traceIsQuery, int referenceTraceParametersTraceMode, int numberOfMatchedNodesTempMax, bool * exactMatch)
{
	if(!exactMatchFoundTemp)
	{
		*exactMatch = false;	//query was not perfectly tracable at/from this node (queryEntityNode)
	}

	bool matchFound = false;				
	if(!traceIsQuery)
	{		
		if(referenceTraceParametersTraceMode == TRACE_MODE_ONLY_RECORD_EXACT_MATCH)
		{
			if(exactMatchFoundTemp)
			{
				matchFound = true;			
			}
		}
		else if(referenceTraceParametersTraceMode != TRACE_MODE_ONLY_RECORD_EXACT_MATCH)
		{
			if(numberOfMatchedNodesTempMax > 0)
			{	
				matchFound = true;				
			}			
		}
	}
	else
	{
		if(numberOfMatchedNodesTempMax > 0)
		{				
			matchFound = true;
		}
	}
	
	return matchFound;
}

bool verifyThatAnswerEntityIsDefinedByComparisonVariableNode(GIAEntityNode * entityNode, string comparisonVariableNodeName)
{
	bool definitionFound = false;
	
	if(entityNode->entityName == comparisonVariableNodeName)
	{
		definitionFound = true;
	}	
	else
	{
		if(!(entityNode->entityNodeDefiningThisInstance->empty()))
		{
			if(verifyThatAnswerEntityIsDefinedByComparisonVariableNode((entityNode->entityNodeDefiningThisInstance->back())->entity, comparisonVariableNodeName))
			{
				definitionFound = true;
			}		
		}
			
		if(!(entityNode->EntityNodeDefinitionList->empty()))
		{
			for(vector<GIAEntityConnection*>::iterator connectionIter = entityNode->EntityNodeDefinitionList->begin(); connectionIter < entityNode->EntityNodeDefinitionList->end(); connectionIter++)
			{
				if(verifyThatAnswerEntityIsDefinedByComparisonVariableNode((*connectionIter)->entity, comparisonVariableNodeName))
				{
					definitionFound = true;
				}
			}				
		}
	}
			
	return definitionFound;
}



bool compareEntityNames(GIAEntityNode * queryEntityNode, GIAEntityNode * entityNode)
{
	bool entityNamesAreSynonymous = false;
	
	#ifndef USE_WORDNET
	cout << "compareEntityNames() error: requires USE_WORDNET" << endl;
	exit(0);
	#endif
	
	//cout << "\t compareEntityNames: queryEntityNode " << queryEntityNode->entityName << ", with entityNode " << entityNode->entityName << endl; 
		
	if(queryEntityNode->entityName == entityNode->entityName)
	{
		entityNamesAreSynonymous = true;
	}	
	else
	{
		if(queryEntityNode->wordNetPOS != entityNode->wordNetPOS)	//error checking
		{
			/*
			#ifdef GIA_WORDNET_DEBUG
			cout << "compareEntityNames() warning: (queryEntityNode->wordNetPOS != entityNode->wordNetPOS)" << endl;
			cout << "queryEntityNode->wordNetPOS " << queryEntityNode->entityName << " = " << queryEntityNode->wordNetPOS << endl;
			cout << "entityNode->wordNetPOS = " << entityNode->entityName << " = " << entityNode->wordNetPOS << endl;
			#endif
			*/
		}
		else
		{		
			if(checkIfWordIsContainedWithinOtherWordsSynsetsOrViceVersa(&(entityNode->entityName), &(queryEntityNode->entityName), entityNode->wordNetPOS))
			{
				entityNamesAreSynonymous = true;
			}
		}
	}
	
	return entityNamesAreSynonymous;
}



void generateTexualContextWithPreviousNodeForwards(string * queryAnswerContext, string sourceContext, GIAEntityNode* entityNode, GIAEntityNode* entityNodePrevious)
{
	generateTexualContextEntityStringForwards(queryAnswerContext, entityNodePrevious);

	*queryAnswerContext = *queryAnswerContext + sourceContext;
	
	generateTexualContextEntityStringForwards(queryAnswerContext, entityNode);
	
	*queryAnswerContext = *queryAnswerContext + ". ";
}

void generateTexualContextForwards(string * queryAnswerContext, string sourceContext, GIAEntityNode* entityNode)
{		
	string texualContextEntityString = "";
	generateTexualContextEntityString(&texualContextEntityString, entityNode);
	
	*queryAnswerContext = *queryAnswerContext + sourceContext + texualContextEntityString;		
}

void generateTexualContextBackwards(string * queryAnswerContext, string sourceContext, GIAEntityNode* entityNode)
{		
	string texualContextEntityString = "";
	generateTexualContextEntityString(&texualContextEntityString, entityNode);
	
	*queryAnswerContext = sourceContext + texualContextEntityString + *queryAnswerContext;	
}

void generateTexualContextEntityStringForwards(string * queryAnswerContext, GIAEntityNode* entityNode)
{	
	string texualContextEntityString = "";
	generateTexualContextEntityString(&texualContextEntityString, entityNode);
	
	*queryAnswerContext = *queryAnswerContext + texualContextEntityString;	
}

void generateTexualContextEntityStringBackwards(string * queryAnswerContext, GIAEntityNode* entityNode)
{	
	string texualContextEntityString = "";
	generateTexualContextEntityString(&texualContextEntityString, entityNode);
	
	*queryAnswerContext = texualContextEntityString + *queryAnswerContext;	
}

void generateTexualContextEntityString(string * texualContextEntityString, GIAEntityNode* entityNode)
{
	string entityPretext = "";
	string entityPosttext = "";
	
	if(entityNode->negative)
	{
		entityPosttext = entityPosttext + "(not) ";
	}

	//cout << "HERE2" << endl;
	
	/*
	if(entityNode->isDefinite)
	{//ie definite noun
		entityPretext = entityPretext + "the ";
	}
	*/
	
	if(entityNode->hasQuantity)
	{
		string quantityNumberStringTemp = printQuantityNumberString(entityNode);	
		entityPretext = entityPretext + quantityNumberStringTemp + " ";
	}	
	else if(entityNode->isProperty)
	{
	}
	else if(entityNode->isAction)
	{	
	}
	else if(entityNode->isCondition)
	{
	}
	else
	{//concept
		entityPretext = entityPretext + "a ";
	}
	
	*texualContextEntityString =  entityPretext + entityNode->entityName + " " + entityPosttext;
}




double determineMaxConfidenceOfQuerySemanticNetwork(unordered_map<string, GIAEntityNode*> *entityNodesActiveListConceptsQuery)
{
	double maxNumberOfMatchedNodes = 0.0;
				
	unordered_map<string, GIAEntityNode*>::iterator connectionIterQuery;
	for(connectionIterQuery = entityNodesActiveListConceptsQuery->begin(); connectionIterQuery != entityNodesActiveListConceptsQuery->end(); connectionIterQuery++) 
	{//for each node in query semantic net;
		
		GIAEntityNode* currentQueryEntityNode = connectionIterQuery->second;

		#ifdef GIA_QUERY_DEBUG
		cout << "determineMaxConfidenceOfQuerySemanticNetwork" << endl;
		cout << "\currentQueryEntityNode->entityName = " << currentQueryEntityNode->entityName << endl;
		#endif
		
		int numberOfMatchedNodes = 0;	
		string queryAnswerContextTemp = "";
		#ifdef GIA_QUERY_TRACE_INSTANTIATIONS
		bool traceInstantiations = true;
		#else
		bool traceInstantiations = false;
		#endif
		 
		traceEntityNode(currentQueryEntityNode, GIA_QUERY_TRACE_ENTITY_NODES_FUNCTION_DETERMINE_MAX_NUMBER_MATCHED_NODES, &numberOfMatchedNodes, &queryAnswerContextTemp, false, NULL, traceInstantiations);

		if((double)numberOfMatchedNodes > maxNumberOfMatchedNodes)
		{
			maxNumberOfMatchedNodes = numberOfMatchedNodes;
		}				
	}
	
	#ifdef GIA_QUERY_USE_ARTIFICIALLY_ADJUSTED_MAX_CONFIDENCE
	return maxNumberOfMatchedNodes-1.0;
	#else
	return maxNumberOfMatchedNodes;
	#endif
}


void printEntityNodeQualitiesOnly(GIAEntityNode * entityNode, string * printEntityNodeString)
{	
	int numberQualities = 0;
	//cout << "entityNode->entityName = " << entityNode->entityName << endl;
	for(vector<GIAEntityConnection*>::iterator connectionIter = entityNode->PropertyNodeList->begin(); connectionIter < entityNode->PropertyNodeList->end(); connectionIter++)
	{
		GIAEntityNode * propertyNode = (*connectionIter)->entity;
		if(propertyNode->hasQuality)
		{
			if(numberQualities > 0)
			{
				*printEntityNodeString = *printEntityNodeString + "\n";	
			}
			else
			{
				*printEntityNodeString = *printEntityNodeString + "(";	
			}		
			numberQualities++;
			
			*printEntityNodeString = *printEntityNodeString + "Type: " + propertyNode->entityName;
		}	
	}
	
	if(numberQualities > 0)
	{
		*printEntityNodeString = *printEntityNodeString + ")\n";	
	}
}

void printEntityTimeConditionNodeOnly(GIAEntityNode * entityNode, string * printEntityNodeString)
{	
	//cout << "entityNode->entityName = " << entityNode->entityName << endl;
	
	if(entityNode->conditionType == CONDITION_NODE_TYPE_TIME)
	{
		if(entityNode->timeConditionNode != NULL)
		{
			*printEntityNodeString = *printEntityNodeString + "(";	

			*printEntityNodeString = *printEntityNodeString + "Time: " + entityNode->timeConditionNode->conditionName;
			
			*printEntityNodeString = *printEntityNodeString + ")\n";
		}	
	}	

}


void traceEntityNodeDetermineNextCourseOfAction(string * printEntityNodeString, GIAEntityNode * entityNode, string context, int function, int * numberOfMatchedNodes, bool thisIsInstanceAndPreviousNodeWasDefinition, int referenceSetID, bool traceInstantiations)
{
	if(function == GIA_QUERY_TRACE_ENTITY_NODES_FUNCTION_PRINT)
	{
		/*
		#ifdef GIA_COMPILE_FOR_BAI_APP_SERVER_RELEASE
		*printEntityNodeString = *printEntityNodeString + "\nContext: = " + entityNode->entityName;			
		#else
		*/
		*printEntityNodeString = *printEntityNodeString + "\nContext: " + context + " = " + entityNode->entityName;		
		//#endif	
	}
	else if(function == GIA_QUERY_TRACE_ENTITY_NODES_FUNCTION_DETERMINE_MAX_NUMBER_MATCHED_NODES)
	{
		traceEntityNode(entityNode, function, numberOfMatchedNodes, printEntityNodeString, thisIsInstanceAndPreviousNodeWasDefinition, referenceSetID, traceInstantiations);
	}
	else if(function == GIA_QUERY_TRACE_ENTITY_NODES_FUNCTION_RESET_TESTEDFORQUERYCOMPARISON)
	{
		traceEntityNode(entityNode, function, numberOfMatchedNodes, printEntityNodeString, thisIsInstanceAndPreviousNodeWasDefinition, referenceSetID, traceInstantiations);
	}
	else if(function == GIA_QUERY_TRACE_ENTITY_NODES_FUNCTION_RESET_TESTEDFORQUERYCOMPARISONTEMP)
	{
		traceEntityNode(entityNode, function, numberOfMatchedNodes, printEntityNodeString, thisIsInstanceAndPreviousNodeWasDefinition, referenceSetID, traceInstantiations);
	}	
	#ifdef GIA_USE_ADVANCED_REFERENCING
	else if(function == GIA_QUERY_TRACE_ENTITY_NODES_FUNCTION_DETERMINE_MAX_NUMBER_MATCHED_NODES_SAME_SET_ONLY)
	{
		if(entityNode->referenceSetID == referenceSetID)
		{
			traceEntityNode(entityNode, function, numberOfMatchedNodes, printEntityNodeString, thisIsInstanceAndPreviousNodeWasDefinition, referenceSetID, traceInstantiations);
		}
	}			
	#endif
	else
	{
		cout << "error: illegal trace entity nodes function" << endl;
		exit(0);
	}

}
void traceEntityNode(GIAEntityNode * entityNode, int function, int * numberOfMatchedNodes, string * printEntityNodeString, bool thisIsInstanceAndPreviousNodeWasDefinition, int referenceSetID, bool traceInstantiations)
{
	bool pass = false;
	if(function == GIA_QUERY_TRACE_ENTITY_NODES_FUNCTION_RESET_TESTEDFORQUERYCOMPARISON)
	{
		if(entityNode->testedForQueryComparison)
		{	
			pass = true;
			entityNode->testedForQueryComparison = false;
		}		
	}
	else if(function == GIA_QUERY_TRACE_ENTITY_NODES_FUNCTION_RESET_TESTEDFORQUERYCOMPARISONTEMP)
	{
		if(entityNode->testedForQueryComparisonTemp)
		{	
			pass = true;
			entityNode->testedForQueryComparisonTemp = false;
		}	
	}
	else
	{
		if(!(entityNode->queryEntityTraced))
		{	
			pass = true;
			entityNode->queryEntityTraced = true;
		}
	}
	
	if(pass)
	{
		/*
		cout << "entityNode being traced = " << entityNode->entityName << endl;
		cout << "*numberOfMatchedNodes = " << *numberOfMatchedNodes << endl;
		*/
		
		if(traceInstantiations)
		{		
			*numberOfMatchedNodes = *numberOfMatchedNodes + 1;
		}
		else
		{
			if(!thisIsInstanceAndPreviousNodeWasDefinition)
			{
				*numberOfMatchedNodes = *numberOfMatchedNodes + 1;
			}
		}

		for(int i=0; i<GIA_ENTITY_NUMBER_OF_VECTOR_CONNECTION_TYPES; i++)
		{
			bool pass2 = true;
			if(!traceInstantiations)
			{
				if(i == GIA_ENTITY_VECTOR_CONNECTION_TYPE_NODE_DEFINING_INSTANCE)
				{
					pass2 = false;
				}
			}
			if(pass2)
			{			
				for(vector<GIAEntityConnection*>::iterator connectionIter = entityNode->entityVectorConnectionsArray[i].begin(); connectionIter != entityNode->entityVectorConnectionsArray[i].end(); connectionIter++) 
				{		
					traceEntityNodeDetermineNextCourseOfAction(printEntityNodeString, (*connectionIter)->entity, entityVectorConnectionContextArray[i], function, numberOfMatchedNodes, entityVectorConnectionThisIsInstanceAndPreviousNodeWasDefinitionArray[i], referenceSetID, traceInstantiations);			
				}
			}
		}
	}	
}







	
	


