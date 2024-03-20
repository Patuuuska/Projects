public class Watek extends Thread {
    private Obraz obraz;
    private int id;

    public Watek(Obraz obraz, int id) {
        this.obraz = obraz;
        this.id = id;
    }

    @Override
    public void run() {
        obraz.calculate_histogram_parallel(id);
        obraz.print_histogram_parallel(id);
    }
}
