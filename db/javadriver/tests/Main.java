class Main {
	static {
		try {
			System.loadLibrary("djon-javadriver");
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public static void testBSON() {
		BSONObjWrapper wrapper = new BSONObjWrapper(1);
		wrapper.add("test", 1);
	}

	public static void main(String[] args) {
		try {
			ConnectionWrapper con = ConnectionManagerWrapper.getConnection("localhost");

			if (!con.open()) {
				System.out.println("Not connected");
			}

			con.insert("dbjava", "nsjava", "{ 'name': 'Juan' }");
			BSONObjWrapper wrapper = con.findByKey("dbjava", "nsjava", "56681d39-e6ae-46cf-8c5e-85e517f7a969");

			System.out.println("has: " + wrapper.has("name"));
			System.out.println("name: " + wrapper.getString("name"));

			ConnectionManagerWrapper.releaseConnection(con);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}
