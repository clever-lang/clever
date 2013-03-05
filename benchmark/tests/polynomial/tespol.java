public class tespol {

    static float dopoly(float x) {
		float pol[] = new float[100];
		int j;
		float mu = (float)10.0;
		float s;

		for (j=0; j<100; j++) {
		    mu =  (mu + (float)2.0) / (float)2.0;
		    pol[j] = mu;
		}
		s = (float)0.0;
		for (j=0; j<100; j++) {
		    s = x*s + pol[j];
		}
		return s;
    }

    static public void main(String argv[]) {
		float x;
		float pu = (float)0.0;
		int i, n;

		n = 100000;
		x = (float)0.2;
		for(i=0; i<n; i++) {
			pu += dopoly(x);
		}
		System.out.println(pu);
  }
}