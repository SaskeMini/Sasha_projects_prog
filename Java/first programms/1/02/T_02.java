import java.util.Scanner;

public class T_02 {

    public static void main(String[] argc){
        int num;
        Scanner in = new Scanner(System.in);
        num = input(in);
        in.close();
        if (num > 47){
            System.out.println("Too large n");
        }
        else{
            System.out.println(fibbo(num));
        }
    }

    static int fibbo(int n){
        if (n == 1 || n == 2) {
            return 1;
        }
        else if (n == 0){
            return 0;
        }
        else{
            return fibbo(n - 1) + fibbo(n - 2);
        }
    }

    static int input(Scanner in){
        int num = 0;
        boolean check_in = false;
        String check_str;
        while(!check_in){
            check_str = in.nextLine();
            try{
                num = Integer.parseInt(check_str);
                check_in = true;
            }
            catch(Exception NumberFormatException){
                System.out.println("Couldn't parse a number. Please, try again");
                check_in = false;
            }
        }
        return num;
    }
}