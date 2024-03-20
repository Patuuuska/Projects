import java.util.*;

public class ClassContainer {
    public Map<String, ClassEmployee> groups;

    ClassContainer(){
        this.groups = new HashMap<>();// kolekcja przechowuje pary klucz-wartość
    }

    public void addClass(String nameOfGroups, int numberOfEmployee) {
        groups.put(nameOfGroups, new ClassEmployee(nameOfGroups,  numberOfEmployee));
    }

    public void removeClass(String nameOfGroups) {
        
        groups.remove(nameOfGroups);
    }

    public Map<String, ClassEmployee> getGroup(){//uzyskania dostępu do prywatnego pola groups
        return groups;
    }

    public List<ClassEmployee> findEmpty() {
        System.out.println("\nPusta grupa: ");
        List<ClassEmployee> emptyClass = new ArrayList<>();
        for (ClassEmployee value : groups.values()) {
            if(value.getListOfEmployee().isEmpty()){
                emptyClass.add(value);
            }
        }
        if(emptyClass.isEmpty()) {
            System.out.println("Brak pustej grupy");
    
        }
        return emptyClass;
    }

    public void summary() {
        System.out.println("\n**** PODSUMOWANIE STATYSTYCZNE WSZYSTKICH GRUP: ***");
        for(ClassEmployee group : groups.values()){
            double procent = ((double) group.getListOfEmployee().size() /group.getMax()) * 100;
            System.out.println("Nazwa grupy: " + group.getGroupName() + " i procentowe zapelnienie - " + procent + "%");
            
        }
    }
}

