package se.liu.enzcu445.lab1;

import javax.swing.*;

public class Exercise3 {
    private final static int TABELL = 5;

    public static void main(String[] args) {
        String input =
                JOptionPane.showInputDialog("Please input a value");

        int tabell = Integer.parseInt(input);

        for(int i = 0; i < 13; i++){
            System.out.println(i+" * " +tabell +" = "+ i*tabell);
        }
    }

}
