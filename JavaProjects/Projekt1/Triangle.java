
public class Triangle extends Figure implements Printing {
    double a;
    double b;
    double c;

    public Triangle(double a, double b, double c) {
         if (a > 0 && b > 0 && c > 0 && (a + b) > c && (a + c) > b && (b + c) > a) {
        this.a = a;
        this.b = b;
        this.c = c;
            } else {
                System.out.println("Boki musza byc wieksze od 0 i spelniac warunek trojkata.\n");
            }
        
    }

    @Override
    public double calculateArea() {
        double perimeter = calculatePerimeter() / 2;
        return Math.sqrt(perimeter * (perimeter - a) * (perimeter - b) * (perimeter - c));
    }

    @Override
    public double calculatePerimeter() {
        return a + b + c;
    }

    @Override
    public void print() {
        System.out.println("TROJKAT");
        System.out.println("Boki trojkata: " + a + ", " + b + ", " + c);
        System.out.println("Obwod: " + calculatePerimeter());
        System.out.println("Pole: " + calculateArea());
        System.out.println();
    }

    
}
