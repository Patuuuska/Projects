package com.example.service;

import com.example.model.ClassContainer;
import com.example.model.Employee;

import org.springframework.stereotype.Service;

import java.util.ArrayList;
import java.util.List;

@Service
public class EmployeeService {

    private final ClassContainer classContainer;

    public EmployeeService(ClassContainer classContainer) {
        this.classContainer = classContainer;
    }

    public List<Employee> getAllEmployees() {
        return new ArrayList<>(classContainer.getEmployees().values());
    }

    public Employee getEmployeeById(String id) {
        return classContainer.getEmployees().get(id);
    }

    public void addEmployee(Employee employee) {
        classContainer.getEmployees().put(employee.getId(), employee);
    }

    public void deleteEmployee(String id) {
        classContainer.getEmployees().remove(id);
    }
}
