import java.util.ArrayList;

class ConnectionWrapper {
	private native boolean open(long connection);
	private native void close(long connection);
	private native void internalClose(long connection);
	private native boolean isOpen(long connection) ;

	private native boolean insert(long connection, String db, String ns, String json);
	private native boolean insert(long connection, String db, String ns, BSONObjWrapper obj);
	private native BSONObjWrapper findByKey(long connection, String db, String ns, String id);
	private native ArrayList<BSONObjWrapper> find(long connection, String db, String ns, String filter);
	private native boolean update(long connection, String db, String ns, String json);
	private native boolean update(long connection, String db, String ns, BSONObjWrapper bson);

	private native boolean dropNamespace(long connection, String db, String ns);

	private native String host(long connection) ;

	private long _connection;

	public ConnectionWrapper(long connection) {
		_connection = connection;
	}

	public long connection() {
		return _connection;
	}

	public boolean open() {
		return open(_connection);
	}

	public void close() {
		close(_connection);
	}

	public void internalClose() {
		internalClose(_connection);
	}

	public boolean isOpen() {
		return isOpen(_connection);
	}

	public boolean insert(String db, String ns, String json) {
		return insert(_connection, db, ns, json);
	}

	public boolean insert(String db, String ns, BSONObjWrapper obj) {
		return insert(_connection, db, ns, obj);
	}

	public BSONObjWrapper findByKey(String db, String ns, String id) {
		return findByKey(_connection, db, ns, id);
	}

	public ArrayList<BSONObjWrapper> find(String db, String ns, String filter) {
		return find(_connection, db, ns, filter);
	}

	public boolean update(String db, String ns, String json) {
		return update(_connection, db, ns, json);
	}

	public boolean update(String db, String ns, BSONObjWrapper bson) {
		return update(_connection, db, ns, bson);
	}

	public boolean dropNamespace(String db, String ns) {
		return dropNamespace(_connection, db, ns);
	}

	public String host() {
		return host(_connection);
	}

}
