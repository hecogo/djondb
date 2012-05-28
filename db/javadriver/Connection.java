public class Connection {
	static {
		System.loadLibrary("djon-client");
	}

	private native boolean open_jni(String host){}
	private native boolean close_jni(){}

   public boolean open() {}

   public void close() {}

   public void internalClose() {}

   public boolean isOpen() {}

	boolean insert(String db,  String ns,  String json){}

	boolean insert( String db,  String ns,  BSONObj obj){}

	BSONObj* findByKey( String db,  String ns,  String id){}

	std::vector<BSONObj*> find( String db,  String ns,  String filter){}

	boolean update( String db,  String ns,  String json){}

	boolean update( String db,  String ns,  BSONObj bson){}

	boolean dropNamespace( String db,  String ns){}

	String host() {}

}
