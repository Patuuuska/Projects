package com.example.demo1;

public class Employee implements Comparable<Employee>{
    private String name;
    private String secondName;
    private EmployeeCondition employeeCondition;
    private int dateOfBirth;
    private double salary;

    public void setSecondName(String secondName) {
        this.secondName = secondName;
    }

    public void setDateOfBirth(int dateOfBirth) {
        this.dateOfBirth = dateOfBirth;
    }

    public void setSalary(double salary) {
        this.salary = salary;
    }

    public Employee(String imie, String nazwisko, EmployeeCondition stan, int rok, double pensja){
        this.name = imie;
        this.secondName = nazwisko;
        this.employeeCondition = stan;
        this.dateOfBirth = rok;
        this.salary = pensja;
    }

    public void printing(){
        System.out.println("\n*** Employee ***");
        System.out.println("Imie: " + this.name);
        System.out.println("Nazwisko: " + this.secondName);
        System.out.println("Stan: " + this.employeeCondition);
        System.out.println("Rok urodzenia: " + this.dateOfBirth);
        System.out.println("Wynagrodzenie: " + this.salary);
    }

    public String getName() {
        return name;
    }
    public String getSecondName() {
        return secondName;
    }

    public double getSalary() {
        return salary;
    }
    public int getDateOfBirth() {
        return dateOfBirth;
    }

    public EmployeeCondition getEmployeeCondition() {
        return employeeCondition;
    }

    public void setEmployeeCondition(EmployeeCondition employeeCondition) {
        this.employeeCondition = employeeCondition;
    }

    public void setName(String imie) {
        this.name = imie;
    }

    public void addSalary(double value){
        salary +=value;
    }
    @Override
    public int compareTo(Employee employee) {
        int compare = this.secondName.compareTo(employee.secondName);
        return compare;
    }
}


