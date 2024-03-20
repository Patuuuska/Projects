import java.util.List;

public class Main {

    public static void main(String[] args) {
ClassContainer container = new ClassContainer();

    container.addClass("Programisci", 25);
    container.addClass("Kierownik", 1);
    container.addClass("Testerzy", 5); 
    container.addClass("HR", 5);  

        ClassEmployee Programisci = container.getGroup().get("Programisci");
        ClassEmployee Kierownik = container.getGroup().get("Kierownik");
        ClassEmployee Testerzy = container.getGroup().get("Testerzy");
        ClassEmployee HR = container.getGroup().get("HR");

        Employee employee1 = new Employee("Jan", "Nowak", EmployeeCondition.OBECNY, 2000, 17880.0);
        Employee employee2 = new Employee("Zosia", "Madej", EmployeeCondition.OBECNY, 1998, 1900.0);
        Employee employee3 = new Employee("Mateusz", "Walczak", EmployeeCondition.CHORY, 1990, 15000.0);
        Employee employee4 = new Employee("Tadeusz", "Kowal", EmployeeCondition.OBECNY, 1975, 13400.0);
        Employee employee5 = new Employee("Maja", "Borek", EmployeeCondition.DELEGACJA, 2001, 1940.0);
        Employee employee6 = new Employee("Ola", "Zachariasz", EmployeeCondition.NIEOBECNY, 1976, 20000.0);
        Employee employee7 = new Employee("Jan", "Nowak", EmployeeCondition.OBECNY, 2000, 17880.0);


        Testerzy.addEmployee(employee1);
        Testerzy.addEmployee(employee3);
        Kierownik.addEmployee(employee6);
        Programisci.addEmployee(employee2);
        Programisci.addEmployee(employee4);
        Programisci.addEmployee(employee5);

        //pracownik o takim samym imieniu i nazwisku
        Testerzy.addEmployee(employee7);


 //szukanie pustej grupy pracownikow
        List<ClassEmployee> emptyClasses = container.findEmpty();
        for (ClassEmployee emptyClass : emptyClasses) {
            System.out.println(emptyClass.getGroupName());
        }

        //dodawanie pensji dla praciwnika
        Programisci.addsalary(employee5, 500);
        employee5.print();
        
        //wyswietlanie calej grupy
        Kierownik.summary();

        //szukanie po nazwisku
        Employee word = Testerzy.search("Nowak");
        if(word!=null) {
            System.out.println("\nZnaleziono pracownika:");
            word.print();
        }
        else{
            System.out.println("Brak informacji");
        }
        
        //szukanie czesciowe
        List<Employee> word2 = Programisci.searchPartial("ek");
        if(word2.isEmpty()){
            System.out.println("Brak informacji");
        }
        else {
            for(Employee Employee : word2){
                System.out.println("\nZnaleziono pracownika:");
                Employee.print();
            }
        }

        //zmiana statusu pracownika
        Testerzy.changeCondition(employee1, EmployeeCondition.NIEOBECNY);

        //calosiowe podusumowanie
        container.summary();

        //usuwanie grupy
        container.removeClass("Kierownik");

        //szukanie ile jest osob po statusie
        System.out.println("Ilosc nieobecnych z grupy Testerzy: "+Testerzy.countByCondition(EmployeeCondition.NIEOBECNY));
       
        //sortowanie 
        System.out.println("\n***Posortowane dane (alfabetycznie): ");
        List<Employee> sort = Testerzy.sortByName();
        for(Employee employee : sort){
            employee.print();
        }


        System.out.println("\n***Posortowane dane (pensja): ");
        List<Employee> sort1 = Testerzy.sortBysalary();
        for (Employee employee : sort1){
            employee.print();
        }

        //szukanie max
        System.out.println("\n***Pracownik ktory najwiecej zarabia: ");
        Employee max = Programisci.max();
        max.print();

        

}}


