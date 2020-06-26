public class ListTest{
	public static void main(String args[]){
		List A = new List();
		List B = new List();
		for(int i=1; i<=20; i++){
			A.append(i);
			B.append(i);
		}
		boolean eq = false;
		eq = A.equals(B);
		System.out.println(eq);
		
		List C = new List();
		List D = new List();
		
		C.append(A);
		C.append(B);
		C.append(A);
		C.append(B);

		D.append(A);
		D.append(B);
		D.append(A);
		D.append(B);
		
		eq = C.equals(D);
		System.out.println(eq);
		
		C.append(A);
		C.append(B);

		D.append(B);
		D.append(A);
		
		eq = C.equals(D);
		System.out.println(eq);
	}
}