package se.liu.enzcu445.lab1;

import javax.swing.*;

public class Exercise2 {
    public static int sumFor(int min, int max){
        int sum = 0;
        for (int val = min; val < max+1; val++){
            sum += val;
        }
        return sum;
    }

    public static int sumWhile(int min, int max){
        int sum = 0;
        while (min < max+1){
            sum += min;
            min++;
        }
        return sum;
    }

    public static void main(String[] args) {
        String input = JOptionPane.showInputDialog("for eller while? ");

        switch (input){
            case "for":
                System.out.println(sumFor(10,11));
                break;
            case "while":
                System.out.println(sumWhile(9,11));
                break;
            default:
                System.out.println("felmeddelande");
                break;
        }

    }
}
