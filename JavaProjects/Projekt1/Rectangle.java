public class Rectangle extends Figure implements Printing {
     double d, e;


    Rectangle(double d, double e) {
        if (d > 0 && e > 0 ) {
        this.d = d;
        this.e = e;
            } else {
                System.out.println("Boki musza byc wieksze od 0.\n");
            }
        
        
    }

    
    
    @Override
    public double calculateArea() {
        return d * e;
    }

    @Override
    public double calculatePerimeter() {
        return 2 * (d + e);
    }

    @Override
    public void print() {
        System.out.println("PROSTOKAT");
        System.out.println("Boki: " + d + ", " + e);
        System.out.println("Obwod: " + calculatePerimeter());
        System.out.println("Pole: " + calculateArea());
        System.out.println();
    }
}
