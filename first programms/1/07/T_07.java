import java.util.Scanner;

public class T_07 {

    public static void main(String[] argc){
        int num;
        Scanner in = new Scanner(System.in);
        work_with_numbers(in);
        in.close();
    }

    static void work_with_numbers(Scanner in){
        boolean check_in = true;
        int last_num = 0, err_ind = 0, iter = 0;
        try{
            last_num = Integer.parseInt(in.next());
        }
        catch(Exception NumberFormatException){
            System.out.println("Input error");
            check_in = false;
        }
        while(check_in){
            iter++;
            int curr_num;
            try{
                String check_str = in.next();
                curr_num = Integer.parseInt(check_str);
                if (curr_num <= last_num && err_ind == 0){
                    err_ind = iter;
                }
                last_num = curr_num;
            }
            catch(Exception NumberFormatException){
                check_in = false;
                break;
            }
        }
        if (err_ind == 0 && iter != 0){
            System.out.println("The sequence is ordered in ascending order");
        }
        else{
            System.out.printf("The sequence is not ordered from the ordinal number of the number %d", err_ind);
        }
    }
}