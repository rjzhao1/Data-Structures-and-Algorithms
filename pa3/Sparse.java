//Ricky Zhao
//Rjzhao
//pa3
import java.io.*;
import java.util.Scanner;
public class Sparse{
	public static void main (String[] args)throws IOException{
		if(args.length != 2){
			System.err.println("Usage: Sparse <File 1> <File 2>");
			System.exit(1);
		}
		
		Scanner in = new Scanner(new File(args[0]));
		PrintWriter out = new PrintWriter(new FileWriter(args[1]));
		int size = in.nextInt();
		int NNZ1 = in.nextInt();
		int NNZ2 = in.nextInt();
		
		int row;
		int col;
		double val;
		
		Matrix A = new Matrix(size);
		Matrix B = new Matrix(size);
		
		for(int i =1; i<=NNZ1;i++){
			row = in.nextInt();
			col = in.nextInt();
			val = in.nextDouble();
			A.changeEntry(row,col,val);
		}
		
		for(int i =1; i<=NNZ2;i++){
			row = in.nextInt();
			col = in.nextInt();
			val = in.nextDouble();
			B.changeEntry(row,col,val);
		}
		
		Matrix scalarMatrix = A.scalarMult(1.5);
		Matrix sumMatrix = A.add(B);
		Matrix sumMatrix2 = A.add(A);
		Matrix diffMatrix = B.sub(A);
		Matrix diffMatrix2 = A.sub(A);
		Matrix tranMatrix = A.transpose();
		Matrix prodMatrix = A.mult(B);
		Matrix prodMatrix2 = B.mult(B);
		
		
		out.println("A has " + A.getSize() + " non-zero entries:");
		out.println(A);
		out.println("B has " + B.getSize() + " non-zero entries:");
		out.println(B);
		out.println("(1.5)*A = ");
		out.println(scalarMatrix);
		out.println("A+B = ");
		out.println(sumMatrix);
		out.println("A+A = ");
		out.println(sumMatrix2);
		out.println("B-A = ");
		out.println(diffMatrix);
		out.println("A-A = ");
		out.println(diffMatrix2);
		out.println("Transpose(A) = ");
		out.println(tranMatrix);
		out.println("A*B = ");
		out.println(prodMatrix);
		out.println("B*B = ");
		out.println(prodMatrix2);
		
		in.close();
		out.close();
	}
}