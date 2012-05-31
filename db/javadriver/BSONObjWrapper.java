import java.util.Iterator;

public class BSONObjWrapper {
	public native void add(long instance,String key, int i);
	public native void add(long instance,String key, double d);
	public native void add(long instance,String key, long l);
	public native void add(long instance,String key, String val);
	public native void add(long instance,String key, BSONObjWrapper bson);
	//public native void add(long instance,String key, BSONArrayObj);

	public native boolean has(long instance,String key) ;

	public native int getInt(long instance,String key) ;
	public native double getDouble(long instance,String key) ;
	public native long getLong(long instance,String key) ;
	public native String getStrings(long instance,String key) ;
	public native String getString(long instance,String key) ;
	public native Object get(long instance,String key) ;
	public native BSONObjWrapper getBSON(long instance,String key) ;
	//public native BSONArrayObj* getBSONArray(long instance,String key) ;

	public native Object getXpath(long instance,String xpath) ;

	//public native BSONTYPE type(long instance,String key) ;

	public native String toString(long instance) ;

	public native Iterator iterator(long instance);
	public native int length(long instance) ;

	private long _instance;

	public BSONObjWrapper(long instance) {
		_instance = instance;
	}

	public long instance() {
		return _instance;
	}

	public void add(String key, int i) {
		add(_instance, key, i);
	}

	public void add(String key, double d) {
		add(_instance, key, d);
	}

	public void add(String key, long l) {
		add(_instance, key, l);
	}

	public void add(String key, String str) {
		add(_instance, key, str);
	}

	public void add(String key, BSONObjWrapper bson) {
		add(_instance, key, bson);
	}

//	public void add(String key, BSONArrayObj);

	public boolean has(String key) {
		return has(_instance, key);
	}	

	public int getInt(String key)  {
		return getInt(_instance, key);
	}

	public double getDouble(String key) {
		return getDouble(_instance, key);
	}

	public long getLong(String key) {
		return getLong(_instance, key);
	}

	public String getString(String key) {
		return getString(_instance, key);
	}

	public BSONObjWrapper getBSON(String key) {
		return getBSON(_instance, key);
	}

//	public BSONArrayObj* getBSONArray(String key) ;
//
	public Object get(String key) {
		return get(_instance, key);
	}

	public Object getXpath(String xpath) {
		return getXpath(_instance, xpath);
	}

	public String toString() {
		return toString(_instance);
	}

	public Iterator iterator() {
		return iterator(_instance);
	}
	
	public int length() {
		return length(_instance);
	}

}
