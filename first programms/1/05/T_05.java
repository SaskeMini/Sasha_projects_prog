import java.util.Scanner;

public class T_05 {

    public static void main(String[] argc){
        int num;
        Scanner in = new Scanner(System.in);
        num = input(in);
        if (num <= 0){
            System.out.println("Input error. Size <= 0");
        }
        else{
            work_with_numbers(in, num);
        }
        in.close();
    }

    static void work_with_numbers(Scanner in, int len){
        boolean check_in = false;
        String check_str;
        String[] words = new String[len];
        while(!check_in){
            check_in = true;
            check_str = in.nextLine();
            words = check_str.split(" ");
            for (String word : words){
                try{
                    double check_num;
                    check_num = Double.parseDouble(word);
                }
                catch(Exception NumberFormatException){
                    System.out.println("Couldn't parse a number. Please, try again");
                    check_in = false;
                    break;
                }
            }
            if (words.length != len && check_in){
                check_in = false;
                System.out.println("Couldn't parse a number. Please, try again");
            }
        }
        sort_mass(words, len);
    }

    static void sort_mass(String[] mass, int len){
        double[] res_nums = new double[len];
        for (int i = 0; i < len; i++){
            res_nums[i] = Double.parseDouble(mass[i]);
        }
        double min_num = 0;
        int min_ind = 0;
        for (int i = 0; i < len; i++){
            min_num = res_nums[i];
            min_ind = i;
            for (int j = i + 1; j < len; j++){
                if (res_nums[j] < min_num){
                    min_num = res_nums[j];
                    min_ind = j;
                }
            }
            if (i != min_ind){
                double temp = res_nums[i];
                res_nums[i] = min_num;
                res_nums[min_ind] = temp;
            }
        }
        for (int i = 0; i < len - 1; i++){
            System.out.printf("%f ", res_nums[i]);
        }
        System.out.printf("%f", res_nums[len - 1]);
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