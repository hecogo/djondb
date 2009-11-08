/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.sinco.network;

import java.io.Serializable;

/**
 *
 * @author cross
 */
class InvalidRequestException extends Exception implements Serializable {

    public InvalidRequestException(String message) {
        super(message);
    }

}
