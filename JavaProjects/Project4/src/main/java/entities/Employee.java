package entities;

import jakarta.persistence.*;
@Entity
public class Employee {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private int id;
    String name;
    String secondName;
    @Enumerated(EnumType.STRING)
    @Column(name = "state")
    EmployeeCondition employeeState;
    int dateOfBirth;
    double salary;

    @ManyToOne
    @JoinColumn(name = "employeeGroup")
    EmployeeGroup employeeGroup;

    public Employee(String name, String secondName, EmployeeCondition employeeState, Integer dateOfBirth, Double salary) {
        this.name = name;
        this.secondName = secondName;
        this.employeeState = employeeState;
        this.dateOfBirth = dateOfBirth;
        this.salary = salary;
    }

    public Employee() {

    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
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

    public void setEmployeeGroup(EmployeeGroup employeeGroup) {
        this.employeeGroup = employeeGroup;
    }
}
