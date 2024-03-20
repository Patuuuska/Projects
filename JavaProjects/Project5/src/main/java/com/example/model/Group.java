package com.example.model;

import java.util.List;

public class Group {

    private String id;
    private String name;
    private List<String> employeeIds;


    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void addEmployeeId(String employeeId) {
        this.employeeIds.add(employeeId);
    }

    public List<String> getEmployeeIds() {
        return employeeIds;
    }
}
