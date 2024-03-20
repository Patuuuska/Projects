public class Runnable_watek implements Runnable {
    private Obraz obraz;
    private int id;
    private int start;
    private int end;

    public Runnable_watek(Obraz obraz, int id, int start, int end) {
        this.obraz = obraz;
        this.id = id;
        this.start = start;
        this.end = end;
    }

    @Override
    public void run() {
        obraz.calculate_histogram_parallel2(start, end);
        obraz.print_histogram_parallel2(id, start, end);
    }
}

