package com.example.controller;
import com.example.model.ClassContainer;
import com.example.model.Employee;
import com.example.model.Group;
import com.example.model.Rating;
import com.example.service.EmployeeService;
import com.example.service.GroupService;
import com.example.service.RatingService;
import com.example.service.CsvGenerator;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import java.io.IOException;
import java.util.List;
@RestController
@RequestMapping("/api")
public class ApiController {

    private final EmployeeService employeeService;
    private final GroupService groupService;
    private final RatingService ratingService;
    private final CsvGenerator csvGenerator;
    @Autowired
    public ApiController(EmployeeService employeeService, GroupService groupService, RatingService ratingService, CsvGenerator csvGenerator) {
        this.employeeService = employeeService;
        this.groupService = groupService;
        this.ratingService = ratingService;
        this.csvGenerator = csvGenerator;
    }

    @GetMapping("/employee")
    public ResponseEntity<List<Employee>> getAllEmployees() {
        List<Employee> employees = employeeService.getAllEmployees();
        return ResponseEntity.ok(employees);
    }

    @GetMapping("/employee/{id}")
    public ResponseEntity<Employee> getEmployeeById(@PathVariable String id) {
        Employee employee = employeeService.getEmployeeById(id);
        if (employee != null) {
            return ResponseEntity.ok(employee);
        } else {
            return ResponseEntity.notFound().build();
        }
    }

    @PostMapping("/employee")
    public ResponseEntity<Void> addEmployee(@RequestBody Employee employee) {
        employeeService.addEmployee(employee);
        return new ResponseEntity<>(HttpStatus.CREATED);
    }

    @DeleteMapping("/employee/{id}")
    public ResponseEntity<Void> deleteEmployee(@PathVariable String id) {
        Employee employee = employeeService.getEmployeeById(id);
        if (employee != null) {
            employeeService.deleteEmployee(id);
            return new ResponseEntity<>(HttpStatus.NO_CONTENT);
        } else {
            return ResponseEntity.notFound().build();
        }
    }

    @GetMapping("/group")
    public ResponseEntity<List<Group>> getAllGroups() {
        List<Group> groups = groupService.getAllGroups();
        return ResponseEntity.ok(groups);
    }

    @PostMapping("/group")
    public ResponseEntity<Void> addGroup(@RequestBody Group group) {
        groupService.addGroup(group);
        return new ResponseEntity<>(HttpStatus.CREATED);
    }


    @DeleteMapping("/group/{id}")
    public ResponseEntity<Void> deleteGroup(@PathVariable String id) {
        Group group = groupService.getGroupById(id);
        if (group != null) {
            groupService.deleteGroup(id);
            return new ResponseEntity<>(HttpStatus.NO_CONTENT);
        } else {
            return ResponseEntity.notFound().build();
        }
    }

    @GetMapping("/group/{id}/employee")
    public ResponseEntity<List<Employee>> getEmployeesInGroup(@PathVariable String id) {
        List<Employee> employeesInGroup = groupService.getEmployeesInGroup(id);
        return ResponseEntity.ok(employeesInGroup);
    }
    @PostMapping("/group/{groupId}/employee")
    public ResponseEntity<Void> addEmployeeToGroup(@PathVariable String groupId, @RequestBody Employee employee) {
        groupService.addEmployeeToGroup(employee, groupId);
        return new ResponseEntity<>(HttpStatus.OK);
    }

    @GetMapping("/group/{id}/fill")
    public ResponseEntity<Double> getGroupFillPercentage(@PathVariable String id) {
        double fillPercentage = groupService.getGroupFillPercentage(id);
        return ResponseEntity.ok(fillPercentage);
    }

    @PostMapping("/rating")
    public ResponseEntity<Void> addRating(@RequestBody Rating rating) {
        ratingService.addRating(rating);
        return new ResponseEntity<>(HttpStatus.CREATED);
    }

    @GetMapping("/employee/csv")
    public ResponseEntity<?> generateCsv() {
        try {
            csvGenerator.generateCsv("employees.csv");
            return ResponseEntity.ok().build();
        } catch (IOException e) {
            return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).body("Błąd podczas generowania pliku CSV");
        }
    }

    @GetMapping("/rating/{groupId}")
    public ResponseEntity<Rating> getRatingByGroupId(@PathVariable String groupId) {
        Rating rating = ratingService.getRatingByGroupId(groupId);
        if (rating != null) {
            return ResponseEntity.ok(rating);
        } else {
            return ResponseEntity.notFound().build();
        }
    }

    @ExceptionHandler(Exception.class)
    public ResponseEntity<String> handleException(Exception e) {
        return ResponseEntity.status(HttpStatus.INTERNAL_SERVER_ERROR).body(e.getMessage());
    }
}
