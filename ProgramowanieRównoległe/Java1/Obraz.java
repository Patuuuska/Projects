import  java.util.Random;


class Obraz {
    
    private int size_n;
    private int size_m;
    private char[][] tab;
    private char[] tab_symb;
    private int[] histogram;
    private int[] histogram_parallel;
	private int[] histogram_parallel2;
  
    public Obraz(int n, int m) {
	
	this.size_n = n;
	this.size_m = m;
	tab = new char[n][m];
	tab_symb = new char[94];
	
	final Random random = new Random();
	
	// for general case where symbols could be not just integers
	for(int k=0;k<94;k++) {
	    tab_symb[k] = (char)(k+33); // substitute symbols
	}

	for(int i=0;i<n;i++) {
	    for(int j=0;j<m;j++) {	
		tab[i][j] = tab_symb[random.nextInt(94)];  // ascii 33-127
		//tab[i][j] = (char)(random.nextInt(94)+33);  // ascii 33-127
		System.out.print(tab[i][j]+" ");
	    }
	    System.out.print("\n");
	}
	System.out.print("\n\n"); 
	
	histogram = new int[94];
    histogram_parallel = new int[94];
	histogram_parallel2 = new int[94];
   	clear_histogram();
    }
    
    public void clear_histogram(){
	for(int i=0;i<94;i++) 
    {
        histogram[i]=0;
        histogram_parallel[i] = 0;
		histogram_parallel2[i] = 0;}

    }

    public void calculate_histogram(){

	  for(int i=0;i<size_n;i++) {
	    for(int j=0;j<size_m;j++) {

		  for(int k=0;k<94;k++) {
		    if(tab[i][j] == tab_symb[k]) histogram[k]++; 
		  }

	    }
	  }

    }

    public void print_histogram(){
	for(int i=0;i<94;i++) {
	    System.out.print(tab_symb[i]+" "+histogram[i]+"\n");	    
	}

    }
    public void calculate_histogram_parallel(int id) {
		for(int i=0;i<size_n;i++) {
			for(int j=0;j<size_m;j++) {
				if(tab[i][j] == tab_symb[id]) histogram_parallel[id]++;
			}
		}
	}

	public synchronized void print_histogram_parallel(int id) {
		System.out.print("Watek "+ id + ": " + tab_symb[id]+ " ");
		for(int i=0;i<histogram_parallel[id];i++){
			System.out.print("=");
		}
		System.out.print("\n");
	}

	public void equal() {
		boolean saRowne = true;
        
            for (int i = 0; i < 94; i++) {
                if (histogram[i] != histogram_parallel[i]) {
                    saRowne = false;
                    break;
                }
            }
        
            if (saRowne) {
                System.out.println("Tablice sa takie same.");
            } else {
                System.out.println("Tablice sa rozne.");
            }
        }
	public void calculate_histogram_parallel2(int start, int end) {
		for(int i=0;i<size_n;i++) {
			for(int j=0;j<size_m;j++) {
				for (int k = start; k < end; k++) {
				if(tab[i][j] == (char)(k+33)) histogram_parallel2[k]++;
				}
			}
		}
	}

	public synchronized void print_histogram_parallel2(int id, int start, int end) {
		for (int i = start; i < end; i++) {
			System.out.print("Watek " + id + ": " + tab_symb[i] + " ");
			for (int j = 0; j < histogram_parallel2[i]; j++) {
				System.out.print("=");
			}
			System.out.print("\n");
		}
	}

	public void equal2() {
            boolean saRowne = true;
        
            for (int i = 0; i < 94; i++) {
                if (histogram[i] != histogram_parallel2[i]) {
                    saRowne = false;
                    break;
                }
            }
        
            if (saRowne) {
                System.out.println("Tablice sa takie same.");
            } else {
                System.out.println("Tablice sa rozne.");
            }
        }
        
}


3
3