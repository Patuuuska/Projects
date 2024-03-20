import entities.Employee;
import entities.EmployeeCondition;
import entities.EmployeeGroup;
import jakarta.persistence.EntityManager;
import jakarta.persistence.EntityManagerFactory;
import org.hibernate.jpa.HibernatePersistenceProvider;
import persistence.CustomPersistenceUnitInfo;

import java.util.HashMap;
import java.util.List;
import java.util.Map;


public class Main {

    public static void main(String[] args) {
        String puName = "pu-name";

        Map<String, String> props = new HashMap<>();
        props.put("hibernate.show_sql", "true");
        props.put("hibernate.hbm2ddl.auto", "create");

        EntityManagerFactory emf = new HibernatePersistenceProvider()
                .createContainerEntityManagerFactory(new CustomPersistenceUnitInfo(puName), props);
        try (EntityManager em = emf.createEntityManager()) {
            em.getTransaction().begin();


            EmployeeGroup testerzy = new EmployeeGroup("Testerzy", 5);
            EmployeeGroup programisci = new EmployeeGroup("Programisci", 10);
            EmployeeGroup kierownik = new EmployeeGroup("Kierownik", 1);

            Employee employee1 = new Employee("Jan", "Nowak", EmployeeCondition.OBECNY, 2000, 17880.0);
            Employee employee2 = new Employee("Zosia", "Madej", EmployeeCondition.OBECNY, 1998, 1900.0);
            Employee employee3 = new Employee("Mateusz", "Walczak", EmployeeCondition.CHORY, 1990, 15000.0);
            Employee employee4 = new Employee("Tadeusz", "Kowal", EmployeeCondition.OBECNY, 1975, 13400.0);
            Employee employee5 = new Employee("Maja", "Borek", EmployeeCondition.DELEGACJA, 2001, 1940.0);
            Employee employee6 = new Employee("Ola", "Zachariasz", EmployeeCondition.NIEOBECNY, 1976, 20000.0);


            employee1.setEmployeeGroup(programisci);
            employee2.setEmployeeGroup(programisci);
            employee3.setEmployeeGroup(testerzy);
            employee4.setEmployeeGroup(testerzy);
            employee5.setEmployeeGroup(kierownik);
            employee6.setEmployeeGroup(testerzy);

            testerzy.setListOfEmployees(List.of(employee4, employee3, employee6));
            programisci.setListOfEmployees(List.of(employee1, employee2));
            kierownik.setListOfEmployees(List.of(employee5));

            em.persist(employee1);
            em.persist(employee2);
            em.persist(employee3);
            em.persist(employee4);
            em.persist(employee5);
            em.persist(employee6);
            em.persist(testerzy);
            em.persist(programisci);
            em.persist(kierownik);


            List<Employee> employees = em.createQuery("SELECT e FROM Employee e WHERE e.salary > 3000", Employee.class).getResultList();
            for (Employee employee : employees) {
                String name = employee.getname();
                String secondName = employee.getsecondName();
                System.out.println("Name: " + name + ", Second Name: " + secondName);
            }
            em.getTransaction().commit();
        }

    }
}