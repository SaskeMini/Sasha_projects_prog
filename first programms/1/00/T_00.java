import java.util.Scanner;

public class T_00 {

    public static void main(String[] argc){
        double x_1, x_2, x_3, y_1, y_2, y_3;
        Scanner in = new Scanner(System.in);
        x_1 = input(in);
        y_1 = input(in);
        x_2 = input(in);
        y_2 = input(in);
        x_3 = input(in);
        y_3 = input(in);
        in.close();
        var n_11 = Math.round(Math.sqrt(((x_2 - x_1) * (x_2 - x_1) + (y_2 - y_1) * (y_2 - y_1))) * 1000);
        var n_22 = Math.round(Math.sqrt(((x_3 - x_2) * (x_3 - x_2) + (y_3 - y_2) * (y_3 - y_2))) * 1000);
        var n_33 = Math.round(Math.sqrt(((x_1 - x_3) * (x_1 - x_3) + (y_1 - y_3) * (y_1 - y_3))) * 1000);
        double n_1 = (double)n_11 / 1000;
        double n_2 = (double)n_22 / 1000;
        double n_3 = (double)n_33 / 1000;
        if (n_1 + n_2 > n_3 && n_1 + n_3 > n_2 && n_2 + n_3 > n_1){
            System.out.printf("Perimeter: %.3f", n_1 + n_2 + n_3);
        }
        else{
            System.out.println("It isn't triangle");
        }
    }

    static double input(Scanner in){
        double num = 0;
        boolean check_in = false;
        String check_str;
        while(!check_in){
            check_str = in.nextLine();
            try{
                num = Double.parseDouble(check_str);
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