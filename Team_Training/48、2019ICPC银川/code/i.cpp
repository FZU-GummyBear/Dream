import java.math.BigInteger;
import java.util.Scanner;

public class Main {

	static BigInteger [] arr = new BigInteger[1010];

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner cin = new Scanner(System.in); 
		int x = cin.nextInt();
		BigInteger y = cin.nextBigInteger();
		String str = cin.nextLine();
		BigInteger a = BigInteger.ZERO;
		int n = str.length();
		BigInteger _x = BigInteger.valueOf(x);
		//System.out.println("x = " + _x);
		for(int i = 1; i < n; ++i) {
			a = a.multiply(_x);
			BigInteger c = BigInteger.ZERO;
			if('0' <= str.charAt(i) && str.charAt(i) <= '9') {
				c = BigInteger.valueOf(str.charAt(i) - '0');
			} else if('A' <= str.charAt(i) && str.charAt(i) <= 'Z') {
				c = BigInteger.valueOf(10 + str.charAt(i) - 'A');
				//System.out.println("s[i] = " + str.charAt(i));
			} else {
				c = BigInteger.valueOf(36 + str.charAt(i) - 'a');
			}
			//	System.out.println("c = " + c);
			a = a.add(c);
		}
		//	System.out.println(a);
		for(int i = 0; i < 1010; ++i) arr[i] = BigInteger.ZERO;
		int cnt = 0;
		while(!a.equals(BigInteger.ZERO)) {
			arr[cnt++] = a.mod(y);
			a = a.divide(y);
		}
		for(int i = cnt - 1; i >= 0; --i) {
			int c = arr[i].intValue();
			if(c < 10) {
				System.out.print(c);
			} else if(c < 36) {
				System.out.print((char)(c - 10 + 'A'));
			} else {
				System.out.print((char)(c - 36 + 'a'));
			}
		}
	}

}

