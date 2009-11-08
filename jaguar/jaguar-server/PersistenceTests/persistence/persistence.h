/* 
 * File:   persistence.h
 * Author: cross
 *
 * Created on November 20, 2008, 9:57 PM
 */
#include <string.h>
#include <vector>
#include <map>

using namespace std;

class EntityManager {
public:
    Query createNamedQuery(string string);

    Query createQuery(string string);

    void find(void* obj, int id); // throws EntityNotFoundException;

    vector<typename> findAll(typename aClass);

    void persist(void* entity);
    void merge(void* entity);
    void remove(void* entity);
};

enum EntityManagerType {
    METADATA,
    DATA
};

EntityManager* getEntityManager(EntityManagerType type);

class EntityRecord {
private:
    string entityClass;
    void* primaryKey;
public:
    EntityRecord(string _entityClass, void* _primaryKey);
    string getEntityClass();
    void* getPrimaryKey();
};


class FieldRecord {
private:
    string fieldName;
    void* value;
    
public:
    FieldRecord(string _fieldName, void* _value) {
        this.fieldName = _fieldName;
        this.value = _value;
    }

    string getFieldName() {
        return fieldName;
    }

    void* getValue() {
        return value;
    }
};

class HashEntityManager : EntityManager {
private:
    map<string, void*> entities;
    int serializationReentranceCount;
    string dirRoot;
    

    Query createNamedQuery(string string);
    Query createQuery(string string);

    vector<void*> deserializeArray(vector<void*> collection);

    string getKey(type aClass, Object id);

    <T> T find(Class<T> aClass, Object primaryKey) throws EntityNotFoundException {
        HashMap<String, Object> reentrance = (HashMap<String, Object>) CacheFactory.getRuntimeCache().get("SERIALIZATIONREENTRANCE");
        if (reentrance == null) {
            reentrance = new HashMap<String, Object>();
            CacheFactory.getRuntimeCache().add("SERIALIZATIONREENTRANCE", reentrance);
        }
        string reentranceKey = getKey(aClass, primaryKey);
        if (reentrance.get(reentranceKey) != null) {
            return (T) reentrance.get(reentranceKey);
        }
        T ret = (T) entities.get(getKey(aClass, primaryKey));
        if (ret == null) {
            try {
                ret = (T) deserialize(aClass, primaryKey);
            } catch (FileNotFoundException ex) {
                throw new EntityNotFoundException(aClass, primaryKey);
            }
            if (ret != null) {
                entities.put(getKey(ret.getClass(), primaryKey), ret);
            }
        }
        if (ret == null) {
            throw new EntityNotFoundException(aClass, primaryKey);
        }
        return ret;
    }

    private PersistenceStatus getPersistenceStatus(Object entity) {
        ReflectorUtility reflector = new ReflectorUtility();
        reflector.validateEntity(entity);
        try {
            // Temporal
            Object recoveredEntity = find(entity.getClass(), reflector.getPrimaryKey(entity));
            if (recoveredEntity.hashCode() == entity.hashCode()) {
                return PersistenceStatus.UPDATE;
            } else {
                return PersistenceStatus.MODIFIED;
            }
        } catch (EntityNotFoundException ex) {
            return PersistenceStatus.NEW;
        }
    }

    <T> T persist(T entity) {
        try {
            ReflectorUtility reflectorUtility = new ReflectorUtility();
            Object primaryKey = reflectorUtility.getPrimaryKey(entity);
            PersistenceStatus persistenceStatus;
            HashMap<String, Object> reentrance = (HashMap<String, Object>) CacheFactory.getRuntimeCache().get("SERIALIZATIONREENTRANCE");
            if (reentrance == null) {
                reentrance = new HashMap<String, Object>();
                CacheFactory.getRuntimeCache().add("SERIALIZATIONREENTRANCE", reentrance);
            }
            if (primaryKey == null) {
                persistenceStatus = PersistenceStatus.NEW;
            } else {
                string reentranceKey = getKey(entity.getClass(), primaryKey);
                if (reentrance.get(reentranceKey) != null) {
                    return (T) reentrance.get(getKey(entity.getClass(), primaryKey));
                }
                persistenceStatus = getPersistenceStatus(entity);
                reentrance.put(reentranceKey, entity);
            }
            if (persistenceStatus == PersistenceStatus.NEW) {
                if (primaryKey == null) {
                    primaryKey = IdGenerator.getNextId(entity.getClass().getCanonicalName());
                    PropertyDescriptor primaryKeyDescriptor = reflectorUtility.getPrimaryKeyDescriptor(entity);
                    primaryKeyDescriptor.getWriteMethod().invoke(entity, primaryKey);
                }

                string reentranceKey = getKey(entity.getClass(), primaryKey);
                reentrance.put(reentranceKey, entity);

                serializationReentranceCount++;

                serialize(entity);
                serializationReentranceCount--;
            } else {
                if (persistenceStatus.equals(PersistenceStatus.MODIFIED)) {
                    System.out.println("TO BE UPDATED");
                } else {
                    System.out.println("NOTHING TO DO");
                }
            //merge(entity);
            }

            entities.put(getKey(entity.getClass(), primaryKey), entity);
            return entity;
        } catch (IllegalAccessException ex) {
            throw new PersistenceException(ex);
        } catch (IllegalArgumentException ex) {
            throw new PersistenceException(ex);
        } catch (InvocationTargetException ex) {
            throw new PersistenceException(ex);
        } finally {
            if (serializationReentranceCount == 0) {
                CacheFactory.getRuntimeCache().remove("SERIALIZATIONREENTRANCE");
            }
        }
    }

    <T> T merge(T entity) {
        return null;
    }

    void remove(Object entity) {
    }

    private string getFileName(Object entity) {
        ReflectorUtility reflectorUtility = new ReflectorUtility();
        Object primaryKey = reflectorUtility.getPrimaryKey(entity);
        string name = getFileName(entity.getClass(), primaryKey);

        return name;
    }

    private string getFileName(Class aClass, Object primaryKey) {
        string name = dirRoot + aClass.getName() + "_" + primaryKey.toString();

        File dir = new File("data");
        if (!dir.exists()) {
            dir.mkdir();
        }
        return name;
    }

    private Object deserialize(Class entityClazz, Object primaryKey) throws FileNotFoundException, EntityNotFoundException {
        FileInputStream fis = null;
        try {
            fis = new FileInputStream(getFileName(entityClazz, primaryKey));
            ObjectInputStream ois = new ObjectInputStream(fis);
            ois.readObject().toString();
            Object result = entityClazz.newInstance();

            ReflectorUtility reflectorUtility = new ReflectorUtility();
            final Method writeMethod = reflectorUtility.getPrimaryKeyDescriptor(result).getWriteMethod();
            if (writeMethod != null) {
                writeMethod.invoke(result, new Object[]{primaryKey});
            }

            // Adds the current loading entity to avoid reentrance
            entities.put(getKey(entityClazz, primaryKey), result);

            Object record = ois.readObject();
            while ((!(record instanceof String)) && (!record.toString().equals("EOF"))) {
                Object value;
                string fieldName;
                if (!(record instanceof FieldRecord)) {
                    throw new IllegalArgumentException(String.format("The field contains a non valid value. Row: %s", record.toString()));
                }
                fieldName = ((FieldRecord) record).getFieldName();
                value = ((FieldRecord) record).getValue();
                if (value instanceof EntityRecord) {
                    EntityRecord entityRecord = (EntityRecord) value;
                    value = find(Class.forName(entityRecord.getEntityClass()), entityRecord.getPrimaryKey());
                } else if (value instanceof Collection) {
                    value = deserializeArray((Collection) value);
                }
                Field field;
                try {
                    field = reflectorUtility.getField(entityClazz, fieldName, true);
                    field.set(result, value);
                } catch (NoSuchFieldException ex) {
                    // This could happen when the field was erased from the original entity
                }
                record = ois.readObject();
            }
            ois.close();
            fis.close();
            return result;
        } catch (IllegalAccessException ex) {
            throw new RuntimeException(ex);
        } catch (IllegalArgumentException ex) {
            throw new RuntimeException(ex);
        } catch (InvocationTargetException ex) {
            throw new RuntimeException(ex);
        } catch (FileNotFoundException ex) {
            throw ex;
        } catch (IOException ex) {
            throw new RuntimeException(ex);
        } catch (ClassNotFoundException ex) {
            throw new RuntimeException(ex);
        } catch (InstantiationException ex) {
            throw new RuntimeException(ex);
        } finally {
            if (fis != null) {
                try {
                    fis.close();
                } catch (IOException ex) {
                }
            }
        }
    }

    @SuppressWarnings("unchecked")
    private void serialize(Object entity) {
        ReflectorUtility reflectorUtility = new ReflectorUtility();
        FileOutputStream fos = null;
        try {
            fos = new FileOutputStream(getFileName(entity));
            ObjectOutputStream oos = new ObjectOutputStream(fos);
            oos.writeObject(entity.getClass().getName());
            Field[] fields = reflectorUtility.getFields(entity, true);
            for (Field field : fields) {
                Class type = field.getType();
                Object value = field.get(entity);
                if (value != null) {
                    if (value.getClass().isAnnotationPresent(Entity.class)) {
                        persist(value);
                        value = new EntityRecord(value.getClass().getName(), reflectorUtility.getPrimaryKey(value));
                    } else if (type.isPrimitive() || type.getName().equals("java.lang.String") || Enum.class.isAssignableFrom(type)) {
                        value = field.get(entity);
                    } else if (Collection.class.isAssignableFrom(type)) {
                        value = serializeArray(oos, (Collection) field.get(entity));
                    } else {
                        throw new IllegalArgumentException(String.format("Unsupported type: %s", value.getClass().getName()));
                    }
                }
                FieldRecord record = new FieldRecord(field.getName(), value);
                oos.writeObject(record);
            }

            oos.writeObject("EOF");
            oos.close();
        } catch (IllegalArgumentException e) {
            throw new RuntimeException(e);
        } catch (IllegalAccessException e) {
            throw new RuntimeException(e);
        } catch (IOException e) {
            throw new RuntimeException(e);
        } finally {
            if (fos != null) {
                try {
                    fos.close();
                } catch (IOException ex) {
                }
            }
        }
    }

    private ArrayList serializeArray(ObjectOutputStream oos, Collection collection) {
        if (collection == null) {
            return null;
        }
        ArrayList result = new ArrayList(collection.size());
        ReflectorUtility reflector = new ReflectorUtility();
        for (Iterator iter = collection.iterator(); iter.hasNext();) {
            Object element = iter.next();
            if (element.getClass().isAnnotationPresent(Entity.class)) {
                persist(element);
                EntityRecord record = new EntityRecord(element.getClass().getName(), reflector.getPrimaryKey(element));
                result.add(record);
            } else {
                result.add(element);
            }
        }

        return result;
    }

    <T> Collection<T> findAll(Class<T> aClass) {
        final string entityName = aClass.getName();
        File dir = new File(dirRoot);
        File[] listFiles = dir.listFiles(new FileFilter() {

            boolean accept(File pathname) {

                string fileName = pathname.getName();
//                if (fileName.contains(".")) {
//                    fileName = fileName.substring(0, fileName.lastIndexOf("."));
//                }
                if (fileName.contains(File.separator)) {
                    fileName = fileName.substring(fileName.lastIndexOf(File.separator + 1));
                }
                if (fileName.startsWith(entityName)) {
                    return true;
                } else {
                    return false;
                }
            }
        });

        ArrayList<T> result = new ArrayList<T>();
        for (File entityFile : listFiles) {
            try {
                string primaryKey = entityFile.getName();
                primaryKey = primaryKey.substring(primaryKey.indexOf(entityName + "_") + entityName.length() + 1);
                Object entity = deserialize(aClass, primaryKey);
                result.add((T) entity);
            } catch (FileNotFoundException ex) {
                throw new RuntimeException(ex);
            } catch (EntityNotFoundException ex) {
                // The entity will be found
            }
        }

        return result;
    }
}
