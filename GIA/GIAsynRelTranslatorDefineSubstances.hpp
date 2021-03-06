/*******************************************************************************
 *
 * No License
 * 
 * This work is under exclusive copyright (c) Baxter AI (baxterai.com). 
 * Nobody else can use, copy, distribute, or modify this work without being 
 * at risk of take-downs, shake-downs, or litigation. 
 * 
 * By publishing this source code in a public repository on GitHub, Terms of 
 * Service have been accepted by which Baxter AI have allowed others to view 
 * and fork their repository.
 * 
 * If you find software that doesn't have a license, that generally means you 
 * have no permission from the creators of the software to use, modify, or 
 * share the software. Although a code host such as GitHub may allow you to 
 * view and fork the code, this does not imply that you are permitted to use, 
 * modify, or share the software for any purpose.
 *
 * This notice has been derived from https://choosealicense.com/no-permission 
 * (https://web.archive.org/web/20180312144938/https://choosealicense.com/no-permission)
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: GIAsynRelTranslatorDefineSubstances.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2021 Baxter AI (baxterai.com)
 * Project: General Intelligence Algorithm
 * Project Version: 3p5a 20-May-2021
 * Requirements: requires text parsed by NLP Parser (eg Relex; available in .CFF format <relations>)
 * Description: Syntactic Relation Translator - Converts relation objects into GIA nodes (of type entity, action, condition etc) in GIA network/tree
 * /
 *******************************************************************************/


#ifndef HEADER_GIA_SYN_REL_TRANSLATOR_DEFINE_SUBSTANCES
#define HEADER_GIA_SYN_REL_TRANSLATOR_DEFINE_SUBSTANCES

#include "GIAglobalDefs.hpp"
#include "GIAsentenceClass.hpp"
#include "GIAentityNodeClass.hpp"
#include "GIAentityConnectionClass.hpp"
#include "GIAconditionNodeClass.hpp"
#include "GIAtranslatorOperations.hpp"
#include "GIAdatabase.hpp"
#include "GIAsynRelTranslatorGeneric.hpp"

class GIAsynRelTranslatorDefineSubstancesClass
{
	private: GIAtranslatorOperationsClass GIAtranslatorOperations;
	private: GIAsynRelTranslatorGenericClass GIAsynRelTranslatorGeneric;

	//these had to be separated out from the above because they are used by GIAsemRelTranslatorParser.cpp;
	public: void defineSubstancesAllNodes(GIAtranslatorVariablesClass* translatorVariables);
	#ifdef GIA_SPECIFIC_ACTION_NETWORK_INDEXES
	public: void defineSubstancesActionNetworkIndexes(GIAtranslatorVariablesClass* translatorVariables);
	#endif
};


#endif
