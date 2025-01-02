import java.util.Scanner;

public class T_03 {

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
                    int check_num;
                    check_num = Integer.parseInt(word);
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
        int[] int_nums = new int[len];
        int summ = 0, count = 0;
        for (int i = 0; i < len; i++) {
            int_nums[i] = Integer.parseInt(words[i]);
            if (int_nums[i] < 0){
                count++;
                summ += int_nums[i];
            }
        }
        if (count == 0){
            System.out.println("There are no negative elements");
        }
        else {
            System.out.println(summ / count);
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