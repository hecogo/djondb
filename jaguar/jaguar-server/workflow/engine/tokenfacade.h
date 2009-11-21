#ifndef TOKENFACADE_H_INCLUDED
#define TOKENFACADE_H_INCLUDED

#include <list>

using namespace std;

#include "token.h"
#include "tokenvo.h"
class ProcessInstance;

class TokenFacade {
public:
    list<Token*>* processToken(ProcessInstance* processInstance, Token* token);
    Token* findBy(TokenVO token);
};


#endif // TOKENFACADE_H_INCLUDED
