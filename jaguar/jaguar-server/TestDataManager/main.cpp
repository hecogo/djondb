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

using namespace std;

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
    attr_cust1->setAttributeType(VARCHAR);
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
    attr1->setAttributeType(INT);
    reqAttrs->push_back(attr1);

    AttributeMD* attr2 = new AttributeMD();
    attr2->setAttributeName(new string("customer"));
    attr2->setAttributeType(INT);
    attr2->setEntityRelated(customerMD);
    reqAttrs->push_back(attr2);

    entityMD->setAttributesMD(reqAttrs);

    return entityMD;
}
/*
 * 
 */
int main(int argc, char** argv) {
    getDefaultMDConnection();
    int a;
    cin >> a;
    loadEntitiesMD();
    EntityMD* root = getEntityMD(1);
    AttributeMD* attr = root->getAttributeMD("customer.name");
    if (attr != NULL) {
        cout << "found" << endl;
    } else {
        cout << "Error: " << getLastErrorCode() << endl;
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

