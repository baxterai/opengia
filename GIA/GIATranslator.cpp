/*******************************************************************************
 *
 * File Name: GIATranslator.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2012 Baxter AI (baxterai.com)
 * Project: General Intelligence Algorithm
 * Project Version: 1i15a 17-Apr-2012
 * Requirements: requires text parsed by NLP Parser (eg Relex; available in .CFF format <relations>)
 * Description: Converts relation objects into GIA nodes (of type entity, action, condition etc) in GIA network/tree
 * TO DO: replace vectors conceptEntityNodesList/conceptEntityNamesList with a map, and replace vectors GIATimeConditionNode/timeConditionNumbersList with a map
 * TO DO: extract date information of entities from relex <features> tag area
 *******************************************************************************/


#include "GIATranslator.h"
#include "GIATranslatorOperations.h"
#include "GIATranslatorDefineGrammarAndReferencing.h"
#include "GIATranslatorDefineProperties.h"
#include "GIATranslatorLinkEntities.h"
#include "GIATranslatorApplyAdvancedFeatures.h"
#include "GIAdatabase.h"


static int referenceTypeHasDeterminateCrossReferenceNumberArray[GRAMMATICAL_NUMBER_TYPE_INDICATE_HAVE_DETERMINATE_NUMBER_OF_TYPES] = {GRAMMATICAL_NUMBER_SINGULAR};


void initialiseGIATranslatorForTexualContext()
{
	initialiseGIATranslatorForTexualContextOperations();
}


#ifdef GIA_USE_RELEX_UPDATE_ADD_PARAGRAPH_TAGS
void convertParagraphSentenceRelationsIntoGIAnetworkNodes(unordered_map<string, GIAEntityNode*> *conceptEntityNodesList, vector<GIATimeConditionNode*> *timeConditionNodesList, vector<long> *timeConditionNumbersList, Paragraph * firstParagraphInList, int NLPfeatureParser, int NLPdependencyRelationsType)
{
	Paragraph * currentParagraphInList = firstParagraphInList;
	while(currentParagraphInList->next != NULL)
	{
		Sentence * firstSentenceInList = currentParagraphInList->firstSentenceInList;

		convertSentenceListRelationsIntoGIAnetworkNodes(conceptEntityNodesList, timeConditionNodesList, timeConditionNumbersList, firstSentenceInList, NLPfeatureParser, NLPdependencyRelationsType);

		#ifdef GIA_ENABLE_REFERENCE_LINKING_BASED_UPON_PRONOUNS_CLEAR_REFERENCES_EVERY_PARAGRAPH	
		//restore critical variables: used for GIA translator reference paser only - cleared every time a new paragraph is parsed
		unordered_map<string, GIAEntityNode*> ::iterator conceptEntityNodesListIter;
		for(conceptEntityNodesListIter = conceptEntityNodesList->begin(); conceptEntityNodesListIter != conceptEntityNodesList->end(); conceptEntityNodesListIter++) 
		{	
			GIAEntityNode * entityNode = conceptEntityNodesListIter->second;
			entityNode->entityAlreadyDeclaredInThisContext = false;
		}						

		/*
		long vectorSize = conceptEntityNodesList->size();
		for(int entityIndex=0; entityIndex<vectorSize; entityIndex++)
		{	
			GIAEntityNode * entityNode = conceptEntityNodesList->at(entityIndex);
			entityNode->entityAlreadyDeclaredInThisContext = false;
		}
		*/
		#endif
		currentParagraphInList = currentParagraphInList->next;
	}
}
#endif

#ifdef USE_CE
void convertSentenceListRelationsIntoGIAnetworkNodesBasedUponClaimHeirachy(unordered_map<string, GIAEntityNode*> *conceptEntityNodesList, vector<GIATimeConditionNode*> *timeConditionNodesList, vector<long> *timeConditionNumbersList, Sentence * firstSentenceInList, CEClaim * firstClaimInHeirachy, vector<CEClaim*> * claimsList, int NLPfeatureParser, int NLPdependencyRelationsType)
{
	Sentence * currentSentenceInList;
	
	currentSentenceInList = firstSentenceInList;	
	vector<CEClaim*>::iterator claimIter;
	for(claimIter = claimsList->begin(); claimIter != claimsList->end(); claimIter++) 
	{	
		CEClaim * currentClaimInHeirachy = *claimIter;
		currentClaimInHeirachy->sentence = currentSentenceInList;		
		currentSentenceInList = currentSentenceInList->next;
	}
	
	currentSentenceInList = firstSentenceInList;		
	for(claimIter = claimsList->begin(); claimIter != claimsList->end(); claimIter++) 
	{
		CEClaim * currentClaimInHeirachy = *claimIter;

		vector<GIAEntityNode*> *sentenceConceptEntityNodesList = &(currentClaimInHeirachy->relevantConceptEntityNodeList);

		setAllClaimEntitiesInHeirachyToUndeclaredInThisContext(firstClaimInHeirachy);
		setParentClaimEntitiesAsAlreadyDeclaredInThisContext(currentClaimInHeirachy);

		Sentence * firstSentenceInArtificialList = currentSentenceInList;
		generateArtificialSentenceListBasedUponParentClaims(currentClaimInHeirachy, firstSentenceInArtificialList);
		
		convertSentenceRelationsIntoGIAnetworkNodes(conceptEntityNodesList, timeConditionNodesList, timeConditionNumbersList, firstSentenceInList, currentSentenceInList, sentenceConceptEntityNodesList, NLPfeatureParser, NLPdependencyRelationsType);
						
		currentSentenceInList = currentSentenceInList->next;
	}
}
#endif

void convertSentenceListRelationsIntoGIAnetworkNodes(unordered_map<string, GIAEntityNode*> *conceptEntityNodesList, vector<GIATimeConditionNode*> *timeConditionNodesList, vector<long> *timeConditionNumbersList, Sentence * firstSentenceInList, int NLPfeatureParser, int NLPdependencyRelationsType)
{
	Sentence * currentSentenceInList = firstSentenceInList;
	while(currentSentenceInList->next != NULL)
	{
		vector<GIAEntityNode*> sentenceConceptEntityNodesListTempNotUsed;
		convertSentenceRelationsIntoGIAnetworkNodes(conceptEntityNodesList, timeConditionNodesList, timeConditionNumbersList, firstSentenceInList, currentSentenceInList, &sentenceConceptEntityNodesListTempNotUsed, NLPfeatureParser, NLPdependencyRelationsType);
	
		currentSentenceInList = currentSentenceInList->next;
	}
}

//NB vector<GIAEntityNode*> *sentenceConceptEntityNodesList is for GIA_USE_CE only
void convertSentenceRelationsIntoGIAnetworkNodes(unordered_map<string, GIAEntityNode*> *conceptEntityNodesList, vector<GIATimeConditionNode*> *timeConditionNodesList, vector<long> *timeConditionNumbersList, Sentence * firstSentenceInList, Sentence * currentSentenceInList, vector<GIAEntityNode*> *sentenceConceptEntityNodesList, int NLPfeatureParser, int NLPdependencyRelationsType)
{

	Relation * currentRelationInList;
	/*
	#ifdef GIA_TRANSLATOR_DEBUG
	cout << "\t" << currentSentenceInList->sentenceText << endl;
	#endif
	*/
	bool GIAEntityNodeIsDateOrStanfordTime[MAX_NUMBER_OF_WORDS_PER_SENTENCE];	//not properly implemented yet
	int GIAEntityNodeGrammaticalTenseArray[MAX_NUMBER_OF_WORDS_PER_SENTENCE];
	bool GIAEntityNodeGrammaticalTenseModifierArray[MAX_NUMBER_OF_WORDS_PER_SENTENCE*GRAMMATICAL_TENSE_MODIFIER_NUMBER_OF_TYPES];
	int GIAEntityNodeGrammaticalNumberArray[MAX_NUMBER_OF_WORDS_PER_SENTENCE];
	bool GIAEntityNodeGrammaticalIsDefiniteArray[MAX_NUMBER_OF_WORDS_PER_SENTENCE];
	bool GIAEntityNodeGrammaticalIsRelexPersonOrStanfordProperNounArray[MAX_NUMBER_OF_WORDS_PER_SENTENCE];
	int GIAEntityNodeGrammaticalGenderArray[MAX_NUMBER_OF_WORDS_PER_SENTENCE];
	//bool GIAEntityNodeGrammaticalHasCountArray[MAX_NUMBER_OF_WORDS_PER_SENTENCE];
	bool GIAEntityNodeGrammaticalIsPronounArray[MAX_NUMBER_OF_WORDS_PER_SENTENCE];

	string GIAEntityNodeNERArray[MAX_NUMBER_OF_WORDS_PER_SENTENCE];
	string GIAEntityNodeNormalizedNERArray[MAX_NUMBER_OF_WORDS_PER_SENTENCE];
	string GIAEntityNodeTimexArray[MAX_NUMBER_OF_WORDS_PER_SENTENCE];
	string GIAEntityNodePOSArray[MAX_NUMBER_OF_WORDS_PER_SENTENCE];
	
	bool GIAEntityNodeArrayFilled[MAX_NUMBER_OF_WORDS_PER_SENTENCE];		//NB could also use currentSentence->maxNumberOfWordsInSentence
	GIAEntityNode * GIAEntityNodeArray[MAX_NUMBER_OF_WORDS_PER_SENTENCE];

	//added 1 May 11a (assign actions to instances (properties) of entities and not entities themselves where appropriate)
	//bool GIAEntityNodeArrayHasAssociatedProperty[MAX_NUMBER_OF_WORDS_PER_SENTENCE];

	bool GIAEntityNodeIsAReference[MAX_NUMBER_OF_WORDS_PER_SENTENCE];

	for(int w=0; w<MAX_NUMBER_OF_WORDS_PER_SENTENCE; w++)
	{					
		GIAEntityNodeIsDateOrStanfordTime[w] = false;
		GIAEntityNodeGrammaticalTenseArray[w] = GRAMMATICAL_TENSE_UNDEFINED;
		GIAEntityNodeGrammaticalNumberArray[w] = GRAMMATICAL_NUMBER_UNDEFINED;
		GIAEntityNodeGrammaticalIsDefiniteArray[w] = false;
		GIAEntityNodeGrammaticalIsRelexPersonOrStanfordProperNounArray[w] = false;
		GIAEntityNodeGrammaticalGenderArray[w] = GRAMMATICAL_NUMBER_UNDEFINED;
		//GIAEntityNodeGrammaticalHasCountArray[w] = GRAMMATICAL_NUMBER_UNDEFINED;
		GIAEntityNodeGrammaticalIsPronounArray[w] = GRAMMATICAL_PRONOUN_UNDEFINED;
		
		GIAEntityNodeNERArray[w] = "";
		GIAEntityNodeNormalizedNERArray[w] = "";
		GIAEntityNodeTimexArray[w] = "";
		GIAEntityNodePOSArray[w] = "";
		
		for(int q=0; q<GRAMMATICAL_TENSE_MODIFIER_NUMBER_OF_TYPES;q++)
		{
			GIAEntityNodeGrammaticalTenseModifierArray[w*q] = false;
		}

		GIAEntityNodeIsAReference[w] = false;

		GIAEntityNodeArrayFilled[w] = false;

		//added 1 May 11a (assign actions to instances (properties) of entities and not entities themselves where appropriate)
		//GIAEntityNodeArrayHasAssociatedProperty[w] = false;

		//GIAActionNodeArrayFilled[w] = false;
	}


	#ifdef GIA_TRANSLATOR_DEBUG
	cout << "pass A;" << endl;
	cout << "pass 0; locate/add all entities" << endl;
	#endif
	locateAndAddAllConceptEntities(currentSentenceInList, GIAEntityNodeArrayFilled, GIAEntityNodeArray, conceptEntityNodesList, sentenceConceptEntityNodesList, NLPdependencyRelationsType);


	
	#ifdef GIA_TRANSLATOR_DEBUG
	cout << "pass 1; fillGrammaticalArrays" << endl;
	#endif
	#ifdef GIA_USE_RELEX
	if(NLPdependencyRelationsType == GIA_DEPENDENCY_RELATIONS_TYPE_RELEX)
	{
		fillGrammaticalArraysRelex(currentSentenceInList, GIAEntityNodeIsDateOrStanfordTime, GIAEntityNodeGrammaticalTenseArray, GIAEntityNodeGrammaticalTenseModifierArray, GIAEntityNodeGrammaticalNumberArray, GIAEntityNodeGrammaticalIsDefiniteArray, GIAEntityNodeGrammaticalIsRelexPersonOrStanfordProperNounArray, GIAEntityNodeGrammaticalGenderArray, GIAEntityNodeGrammaticalIsPronounArray);
	}
	#endif
	#ifdef GIA_USE_STANFORD_DEPENDENCY_RELATIONS
	if(NLPdependencyRelationsType == GIA_DEPENDENCY_RELATIONS_TYPE_STANFORD)
	{
		fillGrammaticalArraysStanford(currentSentenceInList, GIAEntityNodeArrayFilled, GIAEntityNodeArray, GIAEntityNodeIsDateOrStanfordTime, GIAEntityNodeGrammaticalTenseArray, GIAEntityNodeGrammaticalTenseModifierArray, GIAEntityNodeGrammaticalNumberArray, GIAEntityNodeGrammaticalIsDefiniteArray, GIAEntityNodeGrammaticalIsRelexPersonOrStanfordProperNounArray, GIAEntityNodeGrammaticalGenderArray, GIAEntityNodeGrammaticalIsPronounArray, GIAEntityNodeNERArray, GIAEntityNodeNormalizedNERArray, GIAEntityNodeTimexArray, GIAEntityNodePOSArray, NLPfeatureParser);
	}
	#endif
	
	
	#ifdef GIA_TRANSLATOR_DEBUG
	cout << "pass 1a; applyGrammaticalInfoToAllConceptEntities" << endl;
	#endif
 	applyGrammaticalInfoToAllConceptEntities(GIAEntityNodeArrayFilled, GIAEntityNodeArray, GIAEntityNodeIsDateOrStanfordTime, GIAEntityNodeGrammaticalTenseArray, GIAEntityNodeGrammaticalTenseModifierArray, GIAEntityNodeGrammaticalNumberArray, GIAEntityNodeGrammaticalIsDefiniteArray, GIAEntityNodeGrammaticalIsRelexPersonOrStanfordProperNounArray, GIAEntityNodeGrammaticalGenderArray, GIAEntityNodeGrammaticalIsPronounArray, GIAEntityNodeNERArray, GIAEntityNodeNormalizedNERArray, GIAEntityNodeTimexArray, GIAEntityNodePOSArray);

	
	#ifdef GIA_USE_STANFORD_DEPENDENCY_RELATIONS
	if(NLPdependencyRelationsType == GIA_DEPENDENCY_RELATIONS_TYPE_STANFORD)
	{
	
		#ifdef GIA_TRANSLATOR_DEBUG
		cout << "pass 1z1 pass; redistribute Stanford Relations NSubj And Preposition" << endl;
		#endif
		redistributeStanfordRelationsMultiwordPreposition(currentSentenceInList, GIAEntityNodeArray);
							
		#ifndef GIA_DO_NOT_SUPPORT_SPECIAL_CASE_6A_COLLAPSE_ADVMOD_RELATION_GOVERNOR_BE
		#ifdef GIA_TRANSLATOR_DEBUG
		cout << "pass 1z2; redistribute Stanford Relations -Collapse Advmod Relation Function Be (eg The rabbit is 20 meters away. 	nsubj(is-3, rabbit-2) / advmod(is-3, away-6) - > _predadj(rabbit-2, away-6)   +    Kane is late.	nsubj(late-3, Kane-1) / cop(late-3, is-2) -> _predadj(kane-1, late-3)          +    She is the one     nsubj(one-4, She-1) /cop(one-4, is-2) / det(one-4, the-3) -> appos(She-1, one-4)" << endl;
		//[OLD: nsubj(is-3, rabbit-2) / advmod(is-3, away-6) - >nsubj(away-6, rabbit-2)] )" << endl;
		#endif
		redistributeStanfordRelationsCollapseAdvmodRelationGovernorBe(currentSentenceInList, GIAEntityNodeArrayFilled, GIAEntityNodeArray, NLPfeatureParser);		
		#endif
				
		#ifdef GIA_TRANSLATOR_DEBUG
		cout << "pass 1z3; redistribute Stanford Relations - Adverbal Clause Modifier And Complement (eg The accident happened as the night was falling. 	advcl(happen, fall) / mark(fall, as))" << endl;
		#endif
		redistributeStanfordRelationsAdverbalClauseModifierAndComplement(currentSentenceInList, GIAEntityNodeArrayFilled, GIAEntityNodeArray);
				
		#ifdef GIA_TRANSLATOR_DEBUG
		cout << "pass 1z4; redistribute Stanford Relations - Clausal Subject (eg What she said makes sense. 	csubj (make, say)/dobj ( said-3 , What-1 ))" << endl;
		#endif
		redistributeStanfordRelationsClausalSubject(currentSentenceInList, GIAEntityNodeArrayFilled, GIAEntityNodeArray);
		
		#ifdef GIA_USE_REDISTRIBUTE_STANFORD_RELATIONS_PHRASAL_VERB_PARTICLE
		#ifdef GIA_TRANSLATOR_DEBUG
		cout << "pass 1z5; redistribute Stanford Relations - Phrasal Verb Particle (eg They shut down the station. 	prt(shut, down))" << endl;
		#endif
		redistributeStanfordRelationsPhrasalVerbParticle(currentSentenceInList, GIAEntityNodeArrayFilled, GIAEntityNodeArray);
		#endif
		
		#ifdef GIA_TRANSLATOR_DEBUG
		cout << "pass 1z6; redistribute Stanford Relations - Conjunction And Coordinate (eg I eat a pie or tom rows the boat. 	cc(pie-4, or-5) / conj(pie-4, tom-6))" << endl;
		#endif
		redistributeStanfordRelationsConjunctionAndCoordinate(currentSentenceInList, GIAEntityNodeArrayFilled, GIAEntityNodeArray);		
		
		#ifdef GIA_TRANSLATOR_DEBUG
		cout << "pass 1z7; redistribute Stanford Relations - Generate Unparsed Quantity Modifers (eg The punter won almost $1000. 	advmod(won-3, almost-4) / pobj(almost-4, $-5)) / num($-5, 1000-6)" << endl;
		#endif
		redistributeStanfordRelationsGenerateUnparsedQuantityModifers(currentSentenceInList, GIAEntityNodeArrayFilled, GIAEntityNodeArray);	
		
		#ifndef GIA_DO_NOT_SUPPORT_SPECIAL_CASE_6A_GENERATE_MEASURES
		#ifdef GIA_TRANSLATOR_DEBUG
		cout << "pass 1z8; redistribute Stanford Relations - Generate Measures (eg years old - npadvmod(old, years) -> _measure_time(old[7], years[6]))" << endl;
		#endif
		redistributeStanfordRelationsGenerateMeasures(currentSentenceInList, GIAEntityNodeArrayFilled, GIAEntityNodeArray);						
		#endif
		
		#ifdef GIA_TRANSLATOR_DEBUG
		cout << "pass 1z9; redistribute Stanford Relations - Prt And Tmods (eg The disaster happened over night.   prt(happened-3, over-4) / tmod(happened-3, night-5) -> over(happened-3, night-5) )" << endl;
		#endif
		redistributeStanfordRelationsPrtAndTmod(currentSentenceInList, GIAEntityNodeArrayFilled, GIAEntityNodeArray);	
				
	}
	#endif

		#ifdef GIA_STANFORD_DEPENDENCY_RELATIONS_DEBUG2
		currentRelationInList = currentSentenceInList->firstRelationInList;
		while(currentRelationInList->next != NULL)
		{
			if(!(currentRelationInList->disabled))
			{
				string relationType = currentRelationInList->relationType;
				GIAEntityNode * relationGoverner = GIAEntityNodeArray[currentRelationInList->relationGovernorIndex];				
				GIAEntityNode * relationDependent = GIAEntityNodeArray[currentRelationInList->relationDependentIndex];

				cout << "relationType = " << currentRelationInList->relationType << endl;	      
				cout << "relationGoverner = " << relationGoverner->entityName << endl;
				cout << "relationDependent = " << relationDependent->entityName << endl;		
			}
			currentRelationInList = currentRelationInList->next;		
		}
		//exit(0);
		#endif
		
				
	#ifdef GIA_TRANSLATOR_DEBUG
	cout << "pass 1b; identify comparison variable" << endl;
	#endif
	identifyComparisonVariableAlternateMethod(currentSentenceInList, GIAEntityNodeArrayFilled, GIAEntityNodeArray);

	#ifdef GIA_TRANSLATOR_DEBUG	
	cout << "pass 1c; switch argument/functions where necessary" << endl;
	#endif
	switchArgumentsAndFunctionsWhereNecessary(currentSentenceInList, NLPdependencyRelationsType);

	#ifdef GIA_TRANSLATOR_DEBUG		
	cout << "pass 2; identify entity types [define entities as objects, subjects, and being possessive of properties];" << endl;
	#endif
	identifyEntityTypes(currentSentenceInList, GIAEntityNodeArray, NLPdependencyRelationsType);

	#ifdef GIA_ENABLE_REFERENCE_LINKING_BASED_UPON_PRONOUNS
	#ifndef GIA_STANFORD_CORE_NLP_DO_NOT_USE_CODEPENDENCIES
	if(NLPfeatureParser == GIA_NLP_PARSER_RELEX)
	{
	#endif
		
		#ifdef GIA_TRANSLATOR_DEBUG
		cout << "pass 3; link references (eg his/her with joe/emily)" << endl;
		#endif
		linkReferences(currentSentenceInList, GIAEntityNodeArrayFilled, GIAEntityNodeArray, conceptEntityNodesList, GIAEntityNodeIsDateOrStanfordTime, GIAEntityNodeGrammaticalTenseArray, GIAEntityNodeGrammaticalTenseModifierArray, GIAEntityNodeGrammaticalNumberArray, GIAEntityNodeGrammaticalIsDefiniteArray, GIAEntityNodeGrammaticalIsRelexPersonOrStanfordProperNounArray, GIAEntityNodeGrammaticalGenderArray, GIAEntityNodeGrammaticalIsPronounArray, GIAEntityNodeIsAReference);
	#ifndef GIA_STANFORD_CORE_NLP_DO_NOT_USE_CODEPENDENCIES	
	}
	#ifdef GIA_USE_STANFORD_CORENLP
	else if(NLPfeatureParser == GIA_NLP_PARSER_STANFORD_CORENLP)
	{
		#ifdef GIA_TRANSLATOR_DEBUG
		cout << "pass 3; link references (eg his/her with joe/emily)" << endl;
		#endif	
		linkReferencesStanfordCoreNLP(currentSentenceInList, GIAEntityNodeArrayFilled, GIAEntityNodeArray, conceptEntityNodesList, firstSentenceInList->firstCoreferenceInList, GIAEntityNodeIsAReference);
	}
	#endif
	#endif
	#endif

	
							
	#ifdef GIA_TRANSLATOR_DEBUG
	cout << "pass B;" << endl;
	cout << "0z2 pass; collapseRedundantRelationAndMakeNegative (eg 'Space is saved by not having a bulky cart.'); _subj(not[5], by[4]), _subj(have[6], not[5])" << endl;
	#endif
	collapseRedundantRelationAndMakeNegative(currentSentenceInList, GIAEntityNodeArray, NLPdependencyRelationsType);

	#ifdef GIA_TRANSLATOR_DEBUG
	cout << "0z pass; define properties (objects/subjects with properties; eg 'Truffles which are picked are tasty.' - Truffle must be an instance/property in this case); _obj(pick[4], truffle[1]), _predadj(truffle[1], tasty[6])" << endl;
	#endif
	definePropertiesObjectsAndSubjectsWithProperties(GIAEntityNodeArrayFilled, GIAEntityNodeArray);

	#ifdef GIA_TRANSLATOR_DEBUG
	cout << "0a pass; define properties (definite nouns); eg the house" << endl;
	#endif
	definePropertiesDefiniteNouns(GIAEntityNodeArrayFilled, GIAEntityNodeArray, GIAEntityNodeGrammaticalIsDefiniteArray, GIAEntityNodeGrammaticalIsRelexPersonOrStanfordProperNounArray, GIAEntityNodeIsDateOrStanfordTime, GIAEntityNodeIsAReference);

	#ifdef GIA_TRANSLATOR_DEBUG
	cout << "0b pass; define properties (nouns with determinates); eg a house, the house, the houses [all nouns with singular/plural are assumed to have determintes, and are therefore properties]" << endl;
	#endif
	definePropertiesNounsWithDeterminates(GIAEntityNodeArrayFilled, GIAEntityNodeArray, referenceTypeHasDeterminateCrossReferenceNumberArray, GIAEntityNodeGrammaticalIsRelexPersonOrStanfordProperNounArray, GIAEntityNodeIsDateOrStanfordTime, GIAEntityNodeIsAReference);

	#ifdef GIA_TRANSLATOR_DEBUG
	cout << "0c pass; define properties (nouns with adjectives); _amod; eg locked door, _advmod; eg cheetahs run quickly [NOT and c) _predadj; eg giants are red / joe is late]" << endl;
	#endif
	definePropertiesNounsWithAdjectives(currentSentenceInList, GIAEntityNodeArray, NLPdependencyRelationsType);

	#ifdef GIA_TRANSLATOR_DEBUG
	cout << "0d pass; define properties (quantities [not quantity mods/multipiers, not measure pers] and measures);" << endl;
	#endif
	definePropertiesQuantitiesAndMeasures(currentSentenceInList, GIAEntityNodeArray);

	#ifdef GIA_TRANSLATOR_DEBUG
	cout << "0e pass; define properties (quantity mods);" << endl;
	#endif
	definePropertiesQuantityModifiers(currentSentenceInList, GIAEntityNodeArray);

	#ifdef GIA_TRANSLATOR_DEBUG
	cout << "0f pass; define properties (expletives eg 'there' in 'there is a place');" << endl;
	#endif
	definePropertiesExpletives(currentSentenceInList, GIAEntityNodeArray);

	#ifdef GIA_TRANSLATOR_DEBUG
	cout << "0g pass; define properties (pronouns eg 'we'/'I');" << endl;
	#endif
	definePropertiesPronouns(GIAEntityNodeArrayFilled, GIAEntityNodeArray, GIAEntityNodeGrammaticalIsPronounArray, GIAEntityNodeIsAReference);

	#ifdef GIA_TRANSLATOR_DEBUG
	cout << "0h pass; define properties (to_be);" << endl;
	#endif
	definePropertiesToBe(currentSentenceInList, GIAEntityNodeArray);

	#ifdef GIA_TRANSLATOR_DEBUG
	cout << "0i pass; define properties (to_do);" << endl;
	#endif		
	definePropertiesToDo(currentSentenceInList, GIAEntityNodeArray);

	#ifdef GIA_TRANSLATOR_DEBUG
	cout << "0j pass; define properties (has time);" << endl;
	#endif		
	definePropertiesHasTime(GIAEntityNodeArrayFilled, GIAEntityNodeArray);	

	#ifndef GIA_DO_NOT_SUPPORT_SPECIAL_CASE_1F_RELATIONS_TREAT_THAT_AS_A_PRONOUN_IE_PROPERTY			
	#ifdef GIA_TRANSLATOR_DEBUG
	cout << "0k pass; define properties (non explicit pronouns eg 'that');" << endl;
	#endif
	definePropertiesNonExplicitPronouns(GIAEntityNodeArrayFilled, GIAEntityNodeArray);
	#endif
	
	#ifdef GIA_TRANSLATOR_DEBUG
	cout << "1 pass; link properties (possessive relationships); eg joe's bike" << endl;
	#endif
	linkPropertiesPossessiveRelationships(currentSentenceInList, GIAEntityNodeArray);

	#ifdef GIA_TRANSLATOR_DEBUG
	cout << "2a pass; link properties (descriptive relationships); eg joe is happy" << endl;
	#endif
	linkPropertiesDescriptiveRelationships(currentSentenceInList, GIAEntityNodeArray, NLPdependencyRelationsType);

	#ifdef GIA_TRANSLATOR_DEBUG
	cout << "2b pass; link entity definitions (appositive of nouns only)" << endl;
	#endif
	linkEntityDefinitionsAppositiveOfNouns(currentSentenceInList, GIAEntityNodeArray);

	#ifdef GIA_TRANSLATOR_DEBUG
 	cout <<"3a pass; define dependent subject-object definition/composition/action relationships" << endl;
	#endif
	defineSubjectObjectRelationships(currentSentenceInList, GIAEntityNodeArray, conceptEntityNodesList, NLPdependencyRelationsType);

	#ifdef GIA_TRANSLATOR_DEBUG
 	cout <<"3b pass; define independent subject/object action relationships" << endl;
	#endif
	defineSubjectOrObjectRelationships(currentSentenceInList, GIAEntityNodeArray, conceptEntityNodesList, NLPdependencyRelationsType);

	#ifdef GIA_TRANSLATOR_DEBUG
	cout << "3c pass; define indirect objects" << endl;
	#endif
	defineIndirectObjects(currentSentenceInList, GIAEntityNodeArray);

	#ifdef GIA_TRANSLATOR_DEBUG
	cout << "3d pass; define object/subject of preposition" << endl;
	#endif
	defineObjectSubjectOfPreposition(currentSentenceInList, GIAEntityNodeArray, conceptEntityNodesList, NLPdependencyRelationsType);

#ifdef GIA_TRANSLATOR_EXPLICITLY_ADD_CONJUNCTION_CONDITIONS
	#ifdef GIA_TRANSLATOR_DEBUG
	cout << "3e pass; define conjunction conditions; eg Either Tom and/or Max eat the cake...." << endl;
	#endif
	defineConjunctionConditions(currentSentenceInList, GIAEntityNodeArray, conceptEntityNodesList);	
#endif

	#ifdef GIA_TRANSLATOR_DEBUG
	cout << "3f pass; define action/property conditions" << endl;
	#endif
	defineActionPropertyConditions(currentSentenceInList, GIAEntityNodeArrayFilled, GIAEntityNodeArray, conceptEntityNodesList, NLPdependencyRelationsType);

	#ifdef GIA_USE_STANFORD_CORENLP
	if(NLPfeatureParser == GIA_NLP_PARSER_STANFORD_CORENLP)
	{
		#ifdef GIA_TRANSLATOR_DEBUG
		cout <<"4a pass; disable redundant nodes Stanford Core NLP" << endl;	//[this could be implemented/"shifted" to an earlier execution stage with some additional configuration]
		#endif
		disableRedundantNodesStanfordCoreNLP(currentSentenceInList, GIAEntityNodeArrayFilled, GIAEntityNodeArray);	
	}
	#endif
	
	#ifdef GIA_TRANSLATOR_DEBUG
	cout <<"4b pass; extract dates" << endl;	//[this could be implemented/"shifted" to an earlier execution stage with some additional configuration]
	#endif
	extractDates(currentSentenceInList, GIAEntityNodeArrayFilled, GIAEntityNodeArray, NLPfeatureParser);	
	
	#ifdef GIA_TRANSLATOR_DEBUG
	cout << "4c pass; extract quantities" << endl;
	#endif
	extractQuantities(currentSentenceInList, GIAEntityNodeArrayFilled, GIAEntityNodeArray, conceptEntityNodesList, NLPfeatureParser);

	#ifdef GIA_TRANSLATOR_DEBUG
	cout << "4d pass; extract measures" << endl;
	#endif
	extractMeasures(currentSentenceInList, GIAEntityNodeArray, conceptEntityNodesList);

	#ifdef GIA_TRANSLATOR_DEBUG
	cout << "4e/4f pass; define to_be/to_do conditions" << endl;
	#endif
	defineToBeAndToDoProperties(currentSentenceInList, GIAEntityNodeArray, conceptEntityNodesList);

	#ifdef GIA_TRANSLATOR_DEBUG
	cout << "4g pass; extract qualities" << endl;
	#endif
	extractQualities(currentSentenceInList, GIAEntityNodeArray, conceptEntityNodesList, NLPdependencyRelationsType);

	#ifdef GIA_TRANSLATOR_DEBUG
	cout << "4h pass; link properties (parataxis); eg the guy, Akari said, left..." << endl;
	#endif
	linkPropertiesParataxis(currentSentenceInList, GIAEntityNodeArray);	

	if(NLPdependencyRelationsType == GIA_DEPENDENCY_RELATIONS_TYPE_STANFORD)
	{
		#ifdef GIA_USE_STANFORD_CORENLP
		#ifdef GIA_TRANSLATOR_DEBUG
		cout << "4i pass; define Clausal Complement Properties (ccomp); eg ccomp(say, like)	He says that you like to swim" << endl;
		#endif
		defineClausalComplementProperties(currentSentenceInList, GIAEntityNodeArrayFilled, GIAEntityNodeArray);	
		#endif
	}

	#ifdef GIA_TRANSLATOR_DEBUG
	cout << "record sentence nodes as permanent if they are still enabled" << endl;
	#endif
	recordSentenceConceptNodesAsPermanentIfTheyAreStillEnabled(GIAEntityNodeArrayFilled, GIAEntityNodeArray);
	
	
	/*OLD DELETE;
	//cout << "5a pass; parse questions" << endl;	
	currentRelationInList = currentSentenceInList->firstRelationInList;
	while(currentRelationInList->next != NULL)
	{	
		//parse specific relex questions: replace with standard prepositions and add question flag "isQuery"
		if(currentRelationInList->relationType == REFERENCE_TYPE_QUESTION_QUERY_VARIABLE_WHEN)
		{
			passedPropositionTime = true;
		}
		else if(currentRelationInList->relationType == REFERENCE_TYPE_QUESTION_QUERY_VARIABLE_WHERE)
		{
			passedPropositionLocation = true;
		}
		else if(currentRelationInList->relationType == REFERENCE_TYPE_QUESTION_QUERY_VARIABLE_WHY)
		{
			passedPropositionReason = true;
		}	
	}
	*/

	#ifdef GIA_ENABLE_REFERENCE_LINKING_BASED_UPON_PRONOUNS_CLEAR_REFERENCES_EVERY_SENTENCE	
	//restore critical variables: used for GIA translator reference paser only - cleared every time a new sentence is parsed
	unordered_map<string, GIAEntityNode*> ::iterator conceptEntityNodesListIter;
	for(conceptEntityNodesListIter = conceptEntityNodesList->begin(); conceptEntityNodesListIter != conceptEntityNodesList->end(); conceptEntityNodesListIter++) 
	{	
		GIAEntityNode * entityNode = conceptEntityNodesListIter->second;
		entityNode->entityAlreadyDeclaredInThisContext = false;
	}
	/*OLD:
	long vectorSize = conceptEntityNamesList->size();
	for(int entityIndex=0; entityIndex<vectorSize; entityIndex++)
	{	
		GIAEntityNode * entityNode = conceptEntityNodesList->at(entityIndex);
		entityNode->entityAlreadyDeclaredInThisContext = false;
	}
	*/
	#endif
}


	



