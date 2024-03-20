public class Threedim implements Printing {
     Figure base;
     double h;

    Threedim(Figure base, double h) {
    if (h > 0 ) {
        this.base = base;
        this.h = h;}
    else {
        System.out.println("Wysokosc musi byc wieksza niz 0.\n");
    }
    }
    
    public double calculateArea() { //powierzchnia
        return (2 * base.calculateArea() + base.calculatePerimeter()*h );
    }
    
    public double calculateVolume() { //objetosc
        return base.calculateArea() * h;
    }

    
    public void print() {
        System.out.println("GRANIASTOSLUP");
        System.out.println("Wysokosc: " + h);
        System.out.println("Pole podstawy: " + base.calculateArea());
        System.out.println("Pole calej powierzchni: " + calculateArea());
        System.out.println("Objetosc: " + calculateVolume());
        System.out.println();
    }
}
