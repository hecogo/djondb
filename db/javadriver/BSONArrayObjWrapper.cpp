#include "BSONArrayObjWrapper.h"
#include "bson.h"

/*
 * Class:     BSONArrayObjWrapper
 * Method:    create
 * Signature: ()I
 */
JNIEXPORT jlong JNICALL Java_BSONArrayObjWrapper_create
(JNIEnv *env, jobject jobj) {
	BSONArrayObj* obj = new BSONArrayObj();
	return (long)obj;
}

/*
 * Class:     BSONArrayObjWrapper
 * Method:    length
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_BSONArrayObjWrapper_length
(JNIEnv *env, jobject obj, jlong jinstance) {
	BSONArrayObj* instance = (BSONArrayObj*)jinstance;

	return instance->length();
}

/*
 * Class:     BSONArrayObjWrapper
 * Method:    add
 * Signature: (JLBSONObjWrapper;)V
 */
JNIEXPORT void JNICALL Java_BSONArrayObjWrapper_add
(JNIEnv *env, jobject obj, jlong jinstance, jobject jbson) {

	jclass clazzBSONObjWrapper = env->FindClass("BSONObjWrapper");
	jmethodID id = env->GetMethodID(clazzBSONObjWrapper, "instance", "()J");
	BSONObj* ref = (BSONObj*) env->CallLongMethod(jbson, id);

	BSONArrayObj* instance = (BSONArrayObj*)jinstance;
	instance->add(*ref);
}

/*
 * Class:     BSONArrayObjWrapper
 * Method:    get
 * Signature: (JI)LBSONObjWrapper;
 */
JNIEXPORT jobject JNICALL Java_BSONArrayObjWrapper_get
(JNIEnv *env, jobject obj, jlong jinstance, jint jindex) {
	BSONArrayObj* instance = (BSONArrayObj*)jinstance;
	BSONObj* bson = instance->get((int)jindex);

	if (bson != NULL) {
		jclass clazz = env->FindClass("BSONObjWrapper");
		jmethodID jid = env->GetMethodID(clazz, "<init>", "(J)V");
		jobject jbson = env->NewObject(clazz, jid, (long)bson);
		return jbson;
	}

	return NULL;
}

/*
 * Class:     BSONArrayObjWrapper
 * Method:    toChar
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_BSONArrayObjWrapper_toChar
(JNIEnv *env, jobject obj, jlong jinstance) {

	BSONArrayObj* instance = (BSONArrayObj*)jinstance;

	char* str = instance->toChar();
	jstring res = env->NewStringUTF(str);

	return res;
}

