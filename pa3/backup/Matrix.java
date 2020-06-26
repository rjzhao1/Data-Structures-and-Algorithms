public class Matrix{
	//Private inner class
	private class Entry{
		int col;
		double value;
		
		Entry(int x, double y){
			col = x;
			value = y;
		}
		
		public boolean equals(Object x){
			if(!(x instanceof Entry)){
				return false;
			}
			Entry E = (Entry)x;
			if(col==E.col && value == E.value){
				return true;
			}else{
				return false;
			}
		}
		
		public String toString(){
			StringBuffer sb = new StringBuffer();
			sb.append("(");
			sb.append(col).append(", ");
			sb.append(value).append(")");
			return new String(sb);
		}
	}
	//Constructor
	private List[] row;
	private int size;
	private int NNZ;
	Matrix(int n){
		if(n<1){
			throw new RuntimeException("Matrix Error: Matrix() called on an invalid Matrix");
		}
		row = new List[n+1];
		size = n;
		NNZ = 0;
		for(int i=1; i<=n;i++){
			row[i]= new List();
		}
	}
	// Makes a new n x n zero Matrix. pre: n>=1
	// Access functions
	
	int getSize(){
		return size;
	}
	// Returns n, the number of rows and columns of this Matrix

	int getNNZ(){
		return NNZ;
	}		// Returns the number of non-zero entries in this Matrix

	public boolean equals(Object x){
		if(!(x instanceof Matrix)){
			return false;
		}
		if(x==this){
			return true;
		}else{
			Matrix M = (Matrix)x;
			if(size!=M.size||NNZ!=M.NNZ){
				return false;
			}else{
				for(int i = 1;i<=size;i++){
					row[i].moveFront();
					M.row[i].moveFront();
					while(row[i].index()>=0 && M.row[i].index()>=0){
						Entry a = (Entry)row[i].get();
						Entry b = (Entry)M.row[i].get();
						if(a.col!=b.col||a.value!=b.value){
							return false;
						}
						row[i].moveNext();
						M.row[i].moveNext();
					}
		
				}
				return true;
			}
		}
	}  
	// overrides Object's equals() method
	// Manipulation procedures
	
	void makeZero(){
		for(int i=1;i<=size;i++){
			row[i].clear();
		}
		NNZ = 0;
	}
	// sets this Matrix to the zero state

	Matrix copy(){
		Matrix M = new Matrix(size);
		List L;
		Entry E;
		for(int i = 1;i<=size;i++){
			L=row[i];
			if(L.length()>0){
				L.moveFront();
				while(L.index()!=-1){
					E = (Entry)L.get();
					M.row[i].append(new Entry(E.col,E.value));
					M.NNZ++;
					L.moveNext();
				}
			}
		}
		return M;
	}
	// returns a new Matrix having the same entries as this Matrix

	void changeEntry(int i, int j, double x){
		if(i>size||j>size){
			throw new RuntimeException(
			"Matrix Error: changeEntry() called on an invalid Entry of a n x n Matrix");
		}
		if(i<1||j<1){
			throw new RuntimeException(
			"Matrix Error: changeEntry() called on an invalid Entry of a n x n Matrix");
		}
		row[i].moveFront();
		if(row[i].length()<=0&& x>0){
			Entry E = new Entry(j,x);
			row[i].append(E);
			NNZ++;
		}else{
			row[i].moveFront();
			if(x==0){
				boolean passed = false;
				boolean found = false;
				while(row[i].index()>=0&&!passed&&!found){
					Entry check = (Entry)row[i].get();
					if(check.col==j){
						row[i].delete();
						found=true;
						NNZ--;
					}
					if(check.col>j){
						passed = true;
					}
					row[i].moveNext();
				}
			}else{
				if(row[i].length()==0){
					Entry E = new Entry(j,x);
					row[i].append(E);
					NNZ++;
				}else{
					Entry head = (Entry)row[i].front();
					Entry tail = (Entry)row[i].back();
					if(head.col>j){
						Entry E =new Entry(j,x);
						row[i].prepend(E);
						NNZ++;
					}else if(tail.col<j){
						Entry E = new Entry(j,x);
						row[i].append(E);
						NNZ++;
					}else{
						boolean found = false;
						boolean passed = false;
						Entry check = (Entry)row[i].get();
						while(row[i].index()>=0 && !found && !passed){
							check = (Entry)row[i].get();
							if(check.col==j){
								check.value=x;
								NNZ++;
								found = true;
							}else{
								if(check.col>j){
									passed=true;
								}else{
									row[i].moveNext();
								}
							}
						}
						if(passed&&row[i].index()>=0){
							Entry E = new Entry(j,x);
							row[i].insertBefore(E);
							NNZ++;
						}else if(passed && row[i].index()==-1){
							Entry E = new Entry(j,x);
							row[i].append(E);
							NNZ++;
						}
					}
				}
			}
		}
			
	}
	// changes ith row, jth column of this Matrix to x
	// pre: 1<=i<=getSize(), 1<=j<=getSize()

	Matrix scalarMult(double x){
		Matrix mult = new Matrix(size);
		if(x>0){
			for(int i =1;i<=size;i++){
				if(row[i].length()>0){
					row[i].moveFront();
					while(row[i].index()>=0){
						Entry temp = (Entry)row[i].get();
						mult.row[i].append(new Entry(temp.col,temp.value*x));
						mult.NNZ++;
						row[i].moveNext();
					}
				}
			}
		}
		return mult;
	}
	// returns a new Matrix that is the scalar product of this Matrix with x
	Matrix add(Matrix M){
		if(size!=M.size){
			throw new RuntimeException(
				"Matrix Error: add() called on different size matries");
		}
		Matrix sum = new Matrix(size);
		for(int i=1;i<size;i++){
			if(row[i].length()>0||M.row[i].length()>0){
				row[i].moveFront();
				M.row[i].moveFront();
				while(row[i].index()>=0 || M.row[i].index()>=0){
					if(row[i].index()>=0 && M.row[i].index()>=0){
						Entry temp1 = (Entry)row[i].get();
						Entry temp2 = (Entry)M.row[i].get();
						
						if(temp1.col==temp2.col){
							double val = temp1.value+temp2.value;
							if(val!=0){
								sum.row[i].append(new Entry(temp1.col,val));
								sum.NNZ++;
							}
							if(row[i]==M.row[i]){
								row[i].moveNext();
							}else{
								row[i].moveNext();
								M.row[i].moveNext();
							}
						}else if(temp1.col<temp2.col){
							sum.row[i].append(new Entry(temp1.col,temp1.value));
							sum.NNZ++;
							row[i].moveNext();
						}else{
							sum.row[i].append(new Entry(temp2.col,temp2.value));
							sum.NNZ++;
							M.row[i].moveNext();
						}
					}else if(M.row[i].index()<0){
						Entry temp = (Entry)row[i].get();
						sum.row[i].append(new Entry(temp.col,temp.value));
						sum.NNZ++;
						row[i].moveNext();
					}else{
						Entry temp = (Entry) M.row[i].get();
						sum.row[i].append(new Entry(temp.col,temp.value));
						sum.NNZ++;
						M.row[i].moveNext();
					}
				}
			}
		}
		return sum;
		
	}
	// returns a new Matrix that is the sum of this Matrix with M
	// pre: getSize()==M.getSize()

	Matrix sub(Matrix M){
		if(size!=M.size){
			throw new RuntimeException(
				"Matrix Error: add() called on different size matries");
		}
		Matrix diff = new Matrix(size);
		for(int i=1;i<=size;i++){
			if(row[i].length()>0&&M.row[i].length()==0){
				row[i].moveFront();
				while(row[i].index()>=0){
					Entry E = (Entry)row[i].get();
					diff.row[i].append(new Entry(E.col,E.value));
					row[i].moveNext();
				}
			}
			if(row[i].length()==0&&M.row[i].length()>0){
				M.row[i].moveFront();
				while(M.row[i].index()>=0){
					Entry E = (Entry)M.row[i].get();
					diff.row[i].append(new Entry(E.col,0-E.value));
					M.row[i].moveNext();
				}
			}
			if(row[i].length()>0&&M.row[i].length()>0){
				row[i].moveFront();
				M.row[i].moveFront();
				while(row[i].index()>=0&&M.row[i].index()>=0){
					Entry temp1 = (Entry)row[i].get();
					Entry temp2 = (Entry)M.row[i].get();
					if(temp1.col==temp2.col){
						double val = temp1.value-temp2.value;
						if(val!=0){
							diff.row[i].append(new Entry(temp1.col,val));
							diff.NNZ++;
						}
						if(row[i]==M.row[i]){
							row[i].moveNext();
						}else{
							row[i].moveNext();
							M.row[i].moveNext();
						}
					}else if(temp1.col<temp2.col){
						diff.row[i].append(new Entry(temp1.col,temp1.value));
						diff.NNZ++;
						row[i].moveNext();
					}else{
						double val=0-temp2.value;
						diff.row[i].append(new Entry(temp2.col,val));
						diff.NNZ++;
						M.row[i].moveNext();
					}
				}
				if(row[i].index()>=0){
					while(row[i].index()>=0){
						Entry E = (Entry)row[i].get();
						diff.row[i].append(new Entry(E.col,E.value));
						diff.NNZ++;
						row[i].moveNext();
					}
				}
				if(M.row[i].index()>=0){
					while(M.row[i].index()>=0){
						Entry E = (Entry)M.row[i].get();
						diff.row[i].append(new Entry(E.col,0-E.value));
						diff.NNZ++;
						M.row[i].moveNext();
					}
				}
			}
		}
		return diff;
		
	}
	// returns a new Matrix that is the difference of this Matrix with M
	// pre: getSize()==M.getSize()

	Matrix transpose(){
		Matrix M =new Matrix(size);
		for(int i =1;i<=size;i++){
			row[i].moveFront();
			while(row[i].index()>=0){
				Entry temp = (Entry)(row[i].get());
				M.changeEntry(temp.col,i,temp.value);
				row[i].moveNext();
			}
		}
		return M;
	}
	// returns a new Matrix that is the transpose of this Matrix

	Matrix mult(Matrix M){
		if(size!=M.size){
			throw new RuntimeException(
			"Matrix Error: mult() called on a different size Matries");
		}
		Matrix prod = new Matrix(size);
		Matrix multiplier = M.transpose();
		double dotProd;
		for(int i = 1;i<=size;i++){
			if(row[i].length()>0){
				for(int j=1;j<=size;j++){
					if(multiplier.row[j].length()>0){
						dotProd=dot(row[i],multiplier.row[j]);
						if(dotProd!=0){
							prod.row[i].append(new Entry(i,dotProd));
							prod.NNZ++;
						}
					}
				}
			}
		}
		return prod;
	}
	// returns a new Matrix that is the product of this Matrix with M
	// pre: getSize()==M.getSize()

	// Other functions
	public String toString(){
		StringBuffer sb = new StringBuffer();
		for(int i =1;i<=size;i++){
			if(row[i].length()>0){
				sb.append(i);
				sb.append(": ");
				sb.append(row[i]);
				sb.append("\n");
			}
		}
		return new String(sb);
			
	} // overrides Object's toString() method
	
	private static double dot(List P, List Q){
		double dot = 0;
		P.moveFront();
		Q.moveFront();
		Entry mult1;
		Entry mult2;
		while(P.index()>=0&&Q.index()>=0){
			mult1 = (Entry)P.get();
			mult2 = (Entry)Q.get();
			if(mult1.col==mult2.col){
				dot+=(mult1.value*mult2.value);
				P.moveNext();
				Q.moveNext();
			}else if(mult1.col<mult2.col){
				P.moveNext();
			}else{
				Q.moveNext();
			}
		}
		return dot;
	}



}