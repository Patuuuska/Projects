import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

public class ClassEmployee {
    private String groupName;
    private List<Employee> listOfEmployee;
    private int maxNumberOfEmployee;

    public ClassEmployee(String groupName, Integer maxNumberOfEmployee) {
        this.groupName = groupName;
        this.listOfEmployee = new ArrayList<>();
        this.maxNumberOfEmployee = maxNumberOfEmployee;
    }

    public List<Employee> getListOfEmployee() {
        return this.listOfEmployee;
    }

    public String getGroupName() {
        return groupName;
    }
    public int getMax(){
        return maxNumberOfEmployee;
    }
  
    
    public void addEmployee(Employee employee) {
        if (listOfEmployee.size() + 1 <= maxNumberOfEmployee) {
            if (listOfEmployee.stream().anyMatch(e -> e.getname().equals(employee.getname()) && e.getsecondName().equals(employee.getsecondName()))) {
                System.out.println("Pracownik o takim imieniu i nazwisku istnieje.");
            } else {
                listOfEmployee.add(employee);
            }
        } else {
            System.err.println("Za dużo pracowników w danej grupie.");
        }
    }
    

    public void addsalary(Employee Employee, double salary) {
        for (Employee oneEmployee : listOfEmployee) {
            if (oneEmployee.equals(Employee)) {
                Employee.setsalary(Employee.getsalary() + salary);
            }
        }
    }


    public void changeCondition(Employee Employee, EmployeeCondition employeeState) {
        for (Employee oneEmployee : listOfEmployee) {
            if (oneEmployee.equals(Employee)) {
                oneEmployee.setEmployeeState(employeeState);
            }
        }
    }


    public Employee search(String secondName) {
        for (Employee Employee : listOfEmployee) {
            if (Employee.getsecondName().compareTo(secondName) == 0) {
                return Employee;
            }
        }
        return null;
    }

    public List<Employee> searchPartial(String word) {
        List<Employee> allowList = new ArrayList<>();
        for (Employee Employee : listOfEmployee) {
            if (Employee.getsecondName().contains(word) || Employee.getname().contains(word)) {
                allowList.add(Employee);
            }
        }
        return allowList;
    }

    public int countByCondition(EmployeeCondition state) {
        int counter = 0;
        for (Employee Employee : listOfEmployee) {
            if (Employee.getemployeeCondition().equals(state)) {
                counter++;
            }
        }
        return counter ;
    }

    public void summary() {
        System.out.println("\n*** Grupa: ***");
        for (Employee Employee : listOfEmployee) {
            Employee.print();
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
                return Double.compare(Employee1.getsalary(), Employee2.getsalary());
            }
        });
        return sort;
    }

    
    Employee max(){
        Employee maxx = Collections.max(listOfEmployee, new Comparator<Employee>() {

        });
        return maxx;
    }
}

