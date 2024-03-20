public class Diamond extends Figure implements Printing {
     double x, y;

    Diamond(double x, double y) {
        if (x > 0 && y > 0) {
        this.x = x;
        this.y = y;
            } else {
                System.out.println("Przekatne musza byc wieksze od 0.\n");
            }
        
    }

    @Override
    public double calculatePerimeter() {
        double sideLength = 0.5 * Math.sqrt(x * x + y * y);
        return 4 * sideLength;
    }

    @Override
    public double calculateArea() {
        return (x * y) / 2;
    }

    @Override
    public void print() {
        System.out.println("ROMB");
        System.out.println("Przekatne: " + x + ", " + y);
        System.out.println("Obwod: " + calculatePerimeter());
        System.out.println("Pole: " + calculateArea());
        System.out.println();
    }
}
