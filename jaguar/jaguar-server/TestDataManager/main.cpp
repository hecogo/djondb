/* 
 * File:   main.cpp
 * Author: cross
 *
 * Created on May 26, 2010, 11:11 PM
 */

#include <stdlib.h>

#include "dbjaguar.h"
#include "datamanager.h"
#include "util.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

#define ERROR_CHECK() \
if (getLastErrorCode() > 0) { \
    cout << "An error ocurred: " << getLastErrorCode() << ". Description: " << getLastErrorDescription() << endl; \
    exit(1); \
}

EntityMD* createEntities() {
    EntityMD* entityMD = new EntityMD();
    entityMD->setEntityName(new string("Solicitud"));
    entityMD->setEntityType(NORMAL);
    entityMD->setIdEntity(1);
    entityMD->setTableName(new string("solic"));

    EntityMD* customerMD = new EntityMD();
    customerMD->setEntityName(new string("Cliente"));
    customerMD->setEntityType(NORMAL);
    customerMD->setIdEntity(2);
    customerMD->setTableName(new string("customer"));
    vector<AttributeMD*>* reqAttrsCustomer = new vector<AttributeMD*>();
    AttributeMD* attr_cust1 = new AttributeMD();
    attr_cust1->setAttributeName(new string("name"));
    attr_cust1->setAttributeType(AT_VARCHAR);
    reqAttrsCustomer->push_back(attr_cust1);
    customerMD->setAttributesMD(reqAttrsCustomer);

/*
    EntityMD* docTypeMD = new EntityMD();
    docTypeMD->setEntityName(new string("DocType"));
    docTypeMD->setEntityType(BASIC);
    docTypeMD->setIdEntity(3);
    docTypeMD->setTableName(new string("doctype"));
*/
    // Request attributes
    vector<AttributeMD*>* reqAttrs = new vector<AttributeMD*>();

    AttributeMD* attr1 = new AttributeMD();
    attr1->setAttributeName(new string("value"));
    attr1->setAttributeType(AT_INT);
    reqAttrs->push_back(attr1);

    AttributeMD* attr2 = new AttributeMD();
    attr2->setAttributeName(new string("customer"));
    attr2->setAttributeType(AT_INT);
    attr2->setEntityRelated(customerMD);
    reqAttrs->push_back(attr2);

    entityMD->setAttributesMD(reqAttrs);

    return entityMD;
}

int testLoadEntitiesMD() {
    loadEntitiesMD();
    EntityMD* root = getEntityMD(1);
    AttributeMD* attr = root->getAttributeMD("customer.name");
    if (attr != NULL) {
        cout << "found" << endl;
    } else {
        cout << "Error: " << getLastErrorCode() << endl;
        return (EXIT_FAILURE);
    }
    TransactionManager manager;
    Transaction* transaction = manager.startTransaction();
    Entity* request = createEntity(1, transaction);

    cout << "Setting value to: " << 1 << endl;

    request->setValue("value", new int(1));
    ERROR_CHECK();

    int* value = (int*)request->getValue("value");
    ERROR_CHECK();
    cout << "Retrieved Value for 'value': " << *value << endl;

    cout << "Setting customer.name to: pedro" << endl;
    request->setValue("customer.name", new string("pedro"));
    ERROR_CHECK();

    string* name = (string*)request->getValue("customer.name");
    ERROR_CHECK();

    cout << "Retrieved value for 'customer.name': " << *name << endl;

    cout << "Changing value for: 'customer.name' to: juan" << endl;

    request->setValue("customer.name", new string("juan"));
    ERROR_CHECK();
    request->setValue("customer.lastname", new string("crossley"));
    ERROR_CHECK();

    name = (string*)request->getValue("customer.name");
    ERROR_CHECK();
    cout << "Retrieved value for 'customer.name': " << *name << endl;

    name = (string*)request->getValue("customer.lastname");
    ERROR_CHECK();
    cout << "Retrieved value for 'customer.lastname': " << *name << endl;

    delete(transaction);
    delete(request);
    releaseEntitiesMD();
}

void testDeploy() {
    ifstream* f = new ifstream("entities.dat", ifstream::in);
    deployEntities((istream*)f);
    f->close();
    delete(f);
}
/*
 * 
 */
int main(int argc, char** argv) {
    getDefaultMDConnection();
    cout << "enter a number an hit enter" << endl;
    int a;
    cin >> a;
    testDeploy();
    int r = testLoadEntitiesMD();
    cache::cleanGlobalCache();
    if (r) {
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

