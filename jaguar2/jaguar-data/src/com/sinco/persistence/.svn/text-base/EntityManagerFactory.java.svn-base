/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.sinco.persistence;

/**
 *
 * @author cross
 */
public class EntityManagerFactory {

    public static EntityManager getEntityManager(EntityManagerType type) {
        switch (type) {
            case METADATA:
                return new HashEntityManager();
            case DATA:
                return new DataEntityManager();
            default:
                throw new IllegalArgumentException(String.format("Type %s not supported.", type));
        }
    }
}
