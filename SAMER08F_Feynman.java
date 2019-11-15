/*package whatever //do not write package name here */

import java.io.*;
import java.util.*;

class GFG {
	public static void main (String[] args) {
		//System.out.println("GfG!");
		
		Scanner sc = new Scanner(System.in);
		
		while(true){
		    int n = sc.nextInt();
		    
		    if(n == 0)
		    break;
		    
		    long ans = 0;
		    
		    while(n >= 1){
		        ans += (n*n);
		        n -= 1;
		    }
		    
		    System.out.println(ans);
		}
	}
}
