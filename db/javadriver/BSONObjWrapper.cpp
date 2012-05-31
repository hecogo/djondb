#include "BSONObjWrapper.h"
#include "bson.h"

/*
 * Class:     BSONObjWrapper
 * Method:    add
 * Signature: (JLjava/lang/String;I)V
 */
JNIEXPORT void JNICALL Java_BSONObjWrapper_add__JLjava_lang_String_2I
  (JNIEnv *env, jobject jobj, jlong jinstance,jstring jkey, jint ji){
	  BSONObj* obj = (BSONObj*)jinstance;
	  
	  jboolean iscopy;
	  int i = (int)ji;
	  const char* key = env->GetStringUTFChars(jkey, &iscopy);

	  obj->add(key, i);

	  env->ReleaseStringUTFChars(jkey, key);
}

/*
 * Class:     BSONObjWrapper
 * Method:    add
 * Signature: (JLjava/lang/String;D)V
 */
JNIEXPORT void JNICALL Java_BSONObjWrapper_add__JLjava_lang_String_2D
  (JNIEnv *env, jobject jobj, jlong jinstance,jstring jkey, jdouble jd){
	  BSONObj* obj = (BSONObj*)jinstance;
	  jboolean iscopy;
	  const char* key = env->GetStringUTFChars(jkey, &iscopy);
	  double d = (double)jd;
	  obj->add(key, d);

	  env->ReleaseStringUTFChars(jkey, key);
}

/*
 * Class:     BSONObjWrapper
 * Method:    add
 * Signature: (JLjava/lang/String;J)V
 */
JNIEXPORT void JNICALL Java_BSONObjWrapper_add__JLjava_lang_String_2J
  (JNIEnv *env, jobject jobj, jlong jinstance,jstring jkey, jlong jl){
	  BSONObj* obj = (BSONObj*)jinstance;
	  jboolean iscopy;
	  const char* key = env->GetStringUTFChars(jkey, &iscopy);
	  long l = (long)l;
	  obj->add(key, l);

	  env->ReleaseStringUTFChars(jkey, key);
}

/*
 * Class:     BSONObjWrapper
 * Method:    add
 * Signature: (JLjava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_BSONObjWrapper_add__JLjava_lang_String_2Ljava_lang_String_2
  (JNIEnv *env, jobject jobj, jlong jinstance,jstring jkey, jstring jstr){
	  BSONObj* obj = (BSONObj*)jinstance;
	  jboolean iscopy;
	  const char* key = env->GetStringUTFChars(jkey, &iscopy);
	  const char* str = env->GetStringUTFChars(jstr, &iscopy);
	  obj->add(key, str);

	  env->ReleaseStringUTFChars(jkey, key);
	  env->ReleaseStringUTFChars(jstr, str);
}

/*
 * Class:     BSONObjWrapper
 * Method:    add
 * Signature: (JLjava/lang/String;LBSONObjWrapper;)V
 */
JNIEXPORT void JNICALL Java_BSONObjWrapper_add__JLjava_lang_String_2LBSONObjWrapper_2
  (JNIEnv *env, jobject jobj, jlong jinstance,jstring jkey, jobject jbson){
	  BSONObj* obj = (BSONObj*)jinstance;
	  jboolean iscopy;
	  const char* key = env->GetStringUTFChars(jkey, &iscopy);

	  jclass clazzBSONObjWrapper = env->FindClass("BSONObjWrapper");
	  jmethodID id = env->GetMethodID(clazzBSONObjWrapper, "instance", "()J");
	  BSONObj* ref = (BSONObj*) env->CallLongMethod(jbson, id);

	  obj->add(key, *ref);

	  env->ReleaseStringUTFChars(jkey, key);
}

/*
 * Class:     BSONObjWrapper
 * Method:    has
 * Signature: (JLjava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_BSONObjWrapper_has
  (JNIEnv *env, jobject jobj, jlong jinstance,jstring jkey){
	  BSONObj* obj = (BSONObj*)jinstance;

	  jboolean iscopy;
	  const char* key = env->GetStringUTFChars(jkey, &iscopy);

	  jboolean res = (jboolean)obj->has(key);

	  env->ReleaseStringUTFChars(jkey, key);
	  return res;
}

/*
 * Class:     BSONObjWrapper
 * Method:    getInt
 * Signature: (JLjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_BSONObjWrapper_getInt
  (JNIEnv *env, jobject jobj, jlong jinstance,jstring jkey){
	  BSONObj* obj = (BSONObj*)jinstance;
	  jboolean iscopy;
	  const char* key = env->GetStringUTFChars(jkey, &iscopy);

	  int i = (int)obj->getInt(key);

	  env->ReleaseStringUTFChars(jkey, key);

	  return i;
}

/*
 * Class:     BSONObjWrapper
 * Method:    getDouble
 * Signature: (JLjava/lang/String;)D
 */
JNIEXPORT jdouble JNICALL Java_BSONObjWrapper_getDouble
  (JNIEnv *env, jobject jobj, jlong jinstance,jstring jkey){
	  BSONObj* obj = (BSONObj*)jinstance;
	  jboolean iscopy;
	  const char* key = env->GetStringUTFChars(jkey, &iscopy);

	  double* d = (double*)obj->getDouble(key);

	  env->ReleaseStringUTFChars(jkey, key);

	  return *d;
}

/*
 * Class:     BSONObjWrapper
 * Method:    getLong
 * Signature: (JLjava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_BSONObjWrapper_getLong
  (JNIEnv *env, jobject jobj, jlong jinstance,jstring jkey){
	  BSONObj* obj = (BSONObj*)jinstance;
	  jboolean iscopy;
	  const char* key = env->GetStringUTFChars(jkey, &iscopy);

	  long l = (long)obj->getLong(key);

	  env->ReleaseStringUTFChars(jkey, key);

	  return l;
}

/*
 * Class:     BSONObjWrapper
 * Method:    getString
 * Signature: (JLjava/lang/String;)Ljava/lang/String{
}
 */
JNIEXPORT jstring JNICALL Java_BSONObjWrapper_getString
(JNIEnv *env, jobject jobj, jlong jinstance,jstring jkey) {
	BSONObj* obj = (BSONObj*)jinstance;
	jboolean iscopy;
	const char* key = env->GetStringUTFChars(jkey, &iscopy);

	char* val = obj->getChars(key);
	jstring res = env->NewStringUTF(val);

	env->ReleaseStringUTFChars(jkey, key);

	return res;
}

/*
 * Class:     BSONObjWrapper
 * Method:    get
 * Signature: (JLjava/lang/String;)Ljava/lang/Object{
 }
 */
JNIEXPORT jobject JNICALL Java_BSONObjWrapper_get
(JNIEnv *env, jobject jobj, jlong jinstance,jstring jkey){
	BSONObj* obj = (BSONObj*)jinstance;
	jboolean iscopy;
	const char* key = env->GetStringUTFChars(jkey, &iscopy);

	env->ReleaseStringUTFChars(jkey, key);
}

/*
 * Class:     BSONObjWrapper
 * Method:    getBSON
 * Signature: (JLjava/lang/String;)LBSONObjWrapper{
 }
 */
JNIEXPORT jobject JNICALL Java_BSONObjWrapper_getBSON
(JNIEnv *env, jobject jobj, jlong jinstance,jstring jkey){
	BSONObj* obj = (BSONObj*)jinstance;
	jboolean iscopy;
	const char* key = env->GetStringUTFChars(jkey, &iscopy);

	BSONObj* bson = obj->getBSON(key);

	jclass clazz = env->FindClass("BSONObjWrapper");
	jmethodID jid = env->GetMethodID(clazz, "<init>", "(J)V");
	jobject jbson = env->NewObject(clazz, jid, (long)bson);

	env->ReleaseStringUTFChars(jkey, key);

	return jbson;
}

/*
 * Class:     BSONObjWrapper
 * Method:    getXpath
 * Signature: (JLjava/lang/String;)Ljava/lang/Object{
 }
 */
JNIEXPORT jobject JNICALL Java_BSONObjWrapper_getXpath
(JNIEnv *env, jobject jobj, jlong jinstance,jstring jxpath){
	BSONObj* obj = (BSONObj*)jinstance;
	jboolean iscopy;
	const char* xpath = env->GetStringUTFChars(jxpath, &iscopy);

	env->ReleaseStringUTFChars(jxpath, xpath);
}

/*
 * Class:     BSONObjWrapper
 * Method:    toString
 * Signature: (J)Ljava/lang/String{
 }
 */
JNIEXPORT jstring JNICALL Java_BSONObjWrapper_toString
(JNIEnv *env, jobject jobj, jlong jinstance){
	BSONObj* obj = (BSONObj*)jinstance;

	char* str = obj->toChar();

	jstring res = env->NewStringUTF(str);

	return res;

}

/*
 * Class:     BSONObjWrapper
 * Method:    iterator
 * Signature: (J)Ljava/util/Iterator{
 }
 */
JNIEXPORT jobject JNICALL Java_BSONObjWrapper_iterator
(JNIEnv *env, jobject jobj, jlong jinstance){
	BSONObj* obj = (BSONObj*)jinstance;

}

/*
 * Class:     BSONObjWrapper
 * Method:    length
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_BSONObjWrapper_length
(JNIEnv *env, jobject jobj, jlong jinstance){
	BSONObj* obj = (BSONObj*)jinstance;

	jint res = (jint)obj->length();

	return res;
}

