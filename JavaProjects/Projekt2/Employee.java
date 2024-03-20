import java.lang.Comparable;

public class Employee implements Comparable<Employee> {
    private String name;
    private String secondName;
    private EmployeeCondition ;
    private int dateOfBirth;
    private double salary;

    public Employee(String name, String secondName, EmployeeCondition employeeState, Integer dateOfBirth, Double salary) {
        this.name = name;
        this.secondName = secondName;
        this.employeeState = employeeState;
        this.dateOfBirth = dateOfBirth;
        this.salary = salary;
    }

    public String getname() {
        return this.name;
    }

    public String getsecondName() {
        return this.secondName;
    }

    public EmployeeCondition getemployeeCondition() {
        return this.employeeState;
    }

    public void setEmployeeState(EmployeeCondition state) {
        this.employeeState = state;
    }

    public int getDateOfBirth() {
        return this.dateOfBirth;
    }

    public double getsalary() {
        return this.salary;
    }

    public void setsalary(double sal) {
        this.salary = sal;
    }

    public void print() {
        System.out.println("\n*** Employee ***");
        System.out.println("Imie: " + this.name);
        System.out.println("Nazwisko: " + this.secondName);
        System.out.println("Stan: " + this.employeeState);
        System.out.println("Rok urodzenia: " + this.dateOfBirth);
        System.out.println("Wynagrodzenie: " + this.salary);
    }

    @Override
    public int compareTo(Employee Employee) {
        int compare = this.secondName.compareTo(Employee.secondName);
        return compare;
    }

}
