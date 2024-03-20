package com.example.service;

import com.example.model.ClassContainer;
import com.example.model.Employee;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.io.FileWriter;
import java.io.IOException;
import java.util.Map;

@Service
public class CsvGenerator {

    private final ClassContainer classContainer;

    @Autowired
    public CsvGenerator(ClassContainer classContainer) {
        this.classContainer = classContainer;
    }

    public void generateCsv(String fileName) throws IOException {
        try (FileWriter writer = new FileWriter(fileName)) {
            // Header
            writer.append("ID,Name,Position,GroupID\n");

            // Employees
            for (Map.Entry<String, Employee> entry : classContainer.getEmployees().entrySet()) {
                Employee employee = entry.getValue();
                writer.append(String.format("%s,%s,%s,%s\n",
                        employee.getId(), employee.getName(), employee.getPosition(), employee.getGroupId()));
            }
        }
    }
}
