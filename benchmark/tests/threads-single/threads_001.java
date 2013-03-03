public class threads_001 {
	public static void main(String[] args) {
		//double  t0 = System.currentTimeMillis();
		long acc = 0;
		int L = 10000000;
		int n = 2 * L;

		for (int i = 0; i <= n; ++i) acc += i;

		//double  t1 = System.currentTimeMillis();
		//System.out.println("Time elapsed single-thread version Java: " + (t1 - t0) / 1000);
		System.out.println("Java");
		System.out.println(acc);
	}
}
