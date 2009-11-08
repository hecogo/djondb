/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.sinco.bpm.workflow;

import com.sinco.bpm.workflow.metadata.Task;
import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author JuanC
 */
public class TransferObjectAssembler {
    public static TransferObjectAssembler instance;
    
    public enum TokenStructure {
        BASIC
    }
    
    public static TransferObjectAssembler getInstance() {
        if (instance == null) {
            instance = new TransferObjectAssembler();
        }
        return instance;
    }
    
    private TransferObjectAssembler() {
        
    }
    
    public List<TokenVO> getToken(TokenStructure struc, List<Token> tokens) {
        ArrayList<TokenVO> res = new ArrayList<TokenVO>();
        for (Token token : tokens) {
            res.add(getToken(struc, token));
        }
        return res;
    }
    
    public TokenVO getToken(TokenStructure struc, Token token) {
        switch (struc) {
            case BASIC:
                return buildBasicTokenVO(token);
            default:
                throw new RuntimeException("Token structure: " + struc + " not supported");
        }
    }


    private TokenVO buildBasicTokenVO(Token token) {
        TokenVO res = new TokenVO();
        res.setId(token.getId());
        res.setStatus(token.getStatus());
        res.setProcessInstance(buildBasicProcessInstance(token.getProcessInstance()));
        res.setTask(buildBasicTaskVO(token.getTask()));
        return res;
    }
    
    private ProcessInstanceVO buildBasicProcessInstance(ProcessInstance process) {
        ProcessInstanceVO vo = new ProcessInstanceVO();
        vo.setId(process.getId());
        vo.setProcessName(process.getProcessDefinition().getDefinitionName());
        return vo;
    }
    
    private TaskVO buildBasicTaskVO(Task task) {
        TaskVO vo = new TaskVO();
        vo.setId(task.getId());
        vo.setTaskName(task.getTaskName());
        vo.setTaskType(task.getTaskType());
        return vo;
    }
}
