import java.util.Scanner;

public class T_09 {

    public static void main(String[] argc){
        int num;
        Scanner in = new Scanner(System.in);
        num = input(in, false);
        work_with_users(in, num);
        in.close();
    }

    static void work_with_users(Scanner in, int len){
        User[] mass = new User[len];
        for (int i = 0; i < len; i++){
            mass[i] = new User();
            mass[i].name = in.nextLine();
            int temp_age = input(in, true);
            if (temp_age > 0){
                mass[i].age = temp_age;
            }
            else{
                i--;
            }
        }
        boolean check = false;
        for (int i = 0; i < len; i++){
            if (mass[i].age >= 18){
                if (check){
                    System.out.printf(", %s", mass[i].name);
                }
                else{
                    System.out.printf("%s", mass[i].name);
                    check = true;
                }
            }
        }
    }

    static int input(Scanner in, boolean age){
        int num = 0;
        boolean check_in = false;
        String check_str;
        while(!check_in){
            check_str = in.nextLine();
            try{
                num = Integer.parseInt(check_str);
                check_in = true;
                if (age && num <= 0){
                    System.out.println("Incorrect input. Age <= 0");
                }
                else if (!age && num <= 0){
                    System.out.println("Couldn't parse a number. Please, try again");
                    check_in = false;
                }
            }
            catch(Exception NumberFormatException){
                System.out.println("Couldn't parse a number. Please, try again");
                check_in = false;
            }
        }
        return num;
    }
}