/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.sinco.persistence;

import com.sinco.cache.CacheFactory;
import java.beans.IntrospectionException;
import java.beans.PropertyDescriptor;
import java.lang.annotation.Annotation;
import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.lang.reflect.Modifier;
import java.lang.reflect.UndeclaredThrowableException;
import java.util.ArrayList;
import java.util.Arrays;

/**
 *
 * @author cross
 */
class ReflectorUtility {

    public PropertyDescriptor getPrimaryKeyDescriptor(Object entity) {
        try {
            Method[] methods = entity.getClass().getMethods();

            Method primarykeyGetMethod = null;
            for (Method method : methods) {
                Annotation ann = method.getAnnotation(Id.class);
                if (ann != null) {
                    primarykeyGetMethod = method;
                    break;
                }
            }
            if (primarykeyGetMethod == null) {
                throw new IllegalArgumentException("Entity " + entity.toString() + " does not have any id field");
            }

            if (primarykeyGetMethod.getParameterTypes().length > 0) {
                throw new IllegalArgumentException("Invalid primarykey method definition, it must not have any return arguments");
            }

            String getMethodName = primarykeyGetMethod.getName();
            String propertyName = getMethodName;
            String setMethodName = null;
            if (getMethodName.startsWith("get")) {
                propertyName = getMethodName.substring(3);
                char[] array = propertyName.toCharArray();
                if ((array[0] >= 'A') && (array[0] <= 'Z')) {
                    array[0] = (char) ((int) array[0] + ('a' - 'A'));
                }
                propertyName = String.valueOf(array, 0, array.length);
                setMethodName = "set" + getMethodName.substring(3);
            }
            Class returnType = primarykeyGetMethod.getReturnType();

            Method primarykeySetMethod = null;
            try {
                primarykeySetMethod = entity.getClass().getMethod(setMethodName, new Class[]{returnType});
            } catch (NoSuchMethodException e) {
                // Expected if the property is a readonly property
            }
            PropertyDescriptor descriptor = new PropertyDescriptor(propertyName, primarykeyGetMethod, primarykeySetMethod);

            return descriptor;
        } catch (IntrospectionException e) {
            throw new PersistenceException(e);
        }
    }

    public Object getPrimaryKey(Object entity) {
        try {
            Method primaryKeyMethod = getPrimaryKeyDescriptor(entity).getReadMethod();
            Object primaryKey = primaryKeyMethod.invoke(entity, new Object[]{});
            if (primaryKey == null) {
                return null;
            } else {
                if ((primaryKey instanceof Number) && (((Number)primaryKey).longValue() == 0)) {
                    return null;
                } else {
                    return primaryKey;
                }
            }
        } catch (IllegalAccessException e) {
            throw new PersistenceException(e);
        } catch (IllegalArgumentException e) {
            throw new PersistenceException(e);
        } catch (InvocationTargetException e) {
            throw new PersistenceException(e);
        }
    }
    
    public void validateEntity(Class entityClazz) {
        if (!entityClazz.isAnnotationPresent(Entity.class)) {
            throw new PersistenceException(String.format("The class %s is not annotated as com.sinco.persistence.Entity"));
        }
    }
    
    public void validateEntity(Object entity) {
        validateEntity(entity.getClass());
    }
    
    private ArrayList<Field> getAllFields(Class clazz) {
        ArrayList<Field> result = new ArrayList<Field>(Arrays.asList(clazz.getDeclaredFields()));
        if (!Object.class.equals(clazz.getSuperclass())) {
            result.addAll(getAllFields(clazz.getSuperclass()));
        }
        return result;
    }
    
    public Field[] getFields(Object entity, boolean accessibles) {
        return getFields(entity.getClass(), accessibles);
    }
    
    @SuppressWarnings("unchecked")
    public Field[] getFields(Class clazz, boolean accessibles) {
        validateEntity(clazz);
        
        Field[] cachedFields = (Field[]) CacheFactory.getGlobalCache("ENTITY_FIELDS").get(clazz.getName() + "@" + accessibles);
        if (cachedFields != null) {
            return cachedFields;
        }
        ArrayList<Field> fields = getAllFields(clazz);
        
        ArrayList<Field> result = new ArrayList<Field>();
        for (Field field : fields) {
            if (((field.getModifiers() & Modifier.TRANSIENT) == 0) &&
                ((field.getModifiers() & Modifier.FINAL) == 0)) { // is not transient
                field.setAccessible(accessibles);
                result.add(field);
            }
        }
        Field[] resultFields = result.toArray(new Field[] {});
        CacheFactory.getGlobalCache("ENTITY_FIELDS").add(clazz.getName() + "@" + accessibles, resultFields);
        return resultFields;
    }
    
    public Field getField(Class clazz, String fieldName, boolean accessible) throws NoSuchFieldException {
        Field[] fields = getFields(clazz, accessible);
        for (Field field : fields) {
            if (field.getName().equals(fieldName)) {
                return field;
            }
        }
        throw new java.lang.NoSuchFieldException("Field: " + fieldName);
    }
}
