import java.util.Scanner;

public class EnterData{
     
    public static String enterchoose() {
        System.out.println("Twoj wybor: ");
        Scanner scanner = new Scanner(System.in);
        return scanner.nextLine();
    }

    public static double enterabc() {
        System.out.println("Podaj dlugosc boku: ");
        Scanner scanner = new Scanner(System.in);
        return scanner.nextDouble();
    }

    public static double enterxy() {
        System.out.println("Podaj dlugosc przekatnej: ");
        Scanner scanner = new Scanner(System.in);
        return scanner.nextDouble();
       
    }

    public static double enterh() {
        System.out.println("Podaj wysokosc: ");
        Scanner scanner = new Scanner(System.in);
        return scanner.nextDouble();
    }
    
}

