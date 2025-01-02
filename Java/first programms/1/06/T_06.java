import java.util.Scanner;
import java.io.*;

public class T_06 {

    public static void main(String[] argc){
        String file_name, xz = "";
        Scanner in = new Scanner(System.in);
        file_name = in.nextLine();
        File file_in = new File(file_name);
        try(Scanner fin = new Scanner(file_in)){
            xz = fin.nextLine();
            file_input(fin, xz);
        }
        catch(Exception FileNotFoundException){
            System.out.println("Input error. File isn't exist");
        }
        in.close();
    }

    static void file_input(Scanner fin, String xz){
        int len = 0;
        String[] words;
        len = Integer.parseInt(xz);
        if (len > 0){
            words = new String[len];
            xz = fin.nextLine();
            words = xz.split(" ");
            double[] nums = new double[len];
            int i = 0;
            for (String word : words){
                boolean check = true;
                double check_num = 0;
                try{
                    check_num = Double.parseDouble(word);
                }
                catch(Exception NumberFormatException){
                    check = false;
                }
                if (check){
                    nums[i++] = check_num;
                }
            }
            if (i < len){
                System.out.println("Input error. Insufficient number of elements");
            }
            else{
                min_max(len, nums);
            }
        }
        else{
            System.out.println("Input error. Size <= 0");
        }
    }

    static void min_max(int len, double[] mass){
        double min = mass[0];
        double max = mass[0];
        for (int i = 0; i < len; i++){
            if (mass[i] < min){
                min = mass[i];
            }
            if (mass[i] > max){
                max = mass[i];
            }
        }
        String res = String.valueOf(min) + " " + String.valueOf(max);
        try(FileOutputStream fout = new FileOutputStream("result.txt", false)){
            byte[] buff = res.getBytes();
            fout.write(buff, 0, buff.length);
            System.out.println(len);
            for (int i = 0; i < len - 1; i++){
                System.out.printf("%f ", mass[i]);
            }
            System.out.printf("%f\n", mass[len - 1]);
            System.out.println("Saving min and max values in file");
        }
        catch(IOException ex){
            System.out.println(ex.getMessage());
        } 
    }
}