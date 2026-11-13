package se.liu.enzcu445.lab1;

public class Exercise6 {
    public static void main(String[] args) {
        //System.out.println(isPrime(4));
        for (int i = 2; i < 101; i++) {
            if (isPrime(i)){
                System.out.println(i);
            }
        }
    }
    public static boolean isPrime(int number) {
        if (number < 2) {
            return false;
        }

        for (int i = 2; i < number; i++) {
            if (number % i == 0) {
                return false;
            }
        }
        return true;
    }
}
