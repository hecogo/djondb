/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.sinco.client.model;

import com.sinco.bpm.workflow.InstanceStatus;
import com.sinco.bpm.workflow.ProcessInstance;
import com.sinco.bpm.workflow.TaskVO;
import com.sinco.bpm.workflow.TokenVO;
import com.sinco.bpm.workflow.WorkflowResponse;
import com.sinco.bpm.workflow.metadata.ManualTask;
import com.sinco.bpm.workflow.metadata.ProcessDefinition;
import com.sinco.bpm.workflow.metadata.TaskType;
import com.sinco.cache.CacheFactory;
import com.sinco.client.MetadataHelper;
import com.sinco.client.Server;
import com.sinco.network.NetworkClient;
import com.sinco.network.NetworkException;
import java.net.UnknownHostException;
import java.util.HashMap;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 *
 * @author cross
 */
public class ProcessModel {
    private static Log logger = LogFactory.getLog(ProcessModel.class);
    private Server server;
    MetadataHelper processHelper;
    ProcessStatus processStatus;
    private List<TokenVO> currentTokens;
    private TokenVO currentToken;
    
    public ProcessModel(Server server) {
        this.server = server;
        this.processStatus = ProcessStatus.NOT_STARTED;
        processHelper = new MetadataHelper(server);
    }

    public void createInstance(ProcessDefinition processDefinition) {
        try {
            NetworkClient client = new NetworkClient();
            Object[] response = client.sendReceive(server.getHostAddress(), server.getHostPort(), 102L, new Object[]{processDefinition.getId()});
            WorkflowResponse workflowResponse = (WorkflowResponse) response[0];
            this.currentTokens = workflowResponse.getCurrentTokens();
            if (getCurrentTokens().size() > 0) {
                processStatus = ProcessStatus.RUNNING;
            }
            refreshCurrentToken();
        } catch (UnknownHostException ex) {
            throw new RuntimeException(ex);
        } catch (NetworkException ex) {
            throw new RuntimeException(ex);
        }
    }

    public Class getCurrentFormId() {
        // Temporal implementation
        TaskVO taskVO = getCurrentToken().getTask();
        HashMap<Long, Class> taskFormByIdTask = (HashMap<Long, Class>) CacheFactory.getGlobalCache("METADATA").get("TASKFORMS");
        
        Class formClass = taskFormByIdTask.get(taskVO.getId());
        return formClass;
    }

    public TokenVO getCurrentToken() {
        return currentToken;
    }
    
    public ProcessDefinition[] getProcessDefinitions() {
        try {
            return processHelper.getProcessDefinitions();
        } catch (UnknownHostException ex) {
            throw new RuntimeException(ex);
        } catch (NetworkException ex) {
            throw new RuntimeException(ex);
        }
    }

    public Server getServer() {
        return server;
    }

    public void processCurrentToken() {
        try {
            NetworkClient client = new NetworkClient();
            
            Object[] parameters = new Object[]{ getCurrentToken() };
            Object[] response = client.sendReceive(server.getHostAddress(), server.getHostPort(), 103L, parameters );
            WorkflowResponse workflowResponse = (WorkflowResponse) response[0];
            this.currentTokens = workflowResponse.getCurrentTokens();
            refreshCurrentToken();
            if (getCurrentTokens().size() > 0) {
                processStatus = ProcessStatus.RUNNING;
            } else {
                processStatus = processStatus.CLOSED;
            }
        } catch (UnknownHostException ex) {
            throw new RuntimeException(ex);
        } catch (NetworkException ex) {
            throw new RuntimeException(ex);
        }
    }

    public void setServer(Server server) {
        this.server = server;
    }
    
    public ProcessStatus getProcessStatus() {
        return processStatus;
    }

    public List<TokenVO> getCurrentTokens() {
        return currentTokens;
    }

    private void refreshCurrentToken() {
        currentToken = null;
        for (TokenVO vo : currentTokens) {
            if (vo.getTask().getTaskType().equals(TaskType.MANUAL)) {
                currentToken = vo;
                break;
            }
        }
    }
    
}
