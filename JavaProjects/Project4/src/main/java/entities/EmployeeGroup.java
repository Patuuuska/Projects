package entities;

import jakarta.persistence.*;

import java.util.ArrayList;
import java.util.List;

@Entity
public class EmployeeGroup {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private int id;

    String groupName;

    @OneToMany(mappedBy = "employeeGroup")
    List<Employee> listOfEmployees;
    int maxNumberOfEmployees;

    public EmployeeGroup(String groupName, int maxNoOfEmployees) {
        this.groupName = groupName;
        this.maxNumberOfEmployees = maxNoOfEmployees;
    }

    public EmployeeGroup() {

    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getGroupName() {
        return groupName;
    }

    public void setGroupName(String groupName) {
        this.groupName = groupName;
    }

    public List<Employee> getListOfEmployees() {
        return listOfEmployees;
    }

    public void setListOfEmployees(List<Employee> listOfEmployees) {
        this.listOfEmployees = listOfEmployees;
    }

    public int getMaxNoOfEmployees() {
        return maxNumberOfEmployees;
    }

    public void setMaxNoOfEmployees(int maxNoOfEmployees) {
        this.maxNumberOfEmployees = maxNoOfEmployees;
    }

}
