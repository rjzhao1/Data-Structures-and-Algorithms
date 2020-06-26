//Ricky Zhao
//Rjzhao
//pa1
import java.io.*;
import java.util.Scanner;
public class Lex{
	public static void main(String []args) throws IOException{
		if(args.length != 2){
			System.err.println("Usage: Lex <File 1> <File 2>");
			System.exit(1);
		}
		
		Scanner in = new Scanner(new File(args[0]));
		Scanner in2 = new Scanner(new File(args[0]));
		PrintWriter out = new PrintWriter(new FileWriter(args[1]));
		
		int len = 0;
		
		while(in.hasNextLine()){
			len++;
			in.nextLine();
		}
		
		String[] word = new String[len];
		for(int i =0;i<len;i++){
			word[i]=in2.nextLine();
		}
		List wordInd = new List();
		wordInd.append(0);
		
		for(int i =1;i<len;i++){
			wordInd.moveFront();
			while(wordInd.index()!=-1&&word[i].compareTo(word[wordInd.get()])>0){
				wordInd.moveNext();
			}
			if(wordInd.index()!=-1){
				wordInd.insertBefore(i);
			}else{
				wordInd.append(i);
			}
		}
		
		wordInd.moveFront();
		while(wordInd.index()!=-1){
			out.println(word[wordInd.get()]);
			wordInd.moveNext();
		}
		
		in.close();
		in2.close();
		out.close();
	}
}
