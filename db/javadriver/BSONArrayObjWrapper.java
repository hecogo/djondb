// =====================================================================================
//  Filename:  BSONArrayObj.java
//
//  Description:  This file contains the definition of the class BSONArrayObj which is an array of BSONObj
//
//  Version:  1.0
//  Created:  02/15/2012 09:07:11 AM
//  Revision:  none
//  Compiler:  gcc
//
//  Author:  Juan Pablo Crossley (crossleyjuan@gmail.com),
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

class BSONArrayObjWrapper {
	private long _instance;

	public BSONArrayObjWrapper() {
		_instance = create();
		System.out.println("BSONArrayObj: " + _instance);
	}

	public BSONArrayObjWrapper(long instance) {
		_instance = instance;
	}

	private native long create();
	private native int length(long instance);
	private native void add(long instance, BSONObjWrapper obj);
	private native BSONObjWrapper get(long instance, int index);
   private native String toChar(long instance);

	public long instance() {
		return _instance;
	}

	public int length() {
		return length(_instance);
	}

	public void add(BSONObjWrapper obj) {
		add(_instance, obj);
	}

	public BSONObjWrapper get(int index) {
		return get(_instance, index);
	}

   public String toChar() {
		return toChar(_instance);
	}

};
