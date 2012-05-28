import java.util.ArrayList;

class ConnectionWrapper {
	public native boolean open(long connection);
	public native void close(long connection);
	public native void internalClose(long connection);
	public native boolean isOpen(long connection) ;

	public native boolean insert(long connection, String db, String ns, String json);
	public native boolean insert(long connection, String db, String ns, BSONObjWrapper obj);
	public native BSONObjWrapper findByKey(long connection, String db, String ns, String id);
	public native ArrayList<BSONObjWrapper> find(long connection, String db, String ns, String filter);
	public native boolean update(long connection, String db, String ns, String json);
	public native boolean update(long connection, String db, String ns, BSONObjWrapper bson);

	public native boolean dropNamespace(long connection, String db, String ns);

	public native String host(long connection) ;

	private long _connection;

	public ConnectionWrapper(long connection) {
		_connection = connection;
	}
}
