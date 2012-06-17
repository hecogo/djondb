import java.util.*;

class Main {
	static {
		try {
			System.loadLibrary("djon-javadriver");
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public static void testBSON() {
		System.out.println("testing testBSON");
		BSONObjWrapper wrapper = new BSONObjWrapper();
		wrapper.add("i", 1);
		wrapper.add("d", 100120d);
		wrapper.add("l", 12l);
		wrapper.add("s", "Test");
		BSONObjWrapper inner = new BSONObjWrapper();
		inner.add("s", "s");
		wrapper.add("inner", inner);
		assert(5 == wrapper.length());
		assert(wrapper.has("i"));
		assert(wrapper.has("d"));
		assert(wrapper.has("l"));
		assert(wrapper.has("s"));
		assert(1 == wrapper.getInt("i"));
		assert(100120d == wrapper.getDouble("d"));
		assert(12l == wrapper.getLong("l"));
		assert("Test".equals(wrapper.getString("s")));
		BSONObjWrapper innerres = wrapper.getBSON("inner");
		assert(innerres != null);
		assert("Test".equals(innerres.getString("s")));

		// test arrays
		BSONArrayObjWrapper array = new BSONArrayObjWrapper();
		System.out.println("Array");
		BSONObjWrapper obj = new BSONObjWrapper();
		obj.add("i", 1);
		System.out.println("adding to Array");
		array.add(obj);
		wrapper.add("array", array);
		assert(wrapper.getBSONArray("array") != null);
		assert(wrapper.getBSONArray("array").length() == 1);
		//	public BSONArrayObj* getBSONArray(String key) ;
		//
		assert(wrapper.get("s") != null);
		//wrapper.getXpath(String xpath);
		//wrapper.toString();
		//wrapper.iterator();
	}

	public void testConnection() {
		try {
			ConnectionWrapper con = ConnectionManagerWrapper.getConnection("localhost");

			if (!con.open()) {
				System.out.println("Not connected");
			}

			con.insert("dbjava", "nsjava", "{ 'name': 'Juan' }");
			ArrayList<BSONObjWrapper> wrapper = con.find("dbjava", "nsjava", "$'name' == 'Juan'");

			System.out.println("Size: " + wrapper.size());

			for (int x = 0; x < wrapper.size(); x++) {
				BSONObjWrapper bson = wrapper.get(x);
				System.out.println(bson.toString());
			}

			ConnectionManagerWrapper.releaseConnection(con);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public static void main(String[] args) {
		Main m = new Main();
		m.testBSON();
		m.testConnection();
	}
}
