
class Test {
	native void test1();
	native void test2(String name);

	static {
		System.loadLibrary("testjni");
	}

	public static void main(String arg[]) {
		Test t = new Test();
		t.test1();
		t.test2("John");
	}
}
