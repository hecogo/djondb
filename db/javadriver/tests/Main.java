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
		ConnectionManagerWrapper.getConnection("localhost");
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}
