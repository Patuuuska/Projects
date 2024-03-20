package com.example.service;

import com.example.model.ClassContainer;
import com.example.model.Group;
import com.example.model.Employee;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.ArrayList;



@Service
public class GroupService {

    private final ClassContainer classContainer;

    @Autowired
    public GroupService(ClassContainer classContainer) {
        this.classContainer = classContainer;
    }

    public List<Group> getAllGroups() {
        return List.copyOf(classContainer.getGroups().values());
    }

    public Group getGroupById(String id) {
        return classContainer.getGroups().get(id);
    }

    public void addGroup(Group group) {

        if (group.getId() == null || group.getId().isEmpty()) {
            throw new IllegalArgumentException("Id grupy nie może być puste");
        }

        if (classContainer.getGroups().containsKey(group.getId())) {
            throw new IllegalArgumentException("Id grupy musi być unikalne");
        }

        List<String> employeeIds = group.getEmployeeIds();
        for (String employeeId : employeeIds) {
            Employee employee = classContainer.getEmployees().get(employeeId);
            if (employee != null) {
                employee.setGroupId(group.getId());
            }
        }

        classContainer.getGroups().put(group.getId(), group);
    }

    public void addEmployeeToGroup(Employee employee, String groupId) {
        Group group = classContainer.getGroups().get(groupId);

        if (employee != null && group != null) {
            employee.setGroupId(groupId);

            group.getEmployeeIds().add(employee.getId());

            classContainer.getEmployees().put(employee.getId(), employee);
        } else {
            throw new IllegalArgumentException("Employee or Group not found");
        }
    }

    public void deleteGroup(String id) {
        classContainer.getGroups().remove(id);
    }

    public List<Employee> getEmployeesInGroup(String groupId) {
        Group group = classContainer.getGroups().get(groupId);
        if (group != null) {
            List<Employee> employeesInGroup = new ArrayList<>();
            for (String employeeId : group.getEmployeeIds()) {
                Employee employee = classContainer.getEmployees().get(employeeId);
                if (employee != null) {
                    employeesInGroup.add(employee);
                }
            }
            return employeesInGroup;
        } else {
            throw new IllegalArgumentException("Group with id " + groupId + " not found");
        }
    }
    public double getGroupFillPercentage(String groupId) {
        Group group = classContainer.getGroups().get(groupId);
        if (group != null) {
            int totalEmployees = 10;
            int groupSize = group.getEmployeeIds().size();
            return (double) groupSize / totalEmployees * 100;
        } else {
            throw new IllegalArgumentException("Group with id " + groupId + " not found");
        }
    }
}
