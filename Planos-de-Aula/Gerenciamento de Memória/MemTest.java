import java.util.Scanner;

class MemTest{
	public static void main(String[] args){
		Scanner s = new Scanner(System.in);
		String input = null;
		do{
			input = s.nextLine();
			for(int i=0; i<Integer.parseInt(input); i++){
				System.out.println(new String(i+""));
			}
			
		}while(true);
	}
}
