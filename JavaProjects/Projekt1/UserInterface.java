public class UserInterface {
    public static void main(String[] args) {
        
        while (true) {
            System.out.println("__________________");
            System.out.println("Wybierz figure:\na -> TROJKAT\nb -> PROSTOKAT\nc -> ROMB\nd -> GRANIASTOSLUP\ne -> ZAMKNIJ");
            String choice = EnterData.enterchoose();
            
switch (choice) {
    case "a":
        double a = EnterData.enterabc();
        double b = EnterData.enterabc();
        double c = EnterData.enterabc();
           Triangle triangle = new Triangle(a, b, c);
           triangle.print();
        break;
    case "b":
        double d = EnterData.enterabc();
        double e = EnterData.enterabc();
        Rectangle rectangle = new Rectangle(d, e);
        rectangle.print();
        break;
    case "c":
        double x = EnterData.enterxy();
        double y = EnterData.enterxy();
        Diamond diamond = new Diamond(x, y);
        diamond.print();
        break;

    case "d":
    Figure figura;
    double h = EnterData.enterh();

    System.out.println("__________________");
            System.out.println("Wybierz figure:\na -> TROJKAT\nb -> PROSTOKAT\nc -> ROMB");
            String choice2 = EnterData.enterchoose();

        switch (choice2) {
            case "a":
        double a1 = EnterData.enterabc();
        double b1 = EnterData.enterabc();
        double c1 = EnterData.enterabc();
       
                
                    figura = new Triangle(a1, b1, c1);
                    Threedim threedim = new Threedim(figura, h);
                    threedim.print();
                
            break;
            case "b":
                
        double d1 = EnterData.enterabc();
        double e1 = EnterData.enterabc();
       

                
                   figura = new Rectangle(d1, e1);
                    Threedim threedim2 = new Threedim(figura, h);
                    threedim2.print();
            break;
            case "c":
                double x1 = EnterData.enterxy();
                double y1 = EnterData.enterxy();
       
                    figura = new Diamond(x1, y1);
                    Threedim threedim3 = new Threedim(figura, h);
                    threedim3.print();
                

            default:
            System.out.println("Zle dane");
            break;

            }


         break;

    
        case "e":
        System.out.println("Zegnam.");
        return;
        default:
        System.out.println("Podaj poprawny klawisz");
        break;
} 

        }
        
    }
    
}
