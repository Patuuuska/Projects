package com.example.demo1;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

public class ClassEmployee {
    private String groupName;
    private ObservableList<Employee> listOfEmployee;
    private int maxNumberOfEmployee;

    public ClassEmployee(String groupName, ObservableList<Employee> list, int maxEmployees) {
        this.groupName = groupName;
        this.maxNumberOfEmployee = maxEmployees;
        this.listOfEmployee = list;
    }
    public ClassEmployee(String groupName, int maxEmployees) {
        this.groupName = groupName;
        this.maxNumberOfEmployee = maxEmployees;
        this.listOfEmployee = FXCollections.observableArrayList();
    }

    public void addEmployee(Employee employee) {
        if (isEmployeeInGroup(employee)) {
            System.out.println("Pracownik o takim imieniu i nazwisku istnieje.");
        } else if (listOfEmployee.size() >= maxNumberOfEmployee) {
            System.err.println("Za dużo pracowników w danej grupie.");
        } else {
            listOfEmployee.add(employee);  }
    }
    public void addSalary(Employee employee, double value) {
        if (isEmployeeInGroup(employee)) {
            employee.addSalary(value);
        }
        else {
            System.out.println("Pracownik nie istnieje w grupie.");
        }
    }

    public void removeEmployee(Employee employee) {
        if (isEmployeeInGroup(employee)) {
            listOfEmployee.remove(employee);
        } else {
            System.out.println("Pracownik nie istnieje w grupie.");        }
    }

    public void changeCondition(Employee employee, EmployeeCondition condition) {
        if (isEmployeeInGroup(employee)) {
            employee.setEmployeeCondition(condition);
        } else {
            System.out.println("Pracownik nie istnieje w grupie.");         }
    }

    public Employee search(String secondName) {
        for (Employee Employee : listOfEmployee) {
            if (Employee.getSecondName().compareTo(secondName) == 0) {
                return Employee;
            }
        }
        return null;
    }

    public List<Employee> searchPartial(String word) {
        List<Employee> allowList = new ArrayList<>();
        for (Employee Employee : listOfEmployee) {
            if (Employee.getSecondName().contains(word) || Employee.getName().contains(word)) {
                allowList.add(Employee);
            }
        }
        return allowList;
    }

    public int countByCondition(EmployeeCondition state) {
        int counter = 0;
        for (Employee Employee : listOfEmployee) {
            if (Employee.getEmployeeCondition().equals(state)) {
                counter++;
            }
        }
        return counter ;
    }
    public void summary() {
        System.out.println("\n*** Grupa: ***");
        for (Employee employee : listOfEmployee) {
            employee.printing();
        }
        System.out.println("\n**************");
    }

    public List<Employee> sortByName() {

        List<Employee> sort = new ArrayList<>(listOfEmployee);
        sort.sort(Employee::compareTo);
        return sort;
    }

    public List<Employee> sortBysalary() {

        List<Employee> sort = new ArrayList<>(listOfEmployee);
        sort.sort(new Comparator<Employee>() {

            @Override
            public int compare(Employee Employee1, Employee Employee2) {
                return Double.compare(Employee1.getSalary(), Employee2.getSalary());
            }
        });
        return sort;
    }

    private boolean isEmployeeInGroup(Employee employee) {
        for (Employee e : listOfEmployee) {
            if (e.getName().equals(employee.getName()) && e.getSecondName().equals(employee.getSecondName())) {
                return true;
            }
        }
        return false;
    }

    public List<Employee> getListOfEmployee() {
        return listOfEmployee;
    }

    public int getMaxNumberOfEmployee() {
        return maxNumberOfEmployee;
    }

    public String getGroupName() {
        return groupName;
    }

    public void setGroupName(String groupName) {
        this.groupName = groupName;
    }

      public double getPercentage(){
        double p = ((double) listOfEmployee.size()/ maxNumberOfEmployee)*100.0;
        return p;
    }
}
