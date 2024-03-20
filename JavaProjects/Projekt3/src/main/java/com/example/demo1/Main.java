package com.example.demo1;

import com.example.demo1.ClassContainer;
import com.example.demo1.Employee;
import com.example.demo1.EmployeeCondition;

import java.util.List;

public class Main {
    public static void main(String[] args) {

        ClassContainer container = new ClassContainer();

        container.addClass("Programisci", 25);
        container.addClass("Kierownik", 1);
        container.addClass("Testerzy", 5);
        container.addClass("HR", 5);


        Employee employee1 = new Employee("Jan", "Nowak", EmployeeCondition.OBECNY, 2000, 17880.0);
        Employee employee2 = new Employee("Zosia", "Madej", EmployeeCondition.OBECNY, 1998, 1900.0);
        Employee employee3 = new Employee("Mateusz", "Walczak", EmployeeCondition.CHORY, 1990, 15000.0);
        Employee employee4 = new Employee("Tadeusz", "Kowal", EmployeeCondition.OBECNY, 1975, 13400.0);
        Employee employee5 = new Employee("Maja", "Borek", EmployeeCondition.DELEGACJA, 2001, 1940.0);
        Employee employee6 = new Employee("Ola", "Zachariasz", EmployeeCondition.NIEOBECNY, 1976, 20000.0);
        Employee employee7 = new Employee("Joanna", "Nowicka", EmployeeCondition.OBECNY, 2000, 17880.0);


        container.findClassByName("Testerzy").addEmployee(employee1);
        container.findClassByName("Testerzy").addEmployee(employee3);
        container.findClassByName("Programisci").addEmployee(employee2);
        container.findClassByName("Kierownik").addEmployee(employee6);
        container.findClassByName("Programisci").addEmployee(employee5);
        container.findClassByName("Programisci").addEmployee(employee7);

    }
}