class Main {
	static {
		try {
		System.loadLibrary("djon-client");
		System.loadLibrary("djon-javadriver");
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	public static void main(String[] args) {
		try {
			ConnectionWrapper con = ConnectionManagerWrapper.getConnection("localhost");

			if (!con.open()) {
				System.out.println("Not connected");
			}

			con.insert("dbjava", "nsjava", "{ 'name': 'Juan' }");

			ConnectionManagerWrapper.releaseConnection(con);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}
