// =====================================================================================
//  Filename:  Test.cpp
// 
//  Description: 
// 
//  Version:  1.0
//  Created:  05/28/2012 08:17:35 AM
//  Revision:  none
//  Compiler:  gcc
// 
//  Author:  YOUR NAME (), 
// 
// License:
// 
// This file is part of the djondb project, for license information please refer to the LICENSE file,
// the application and libraries are provided as-is and free of use under the terms explained in the file LICENSE
// Its authors create this application in order to make the world a better place to live, but you should use it on
// your own risks.
// 
// Also, be adviced that, the GPL license force the committers to ensure this application will be free of use, thus
// if you do any modification you will be required to provide it for free unless you use it for personal use (you may 
// charge yourself if you want), bare in mind that you will be required to provide a copy of the license terms that ensures
// this program will be open sourced and all its derivated work will be too.
// =====================================================================================

#include "Test.h"
#include "test.h"

JNIEXPORT void JNICALL Java_Test_test1
  (JNIEnv *, jobject) {
	  test1();
  }

JNIEXPORT void JNICALL Java_Test_test2
  (JNIEnv *env, jobject jo, jstring strname) {
	  jboolean iscopy = false;
	  const char* name = env->GetStringUTFChars(strname, &iscopy);

	  test2(name);

	  env->ReleaseStringUTFChars(strname, name);
  }

