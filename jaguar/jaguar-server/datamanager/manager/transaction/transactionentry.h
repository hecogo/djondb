/* 
 * File:   transactionentry.h
 * Author: cross
 *
 * Created on May 20, 2010, 2:04 PM
 */

#ifndef _TRANSACTIONENTRY_H
#define	_TRANSACTIONENTRY_H

class TransactionEntry {
public:
    TransactionEntry();
    TransactionEntry(const TransactionEntry& orig);
    virtual ~TransactionEntry();
    void setValue(void* _value);
    void* getValue() const;
    void setIdAttribute(int _idAttribute);
    int setIdAttribute() const;
    void setIdEntity(int _idEntity);
    int setIdEntity() const;
    void setId(int _id);
    int setId() const;
    void setIdEntityKey(int _idEntityKey);
    int getIdEntityKey() const;

private:
    int _id;
    int _idEntity;
    int _idAttribute;
    int _idEntityKey;

    void* _value;
};



#endif	/* _TRANSACTIONENTRY_H */

