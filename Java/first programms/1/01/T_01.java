import java.util.Scanner;

public class T_01 {

    public static void main(String[] argc){
        int sec;
        Scanner in = new Scanner(System.in);
        sec = input(in);
        in.close();
        if (sec < 0){
            System.out.println("Incorrect time");
        }
        else{
            sec = sec % 86400;
            int hours, minutes, seconds;
            hours = sec / 3600;
            minutes = (sec - hours * 3600) / 60;
            seconds = (sec - hours * 3600 - minutes * 60);
            System.out.printf("%02d:%02d:%02d", hours, minutes, seconds);
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