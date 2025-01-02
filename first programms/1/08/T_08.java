import java.util.Scanner;

public class T_08 {

    public static void main(String[] argc){
        int num;
        Scanner in = new Scanner(System.in);
        num = input(in);
        if (num <= 0){
            System.out.println("Input error. Size <= 0");
        }
        else{
            work_with_strings(in, num);
        }
        in.close();
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

    static void work_with_strings(Scanner in, int len){
        String[] mass = new String[len];
        for (int i = 0; i < len; i++){
            mass[i] = in.nextLine();
        }
        String pod = in.nextLine();
        int len_pod = pod.length();
        boolean check = false;
        for (int i = 0; i < len; i++){
            for (int j = 0; j < mass[i].length() - len_pod; j++){
                if (mass[i].substring(j, j + len_pod).equals(pod)){
                    if (check){
                        System.out.printf(", %s", mass[i]);
                    }
                    else{
                        System.out.printf("%s", mass[i]);
                        check = true;
                    }
                    break;
                }
            }
        }
    }
}