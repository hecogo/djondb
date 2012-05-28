class ConnectionManagerWrapper {
	public native static ConnectionWrapper getConnection(String host);
	public native static void releaseConnection(ConnectionWrapper conn);

}	
