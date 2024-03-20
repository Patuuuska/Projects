import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.ArrayList;
import java.util.List;

public class Simple_executor_test {

	private static final int NTHREADS = 8;
	private static final int NTASKS = 20; 
	public static void main(String[] args) {

		double poczatek = 0.0;
		double koniec = Math.PI;
		double przedzial = (koniec - poczatek) / NTASKS;
		double dx = 0.01;
		double wynik = 0.0;

		Counter counter = new Counter();
		ExecutorService executor = Executors.newFixedThreadPool(NTHREADS);
		List<Future<Double>> list = new ArrayList<>();

		for (int i = 0; i < NTASKS; i++) {
			double pocz = i * przedzial;
			double kon = (i+1) * przedzial;

			Calka_callable callable = new Calka_callable(pocz, kon, dx);
			Future<Double> future = executor.submit(callable);
			list.add(future);
		}

		for (Future<Double> list_future : list) {
			try {
				wynik += list_future.get();
			} catch (InterruptedException | ExecutionException e) {
		e.printStackTrace();
		}}

		executor.shutdown();

		System.out.println("Finished all threads");
		System.out.println("Wynik calki sin(x) = " + wynik);
		System.out.format("\nCounter_1: %d, Counter_2 %d\n\n",
				counter.get_c1(), counter.get_c2());
	}
}