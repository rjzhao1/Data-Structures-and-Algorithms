//Ricky Zhao
//Rjzhao
//pa1

public class List{
	private class Node{
		int num;
		Node prev;
		Node next;
	   
		Node(int x){
		   num = x;
		   next = null;
		   prev = null;
		}
	   
	   
	}
	
	private Node head;
	private Node tail;
	private Node cursor;
	private int size;
	private int ind;
	
	// Constructor
	List(){
		head = null;
		tail = null;
		cursor = null;
		size = 0;
		ind = -1;
	}
	// Creates a new empty list.

	// Access functions
	int length(){
		return size;
	}
	// Returns the number of elements in this List.
	
	int index(){
		return ind;
	}
	// If cursor is defined, returns the index of the cursor element,
	// otherwise returns -1.

	int front(){
		if(length()<=0){
			throw new RuntimeException(
				"List Error: front() called on empty list()");
		}
		return head.num;
	}
	// Returns front element. Pre: length()>0

	int back(){
		if(size==0){
			throw new RuntimeException(
				"List Error: front() called on empty list()");
		}
		return tail.num;
	}
	// Returns back element. Pre: length()>0
	
	int get(){
		if(index() == -1){
			throw new RuntimeException(
				"List Error: get() called on undefined cursor");
		}
		if(length()<=0){
			throw new RuntimeException(
				"List Error: get() called on empty list()");
		}
		return cursor.num;
	}		
	// Returns cursor element. Pre: length()>0, index()>=0
	
	boolean equals(List L){
		if(L.length() == length()){
			Node N = head;
			Node M = L.head;
			
			while(N!=null){
				if(N.num!=M.num){
					return false;
				}
				N=N.next;
				M=M.next;
			}
			return true;
		}
		return false;
	}
	// Returns true if and only if this List and L are the same
	// integer sequence. The states of the cursors in the two Lists
	// are not used in determining equality.
	
	// Manipulation procedures
	void clear(){
		head = null;
		tail = null;
		cursor = null;
		size = 0;
		ind=-1;
	}
	// Resets this List to its original empty state.
	
	void moveFront(){
		if(length()!=0){
			cursor=head;
			ind = 0;
		}
	}
	// If List is non-empty, places the cursor under the front element,
	// otherwise does nothing.
	
	void moveBack(){
		if(size!=0){
			cursor = tail;
			ind = length()-1;
		}
	}		
	// If List is non-empty, places the cursor under the back element,
	// otherwise does nothing.
	
	void movePrev(){
		if(cursor!=null){
			if(index()!=0){
				cursor = cursor.prev;
				ind--;
			}else{
				cursor = null;
				ind = -1;
			}
		}
	}
	// If cursor is defined and not at front, moves cursor one step toward
	// front of this List, if cursor is defined and at front, cursor becomes
	// undefined, if cursor is undefined does nothing.
	
	void moveNext(){
		if(cursor!=null){
			if(index()!=length()-1){
				cursor = cursor.next;
				ind++;
			}else{
				cursor=null;
				ind=-1;
			}	
		}
	}
	// If cursor is defined and not at back, moves cursor one step toward
	// back of this List, if cursor is defined and at back, cursor becomes
	// undefined, if cursor is undefined does nothing.
	
	void prepend(int data){
		if(size==0){
			head = new Node(data);
			tail = head;
		}else{
			Node N = new Node(data);
			N.next= head;
			head.prev = N;
			head = N;
			if(cursor!=null){
				ind++;
			}
		}
		size++;
	}
	// Insert new element into this List. If List is non-empty,
	// insertion takes place before front element.
	void append(int data){
		if(size==0){
			tail = new Node(data);
			head = tail;
		}else{
			Node N = new Node(data);
			N.prev=tail;
			tail.next=N;
			tail = N;
		}
		size++;
	}		
	// Insert new element into this List. If List is non-empty,
	// insertion takes place after back element.
	
	void insertBefore(int data){
		if(index()<0){
			throw new RuntimeException(
				"List Error: insertBefore() called on undefined cursor");
		}
		if(length()<=0){
			throw new RuntimeException(
				"List Error: insertBefore() called on an empty list");
		}
		Node N = new Node(data);
		if(index()==0){
			cursor.prev=N;
			N.next=cursor;
			head = N;
		}else{
			N.next=cursor;
			N.prev=cursor.prev;
			cursor.prev.next=N;
			cursor.prev = N;
		}
		ind++;
		size++;
		
	}
	// Insert new element before cursor.
	// Pre: length()>0, index()>=0
	
	void insertAfter(int data){
		if(index()<0){
			throw new RuntimeException(
				"List Error: insertAfter() called on undefined cursor");
		}
		if(length()<=0){
			throw new RuntimeException(
				"List Error: insertAfter() called on an empty list");
		}
		Node N = new Node(data);
		if(index()==length()-1){
			cursor.next=N;
			N.prev=cursor;
			tail =N;
		}else{
			N.prev=cursor;
			N.next=cursor.next;
			cursor.next.prev=N;
			cursor.next=N;
		}
		size++;
	}
	// Inserts new element after cursor.
	// Pre: length()>0, index()>=0
	
	void deleteFront(){
		if(length()<=0){
			throw new RuntimeException(
				"List Error: deleteFront() called on an empty list");
		}
		if(length()==1){
			head=null;
			tail=null;
			cursor=null;
			ind=-1;
		}else{
			if(index()==0){
				cursor=cursor.next;
			}
			head.next.prev=null;
			head=head.next;
			ind--;
		}
		size--;
	}		
	// Deletes the front element. Pre: length()>0
	
	void deleteBack(){
		if(length()<=0){
			throw new RuntimeException(
				"List Error: deleteBack() called on an empty list");
		}
		if(length()==1){
			head=null;
			tail=null;
			cursor=null;
			ind=-1;
		}else{
			if(index()==length()-1){
				cursor=null;
				ind=-1;
			}
			tail.prev.next=null;
			tail=tail.prev;
		}
		size--;
	}
	// Deletes the back element. Pre: length()>0

	void delete(){
		if(index()<0){
			throw new RuntimeException(
				"List Error: delete() called on undefined cursor");
		}
		if(length()<=0){
			throw new RuntimeException(
				"List Error: delete() called on an empty list");
		}
		if(index()==0){
			head=head.next;
			head.prev=null;
			cursor=null;
		}else if(index()==length()-1){
			tail=tail.prev;
			tail.next=null;
			cursor=null;
		}else{
			cursor.prev.next=cursor.next;
			cursor.next.prev=cursor.prev;
			cursor=null;
		}
		ind=-1;
		size--;
		
	}
	// Deletes cursor element, making cursor undefined.
	// Pre: length()>0, index()>=0
	// Other methods
	
	public String toString(){
		StringBuffer sb = new StringBuffer();
		Node N = head;
		for( ;N!=null; N=N.next){
			sb.append(N.num).append(" ");
		}
		return new String(sb);
	}
	// Overrides Object's toString method. Returns a String
	// representation of this List consisting of a space
	// separated sequence of integers, with front on left.
	
	List copy(){
		List L = new List();
		Node N=head;
		while(N!=null){
			L.append(N.num);
			N=N.next;
		}
		return L;
	}
	// Returns a new List representing the same integer sequence as this
	// List. The cursor in the new list is undefined, regardless of the
	// state of the cursor in this List. This List is unchanged.
}
