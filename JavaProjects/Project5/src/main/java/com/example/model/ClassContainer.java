package com.example.model;

import java.util.HashMap;
import java.util.Map;
import org.springframework.stereotype.Component;

@Component
public class ClassContainer {

    private Map<String, Employee> employees = new HashMap<>();
    private Map<String, Group> groups = new HashMap<>();
    private Map<String, Rating> ratings = new HashMap<>();

    public Map<String, Employee> getEmployees() {
        return employees;
    }

    public void setEmployees(Map<String, Employee> employees) {
        this.employees = employees;
    }

    public Map<String, Group> getGroups() {
        return groups;
    }

    public void setGroups(Map<String, Group> groups) {
        this.groups = groups;
    }

    public Map<String, Rating> getRatings() {
        return ratings;
    }

    public void setRatings(Map<String, Rating> ratings) {
        this.ratings = ratings;
    }
}
