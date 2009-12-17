#ifndef TOKENFACADE_H_INCLUDED
#define TOKENFACADE_H_INCLUDED

#include <list>

using namespace std;

#include "token.h"
#include "tokenvo.h"
class ProcessInstance;

list<Token*>* processToken(ProcessInstance* processInstance, Token* token);
Token* findTokenBy(TokenVO token);
void loadCurrentTokens(ProcessInstance* processInstance);
void persistCurrentTokens(ProcessInstance* processInstance);

#endif // TOKENFACADE_H_INCLUDED
