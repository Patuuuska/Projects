package com.example.demo1;

import java.util.*;

public class ClassContainer {
    private String name;
    private Map<String, ClassEmployee> groups;

    public ClassContainer() {
        this.groups = new HashMap<>();
    }

    public ClassEmployee addClass(String groupName, int max) {
        if (groups.containsKey(groupName)) {
            System.out.println("Grupa już istnieje.");
            return groups.get(groupName);
        } else {
            ClassEmployee newClass = new ClassEmployee(groupName, max);
            groups.put(groupName, newClass);
            return newClass;
        }
    }

    public void removeClass(String nazwaGrupy) {
        if (groups.containsKey(nazwaGrupy)) {
            groups.remove(nazwaGrupy);
        } else {
            System.out.println("Grupa nie istnieje.");
        }
    }

    public List<String> findEmpty() {
        System.out.println("\nPusta grupa: ");
        List<String> emptyClass = new ArrayList<>();

        for (Map.Entry<String, ClassEmployee> value : groups.entrySet()) {
               ClassEmployee group = value.getValue();
             if (group.getListOfEmployee().isEmpty()) {
                emptyClass.add(value.getKey());
            }
        }
        return emptyClass;
    }

    public void summary() {
        System.out.println("\n**** PODSUMOWANIE STATYSTYCZNE WSZYSTKICH GRUP: ***");
        for(ClassEmployee group : groups.values()){
            double procent = ((double) group.getListOfEmployee().size() /group.getMaxNumberOfEmployee()) * 100;
            System.out.println("Nazwa grupy: " + group.getGroupName() + " i procentowe zapelnienie - " + procent + "%");

        }
    }

    public ClassEmployee findClassByName(String groupName) {
        for (ClassEmployee group : groups.values()) {
            if (group.getGroupName().equals(groupName)) {
                return group;
            }
        }
        return null;
    }


}