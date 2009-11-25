#include "util.h"
#include <stdlib.h>
#include "wfruntime.h"
#include "engine/token.h"
#include "engine/processinstance.h"
#include "net/response.h"
#include "net/request.h"
#include "net/controller.h"

Response* createResponse(ProcessInstance* instance) {
    string *s = new string();
    s->append("PROC:{" + toString(instance->getId()) + ";");
    list<Token*>* currentTokens = instance->getCurrentTokens();
    s->append("TOKENS:{");
    for (list<Token*>::iterator iter = currentTokens->begin(); iter != currentTokens->end(); iter++) {
        Token* token = *iter;
        s->append("TOKEN:");
        s->append(toString(token->getId()) + ";");
        s->append(*token->getTask()->getTaskName() + ";");
    }
    s->append("}");
    s->append("}");
    Response *response = new Response(s);
    return response;
}

class WorkflowController : public Controller {
private:
    Logger* log;
public:
    WorkflowController(int _requestType) : Controller(_requestType) {
        log = getLogger(NULL);
    };

    Response* processRequest(Request* request) {
        string* action = request->getParameter("ACT");
        if (action->compare("NEW") == 0) {
            if (log->isDebug()) log->debug("Request NEW received.");
            int procDef = atoi(request->getParameter("DEFI")->c_str());
            if (log->isDebug()) log->debug("process id: " + toString(procDef));
            ProcessInstance* instance = createProcessInstance(procDef);
            
            return createResponse(instance);
        } else if (action->compare("PROC")) {
        }
        Response* response = new Response(new string("Testing from workflow controller"));
        return response;
    }
};

void AddWorkflow() {
    WorkflowController* controller = new WorkflowController(1);
    controller->selfRegister();
};

