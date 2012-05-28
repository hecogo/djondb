#include "ConnectionManagerWrapper.h"
#include "djondb_client.h"
#include <string.h>
#include <iostream>

using namespace djondb;

/*
 * Class:     ConnectionManagerWrapper
 * Method:    getConnection
 * Signature: (Ljava/lang/String;)LConnectionWrapper;
 */
JNIEXPORT jobject JNICALL Java_ConnectionManagerWrapper_getConnection
  (JNIEnv *env, jclass cl, jstring host) {
	  jboolean iscopy;
	  const char* chost = env->GetStringUTFChars(host, &iscopy);

	  Connection* con = ConnectionManager::getConnection(std::string(chost));

	  if (con == NULL) {
		  cout << "NULL" << endl;
	  }
	  // Create the Java Wrapper for connection
	  jclass clazzConnectionWrapper = env->FindClass("ConnectionWrapper");
	  jmethodID id = env->GetMethodID(clazzConnectionWrapper, "<init>", "(J)V");
	  jobject connectionWrapper = env->NewObject(clazzConnectionWrapper, id, (long)con);

	  env->ReleaseStringUTFChars(host, chost);

	  return connectionWrapper;
  }

/*
 * Class:     ConnectionManagerWrapper
 * Method:    releaseConnection
 * Signature: (LConnectionWrapper;)V
 */
JNIEXPORT void JNICALL Java_ConnectionManagerWrapper_releaseConnection
  (JNIEnv *env, jclass cl, jobject connection) {

  }
