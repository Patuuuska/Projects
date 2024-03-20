import java.util.Scanner;


class Histogram_test {
    
    public static void main(String[] args) {

	Scanner scanner = new Scanner(System.in);
	
	System.out.println("Set image size: n (#rows), m(#kolumns)");
	int n = scanner.nextInt();
	int m = scanner.nextInt();
	Obraz obraz_1 = new Obraz(n, m);

	obraz_1.calculate_histogram();
	obraz_1.print_histogram();

    System.out.println("Wariant 1");
	int num_threads = 94;

	Watek[] NewThr = new Watek[num_threads];
    
	for (int i = 0; i < num_threads; i++) {
	    (NewThr[i] = new Watek(obraz_1, i)).start();
	 }
    
	for (int i = 0; i < num_threads; i++) {
	    try {
		NewThr[i].join();
	    } catch (InterruptedException e) {}
	}

obraz_1.equal();

System.out.println("Wariant 2"); //obiekty klasy runnable są przekazywane do konstruktora Thread
	System.out.println("Set number of threads");
	int num_threads_2 = scanner.nextInt();
int ilosc = (int)Math.ceil(94/(double)num_threads_2);
	Thread[] NewThr_2 = new Thread[num_threads_2];
for (int i = 0; i < num_threads_2; i++) {
		int start = ilosc * i;
		int end = ilosc * ( i + 1 );
		if(end > 93) {
			end = 93;
		}
	NewThr_2[i] = new Thread(new Runnable_watek(obraz_1, i, start, end));
		NewThr_2[i].start();
	}

	for (int i = 0; i < num_threads_2; i++) {
		try {
			NewThr_2[i].join();
		} catch (InterruptedException e) {
		}
	}
	obraz_1.equal2();
    }

}
    

