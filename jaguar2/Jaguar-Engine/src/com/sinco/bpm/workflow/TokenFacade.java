/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.sinco.bpm.workflow;

import com.sinco.bpm.workflow.metadata.CommonConector;
import com.sinco.bpm.workflow.metadata.ConnectorTargetable;
import com.sinco.bpm.workflow.metadata.Task;
import com.sinco.bpm.workflow.metadata.TaskType;
import com.sinco.persistence.EntityManager;
import com.sinco.persistence.EntityManagerFactory;
import com.sinco.persistence.EntityManagerType;
import com.sinco.persistence.EntityNotFoundException;
import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author cross
 */
public class TokenFacade {

    EntityManager entityManager;
    
    public TokenFacade() {
        entityManager = EntityManagerFactory.getEntityManager(EntityManagerType.DATA);
    }
    
    public Token findBy(TokenVO token) throws EntityNotFoundException {
        return entityManager.find(Token.class, token.getId());
    }

    public List<Token> processToken(ProcessInstance instance, Token token) {
        List<Token> res = new ArrayList<Token>();
        if (token.getStatus().equals(TokenStatus.USER)) {
            executePostUser(token);
        }
        res.add(token);
        while ((token = getNextStatus(res)) != null) {
            res.remove(token);
            if (token.getStatus().equals(TokenStatus.NONE)) {
                executeStart(token);
            }
            if (token.getStatus().equals(TokenStatus.STARTED) 
                    && (token.getTask().getTaskType().equals(TaskType.MANUAL))) {
                token.setStatus(TokenStatus.USER);
                res.add(token);
            }
            if (token.getStatus().equals(TokenStatus.STARTED)
                    || token.getStatus().equals(TokenStatus.POSTUSER)) {
                executeEnd(token);
                res.remove(token);
                // Replaces the exit tokens with the new ones
                res.addAll(getNextTokens(instance, token));
            }
        }
        return res;
    }

    private void executePostUser(Token token) {
        token.setStatus(TokenStatus.POSTUSER);
    }

    private Token getNextStatus(List<Token> tokens) {
        for (Token token : tokens) {
            if (token.getStatus().equals(TokenStatus.NONE)) {
                return token;
            }
            if (token.getStatus().equals(TokenStatus.POSTUSER)) {
                return token;
            }
        }
        return null;
    }

    private void executeEnd(Token token) {
        token.setStatus(TokenStatus.ENDED);
    }

    private void executeStart(Token token) {
        token.setStatus(TokenStatus.STARTED);
//        Task task = token.getTask();
    }

    private List<Token> getNextTokens(ProcessInstance processInstance, Token token) {
        List<CommonConector> sequenceFlows = token.getTask().getSequenceFlows();
        ArrayList<Token> result = new ArrayList<Token>();
        for (CommonConector connector : sequenceFlows) {
            ConnectorTargetable target = connector.getTarget();
            if (target instanceof Task) {
                Task task = (Task) target;
                Token newToken;
                if (result.size() == 0) {
                    newToken = token;
                } else {
                    newToken = new Token();
                }
                newToken.setProcessInstance(processInstance);
                newToken.setStatus(TokenStatus.NONE);
                newToken.setTask(task);
                processInstance.addCurrentToken(newToken);
                result.add(newToken);
            }
        }
        return result;
    }
}
