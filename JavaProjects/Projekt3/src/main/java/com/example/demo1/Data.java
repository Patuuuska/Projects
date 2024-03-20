package com.example.demo1;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;


public class Data {

    private ObservableList<ClassEmployee> listEmployees = FXCollections.observableArrayList();
    public ObservableList<ClassEmployee> getGroups() {
        return this.listEmployees;
    }
    public Data() {

        Employee employee1 = new Employee("Jan", "Nowak", EmployeeCondition.OBECNY, 2000, 17880.0);
        Employee employee2 = new Employee("Zosia", "Madej", EmployeeCondition.OBECNY, 1998, 1900.0);
        Employee employee3 = new Employee("Mateusz", "Walczak", EmployeeCondition.CHORY, 1990, 15000.0);
        Employee employee4 = new Employee("Tadeusz", "Kowal", EmployeeCondition.OBECNY, 1975, 13400.0);
        Employee employee5 = new Employee("Maja", "Borek", EmployeeCondition.DELEGACJA, 2001, 1940.0);
        Employee employee6 = new Employee("Ola", "Zachariasz", EmployeeCondition.NIEOBECNY, 1976, 20000.0);
        Employee employee7 = new Employee("Jan", "Nowak", EmployeeCondition.OBECNY, 2000, 17880.0);


        ObservableList<Employee> list = FXCollections.observableArrayList();
    ClassEmployee Testerzy = new ClassEmployee("Testerzy", list, 5);
    Testerzy.addEmployee(employee1);
    Testerzy.addEmployee(employee3);

    ObservableList<Employee> list2 = FXCollections.observableArrayList();
    ClassEmployee Kierownik = new ClassEmployee("Kierownik", list2, 1);
    Kierownik.addEmployee(employee6);

    ObservableList<Employee> list3 = FXCollections.observableArrayList();
    ClassEmployee HR = new ClassEmployee("HR", list3, 5);
    HR.addEmployee(employee5);

    ObservableList<Employee> list4 = FXCollections.observableArrayList();
    ClassEmployee Programisci = new ClassEmployee("Programisci", list4, 25);
    Programisci.addEmployee(employee2);
    Programisci.addEmployee(employee4);
    Programisci.addEmployee(employee7);


    this.listEmployees.add(Testerzy);
    this.listEmployees.add(Programisci);
    this.listEmployees.add(HR);
    this.listEmployees.add(Kierownik);
    }
}
