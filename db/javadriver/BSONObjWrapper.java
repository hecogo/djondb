class BSONObjWrapper {
	public native void add(long bson,String key, int i);
	public native void add(long bson,String key, double d);
	public native void add(long bson,String key, long l);
	public native void add(long bson,String key, String val);
	public native void add(long bson,String key, BSONObjWrapper bson);
	//public native void add(long bson,String key, BSONArrayObj);

	public native bool has(long bson,String key) ;

	public native int* getInt(long bson,String key) ;
	public native double* getDouble(long bson,String key) ;
	public native long* getLong(long bson,String key) ;
	public native String* getStrings(long bson,String key) ;
	public native String getString(long bson,String key) ;
	public native BSONObj* getBSON(long bson,String key) ;
	//public native BSONArrayObj* getBSONArray(long bson,String key) ;

	public native Object getXpath(long bson,String xpath) ;

	//public native BSONTYPE type(long bson,String key) ;

	public native String* toString(long bson,) ;

	public native std::map<String key, BSONContent* >::_iterator begin(long bson,) ;
	public native std::map<String key, BSONContent* >::_iterator end(long bson,) ;
	public native int length(long bson,) ;

	public void add(String key, int);
	public void add(String key, double);
	public void add(String key, long);
	public void add(String key, String*);
	public void add(String key, String);
	public void add(String key, BSONObj);
	public void add(String key, BSONArrayObj);

	public bool has(String key) ;

	public int* getInt(String key) ;
	public double* getDouble(String key) ;
	public long* getLong(String key) ;
	public String* getStrings(String key) ;
	public String getString(String key) ;
	public BSONObj* getBSON(String key) ;
	public BSONArrayObj* getBSONArray(String key) ;
	public void* get(String key) ;
	public BSONContent* getContent(String key) ;
	public BSONContent* getContent(String key, BSONTYPE) ;

	public BSONContent getXpath(String xpath) ;

	public BSONTYPE type(String key) ;

	public String* toString() ;

	public std::map<String key, BSONContent* >::_iterator begin() ;
	public std::map<String key, BSONContent* >::_iterator end() ;
	public int length() ;

}
