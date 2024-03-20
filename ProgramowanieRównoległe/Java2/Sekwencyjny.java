public class Sekwencyjny {
    public static void main(String[] args) {
     
    double poczatek = 0.0;
    double koniec = Math.PI;
    double dx = 0.01;

    Calka_callable Calka = new Calka_callable(poczatek, koniec, dx);
    double calka_sekwencyjna = Calka.compute_integral();
}

}