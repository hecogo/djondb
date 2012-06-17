/*
 * =====================================================================================
 *
 *       Filename:  ConnectionWrapper.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/28/2012 08:21:47 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include "ConnectionWrapper.h"
#include "djondb_client.h"

using namespace djondb;

/*
 * Class:     ConnectionWrapper
 * Method:    open
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_ConnectionWrapper_open
  (JNIEnv *env, jobject obj, jlong connection) {
	  Connection* con = (Connection*)connection;
	  bool result = con->open();
	  return (jboolean)result;
}

/*
 * Class:     ConnectionWrapper
 * Method:    close
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_ConnectionWrapper_close
  (JNIEnv *env, jobject obj, jlong connection) {
	  Connection* con = (Connection*)connection;
	  con->close();
}

/*
 * Class:     ConnectionWrapper
 * Method:    internalClose
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_ConnectionWrapper_internalClose
  (JNIEnv *env, jobject obj, jlong connection) {
	  Connection* con = (Connection*)connection;
	  con->internalClose();
}

/*
 * Class:     ConnectionWrapper
 * Method:    isOpen
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_ConnectionWrapper_isOpen
  (JNIEnv *env, jobject obj, jlong connection) {
	  Connection* con = (Connection*)connection;
	  jboolean result = (jboolean)con->isOpen();
	  return result;
  }

/*
 * Class:     ConnectionWrapper
 * Method:    insert
 * Signature: (JLjava/lang/String;Ljava/lang/String;Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_ConnectionWrapper_insert__JLjava_lang_String_2Ljava_lang_String_2Ljava_lang_String_2
(JNIEnv *env, jobject obj, jlong jconnection, jstring jdb, jstring jns, jstring jjson) {
	Connection* con = (Connection*)jconnection;

	jboolean iscopy;
	const char* db = env->GetStringUTFChars(jdb, &iscopy);
	const char* ns = env->GetStringUTFChars(jns, &iscopy);
	const char* json = env->GetStringUTFChars(jjson, &iscopy);
	
	jboolean result = (jboolean)con->insert(db, ns, json);

	env->ReleaseStringUTFChars(jdb, db);
	env->ReleaseStringUTFChars(jns, ns);
	env->ReleaseStringUTFChars(jjson, json);

}

/*
 * Class:     ConnectionWrapper
 * Method:    insert
 * Signature: (JLjava/lang/String;Ljava/lang/String;LBSONObjWrapper;)Z
 */
JNIEXPORT jboolean JNICALL Java_ConnectionWrapper_insert__JLjava_lang_String_2Ljava_lang_String_2LBSONObjWrapper_2
(JNIEnv *env, jobject obj, jlong jconnection, jstring jdb, jstring jns, jobject jbson) {

}

/*
 * Class:     ConnectionWrapper
 * Method:    findByKey
 * Signature: (JLjava/lang/String;Ljava/lang/String;Ljava/lang/String;)LBSONObjWrapper;
 */
JNIEXPORT jobject JNICALL Java_ConnectionWrapper_findByKey
(JNIEnv *env, jobject obj, jlong jconnection, jstring jdb, jstring jns, jstring jid) {
	Connection* con = (Connection*)jconnection;

	jboolean iscopy;
	const char* db = env->GetStringUTFChars(jdb, &iscopy);
	const char* ns = env->GetStringUTFChars(jns, &iscopy);
	const char* id = env->GetStringUTFChars(jid, &iscopy);
	
	BSONObj* bson = (BSONObj*)con->findByKey(db, ns, id);

	env->ReleaseStringUTFChars(jdb, db);
	env->ReleaseStringUTFChars(jns, ns);
	env->ReleaseStringUTFChars(jid, id);

	// Create the Java Wrapper for connection
	jclass clazzBSONObjWrapper = env->FindClass("BSONObjWrapper");
	jmethodID mid = env->GetMethodID(clazzBSONObjWrapper, "<init>", "(J)V");
	jobject bsonobj = env->NewObject(clazzBSONObjWrapper, mid, (long)bson);

	return bsonobj;
}

/*
 * Class:     ConnectionWrapper
 * Method:    find
 * Signature: (JLjava/lang/String;Ljava/lang/String;Ljava/lang/String;)Ljava/util/ArrayList;
 */
JNIEXPORT jobject JNICALL Java_ConnectionWrapper_find
(JNIEnv *env, jobject obj, jlong jconnection, jstring jdb, jstring jns, jstring jfilter) {
	Connection* con = (Connection*)jconnection;

	jboolean iscopy;
	const char* db = env->GetStringUTFChars(jdb, &iscopy);
	const char* ns = env->GetStringUTFChars(jns, &iscopy);
	const char* filter = env->GetStringUTFChars(jfilter, &iscopy);
	
	std::vector<BSONObj*> array = con->find(db, ns, filter);

	env->ReleaseStringUTFChars(jdb, db);
	env->ReleaseStringUTFChars(jns, ns);
	env->ReleaseStringUTFChars(jfilter, filter);

	// Create the Java Wrapper for connection
	jclass clazzArrayList = env->FindClass("java/util/ArrayList");
	jclass clazzBSONObjWrapper = env->FindClass("BSONObjWrapper");
	jmethodID minitArray = env->GetMethodID(clazzArrayList, "<init>", "()V");
	jmethodID minitBSON = env->GetMethodID(clazzBSONObjWrapper, "<init>", "(J)V");
	jobject jarraylist = env->NewObject(clazzArrayList, minitArray);
	
	jmethodID madd = env->GetMethodID(clazzArrayList, "add", "(Ljava/lang/Object;)Z");

	for (std::vector<BSONObj*>::iterator i = array.begin(); i != array.end(); i++) {
		BSONObj* element = *i;

		jobject bsonwrapper = env->NewObject(clazzBSONObjWrapper, minitBSON, (long)element);
		env->CallVoidMethod(jarraylist, madd, bsonwrapper);
	}

	return jarraylist;
}

/*
 * Class:     ConnectionWrapper
 * Method:    update
 * Signature: (JLjava/lang/String;Ljava/lang/String;Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_ConnectionWrapper_update__JLjava_lang_String_2Ljava_lang_String_2Ljava_lang_String_2
(JNIEnv *, jobject, jlong, jstring, jstring, jstring) {
}

/*
 * Class:     ConnectionWrapper
 * Method:    update
 * Signature: (JLjava/lang/String;Ljava/lang/String;LBSONObjWrapper;)Z
 */
JNIEXPORT jboolean JNICALL Java_ConnectionWrapper_update__JLjava_lang_String_2Ljava_lang_String_2LBSONObjWrapper_2
(JNIEnv *, jobject, jlong, jstring, jstring, jobject) {
}

/*
 * Class:     ConnectionWrapper
 * Method:    dropNamespace
 * Signature: (JLjava/lang/String;Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_ConnectionWrapper_dropNamespace
(JNIEnv *, jobject, jlong, jstring, jstring) {
}

/*
 * Class:     ConnectionWrapper
 * Method:    host
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_ConnectionWrapper_host
(JNIEnv *, jobject, jlong) {
}

