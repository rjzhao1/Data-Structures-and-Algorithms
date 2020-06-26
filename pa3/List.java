//Ricky Zhao
//Rjzhao
//pa3

public class List{
	private class Node{
		Object item;
		Node prev;
		Node next;
	   
		Node(Object x){
		   item = x;
		   next = null;
		   prev = null;
		}
		
		public boolean equals(Object x){
			if(!(x instanceof Node)){
				return false;
			} 
			Node N = (Node)x;
			if(item.equals(N.item)){
				return true;
			}else{
				return false;
			}
		}
		
		public String toString(){
			StringBuffer sb = new StringBuffer();
			sb.append(item.toString());
			return new String(sb);
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

	Object front(){
		if(length()<=0){
			throw new RuntimeException(
				"List Error: front() called on empty list()");
		}
		return head.item;
	}
	// Returns front element. Pre: length()>0

	Object back(){
		if(size==0){
			throw new RuntimeException(
				"List Error: front() called on empty list()");
		}
		return tail.item;
	}
	// Returns back element. Pre: length()>0
	
	Object get(){
		if(index() == -1){
			throw new RuntimeException(
				"List Error: get() called on undefined cursor");
		}
		if(length()<=0){
			throw new RuntimeException(
				"List Error: get() called on empty list()");
		}
		return cursor.item;
	}		
	// Returns cursor element. Pre: length()>0, index()>=0
	
	public boolean equals(Object x){
		if(!(x instanceof List)){
			return false;
		}
		
		List L = (List)x;
		if(L.length() == length()){
			Node N = head;
			Node M = L.head;
			
			while(N!=null){
				if(N.item!=M.item){
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
			if(cursor!=head){
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
			if(cursor!=tail){
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
	
	void prepend(Object data){
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
	void append(Object data){
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
	
	void insertBefore(Object data){
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
	
	void insertAfter(Object data){
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
			if(cursor==head){
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
			if(cursor==tail){
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
		if(cursor==head){
			if(length()==1){
				head=null;
				tail=null;
				cursor=null;
				ind=-1;
			}else{
				head=head.next;
				head.prev=null;
				cursor=null;
			}
		}else if(cursor==tail){
			
			if(length()==1){
				head=null;
				tail=null;
				cursor=null;
				ind=-1;
			}else{
				tail=tail.prev;
				tail.next=null;
				cursor=null;
			}
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
			sb.append(N.item).append(" ");
		}
		return new String(sb);
	}
	// Overrides Object's toString method. Returns a String
	// representation of this List consisting of a space
	// separated sequence of integers, with front on left.
	
}