//Ricky Zhao
//Rjzhao
//pa3
public class ListTest{
	public static void main(String[] args){
		List A = new List();
		List B = new List();
		  
		for(int i=1; i<=15; i++){
			A.append(i);
			B.prepend(i);
		}
		System.out.println(A);
		System.out.println(B);
		  
		A.moveFront();
		while(A.index()>=0){
			System.out.print(A.get()+" ");
			A.moveNext();
		}
		System.out.println();
		B.moveBack();
		while(B.index()>=0){
			System.out.print(B.get()+" ");
			B.movePrev();
		}
		System.out.println();
	  
		System.out.println(A.equals(B));
		System.out.println(B.equals(C));
		System.out.println(C.equals(A));
		  
		A.moveFront();
		for(int i=0; i<5; i++) A.moveNext(); // at index 5
		A.insertBefore(-1);                  // at index 6
		for(int i=0; i<9; i++) A.moveNext(); // at index 15
		A.insertAfter(-2);
		for(int i=0; i<5; i++) A.movePrev(); // at index 10
		A.delete();
		System.out.println(A);
		System.out.println(A.length());
		A.clear();
		System.out.println(A.length());
	}
}