#include "networkcommon.h"
#include "util/util.h"

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

