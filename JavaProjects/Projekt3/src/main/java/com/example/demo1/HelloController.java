package com.example.demo1;

import javafx.beans.property.SimpleStringProperty;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.*;
import javafx.scene.input.MouseButton;
import javafx.scene.layout.VBox;
import javafx.scene.text.Text;

import java.net.URL;
import java.util.List;
import java.util.ResourceBundle;

import static com.example.demo1.EmployeeCondition.OBECNY;

public class HelloController implements Initializable {
    @FXML
    private ListView<String> grupyPracownicze;
    @FXML
    private TableView<Employee> pracownicyTableView = new TableView<>();
    @FXML
    private TableColumn<Employee, String> imieColumn = new TableColumn<>();
    @FXML
    private TableColumn<Employee, String> nazwiskoColumn = new TableColumn<>();
    @FXML
    private Button addGroupButton = new Button();
    @FXML
    private Button addEmployeeButton = new Button();
    @FXML
    private Button removeGroupButton = new Button();
    @FXML
    private Button removeEmployeeButton = new Button();
    @FXML
    private Button modifyEmployeeDataButton = new Button();
    @FXML
    private Button modifyGroupDataButton = new Button();
    @FXML
    private Button sortGroupByNameButton = new Button();
    @FXML
    private Text nameTextField = new Text();
    @FXML
    private Text lastNameTextField = new Text();

    @FXML
    private Text yearOfBirthTextField = new Text();
    @FXML
    private Text salaryTextField = new Text();
    @FXML
    private Text numberOfEmployeesTextField = new Text();

    @FXML
    private Text groupNameTextField = new Text();
    private Data data = new Data();

    @Override
    public void initialize(URL url, ResourceBundle resourceBundle) {
        pracownicyTableView.getColumns().clear();
        imieColumn.setCellValueFactory(cellData -> new SimpleStringProperty(cellData.getValue().getName()));
        nazwiskoColumn.setCellValueFactory(cellData -> new SimpleStringProperty(cellData.getValue().getSecondName()));
        pracownicyTableView.getColumns().addAll(imieColumn, nazwiskoColumn);

        removeGroupButton.setDisable(true);
        removeEmployeeButton.setDisable(true);

        for (ClassEmployee klasa : data.getGroups()) {
            grupyPracownicze.getItems().addAll((klasa.getGroupName()));
        }

        grupyPracownicze.getSelectionModel().selectedItemProperty().addListener((obs, oldSelection, newSelection) -> {
            if (newSelection != null) {
                String selectedName = grupyPracownicze.getSelectionModel().getSelectedItem();

                for (ClassEmployee klasa : data.getGroups()) {
                    if (klasa.getGroupName().equals(selectedName)) {
                        List<Employee> groupEmployee = klasa.getListOfEmployee();
                        pracownicyTableView.setItems((ObservableList<Employee>) groupEmployee);
                    }
                }
            }
        });
        pracownicyTableView.setOnMouseClicked(event -> {
            if (event.getButton() == MouseButton.PRIMARY && !pracownicyTableView.getSelectionModel().isEmpty()) {
                removeEmployeeButton.setDisable(false);
                Employee selectedEmployee = pracownicyTableView.getSelectionModel().getSelectedItem();
                nameTextField.setText(selectedEmployee.getName());
                lastNameTextField.setText(selectedEmployee.getSecondName());
                yearOfBirthTextField.setText(String.valueOf(selectedEmployee.getDateOfBirth()));
                salaryTextField.setText(String.valueOf(selectedEmployee.getSalary()));
            } else {
                removeEmployeeButton.setDisable(true);
            }
        });
        removeEmployeeButton.setOnAction(event -> {
            Employee selectedEmployees = pracownicyTableView.getSelectionModel().getSelectedItem();
            if (selectedEmployees != null) {
                data.getGroups().remove(selectedEmployees);
                pracownicyTableView.getItems().remove(selectedEmployees);
                removeEmployeeButton.setDisable(true);
            }
        });

        grupyPracownicze.setOnMouseClicked(event -> {
            if (event.getButton() == MouseButton.PRIMARY && !grupyPracownicze.getSelectionModel().isEmpty()) {
                removeGroupButton.setDisable(false);
                String selectedName = grupyPracownicze.getSelectionModel().getSelectedItem();
                for (ClassEmployee klasa : data.getGroups()) {
                    if (klasa.getGroupName().equals(selectedName)) {
                         groupNameTextField.setText(klasa.getGroupName());
                        numberOfEmployeesTextField.setText(String.valueOf(klasa.getPercentage())+'%');
                    }
                }
            } else {
                removeGroupButton.setDisable(true);
            }
        });

        removeGroupButton.setOnAction(event -> {
            String selectedGroupName = grupyPracownicze.getSelectionModel().getSelectedItem();
            if (selectedGroupName != null) {
                data.getGroups().removeIf(classEmployee -> classEmployee.getGroupName().equals(selectedGroupName));
                grupyPracownicze.getItems().remove(selectedGroupName);
                removeGroupButton.setDisable(true);
            }
        });
        modifyEmployeeDataButton.setOnAction(event -> {
            Employee selectedEmployee = pracownicyTableView.getSelectionModel().getSelectedItem();
            if (selectedEmployee != null) {
                DialogPane dialogPane = new DialogPane();
                dialogPane.setHeaderText("Edytuj dane pracownika:");

                TextField imieField = new TextField(selectedEmployee.getName());
                TextField nazwiskoField = new TextField(selectedEmployee.getSecondName());
                TextField rokUrodzeniaField = new TextField(String.valueOf(selectedEmployee.getDateOfBirth()));
                TextField zarobkiField = new TextField(String.valueOf(selectedEmployee.getSalary()));

                dialogPane.setContent(new VBox(
                        new Label("Imię:"),
                        imieField,
                        new Label("Nazwisko:"),
                        nazwiskoField,
                        new Label("Rok Urodzenia:"),
                        rokUrodzeniaField,
                        new Label("Pensja:"),
                        zarobkiField
                ));


                Dialog<String> dialog = new Dialog<>();
                dialog.setDialogPane(dialogPane);

                dialogPane.getButtonTypes().addAll(ButtonType.OK, ButtonType.CANCEL);

                dialog.setResultConverter(buttonType -> {
                    if (buttonType == ButtonType.OK) {
                        selectedEmployee.setName(imieField.getText());
                        selectedEmployee.setSecondName(nazwiskoField.getText());
                        selectedEmployee.setDateOfBirth(Integer.parseInt(rokUrodzeniaField.getText()));
                        selectedEmployee.setSalary(Double.parseDouble(zarobkiField.getText()));
                        pracownicyTableView.refresh();
                    }
                    return null;
                });

                dialog.showAndWait();
            }
        });
        addEmployeeButton.setOnAction(event -> {

            DialogPane dialogPane = new DialogPane();
            dialogPane.setHeaderText("Dodaj nowego pracownika:");

            TextField imieField = new TextField();
            TextField nazwiskoField = new TextField();
            TextField rokUrodzeniaField = new TextField();
            TextField zarobkiField = new TextField();

            dialogPane.setContent(new VBox(
                    new Label("Imię:"),
                    imieField,
                    new Label("Nazwisko:"),
                    nazwiskoField,
                    new Label("Rok Urodzenia:"),
                    rokUrodzeniaField,
                    new Label("Pensja:"),
                    zarobkiField
            ));

            Dialog<String> dialog = new Dialog<>();
            dialog.setDialogPane(dialogPane);

            dialogPane.getButtonTypes().addAll(ButtonType.OK, ButtonType.CANCEL);

            dialog.setResultConverter(buttonType -> {
                if (buttonType == ButtonType.OK) {
                    String imie = imieField.getText();
                    String nazwisko = nazwiskoField.getText();
                    int rokUrodzenia = Integer.parseInt(rokUrodzeniaField.getText());
                    double zarobki = Double.parseDouble(zarobkiField.getText());
                    EmployeeCondition stan = OBECNY;

                    Employee newEmployee = new Employee(imie, nazwisko, stan , rokUrodzenia, zarobki);
                    String selectedName = grupyPracownicze.getSelectionModel().getSelectedItem();
                    for (ClassEmployee klasa : data.getGroups()) {
                        if (klasa.getGroupName().equals(selectedName)) {
                            klasa.getListOfEmployee().add(newEmployee);
                        }
                    }
                    pracownicyTableView.refresh();
                }
                return null;
            });

            dialog.showAndWait();
        });

        addGroupButton.setOnAction(event -> {
            DialogPane dialogPane = new DialogPane();
            dialogPane.setHeaderText("Dodaj grupę pracowniczą:");

            TextField groupNameField = new TextField();
            TextField numberOfEmployeeField = new TextField();

            dialogPane.setContent(new VBox(
                    new Label("Nazwa grupy:"),
                    groupNameField,
                    new Label("Max ilosc pracownikow:"),
                    numberOfEmployeeField
            ));

            Dialog<String> dialog = new Dialog<>();
            dialog.setDialogPane(dialogPane);

            dialogPane.getButtonTypes().addAll(ButtonType.OK, ButtonType.CANCEL);

            dialog.setResultConverter(buttonType -> {
                if (buttonType == ButtonType.OK) {
                    String nazwaGrupy = groupNameField.getText();
                    int maxEmployee = Integer.parseInt(numberOfEmployeeField.getText());

                    ClassEmployee newGroup = new ClassEmployee(nazwaGrupy, maxEmployee);
                    data.getGroups().add(newGroup);

                    grupyPracownicze.getItems().add(nazwaGrupy);
                    pracownicyTableView.refresh();
                }
                return null;
            });

            dialog.showAndWait();
        });

        modifyGroupDataButton.setOnAction(event -> {
            DialogPane dialogPane = new DialogPane();
            dialogPane.setHeaderText("Edytuj grupę pracowniczą");
            String selectedName = grupyPracownicze.getSelectionModel().getSelectedItem();
            TextField nazwaGrupyField = new TextField();
            dialogPane.setContent(new VBox(
                    new Label("Nazwa grupy:"),
                    nazwaGrupyField
            ));

            Dialog<String> dialog = new Dialog<>();
            dialog.setDialogPane(dialogPane);

            dialogPane.getButtonTypes().addAll(ButtonType.OK, ButtonType.CANCEL);
            dialog.setResultConverter(buttonType -> {
                if (buttonType == ButtonType.OK) {
                   String nowaNazwaGrupy = nazwaGrupyField.getText();
                    System.out.println(nowaNazwaGrupy);

                    for (ClassEmployee klasa : data.getGroups()) {
                        if (klasa.getGroupName().equals(selectedName)) {
                            klasa.setGroupName(nowaNazwaGrupy);
                            groupNameTextField.setText(nowaNazwaGrupy);
                            System.out.println(klasa.getGroupName());
                            grupyPracownicze.refresh();
                            pracownicyTableView.refresh();
                        }
                    }
                    grupyPracownicze.getItems().clear();
                    for (ClassEmployee klasa : data.getGroups()) {
                        grupyPracownicze.getItems().addAll((klasa.getGroupName()));
                    }


                    for (ClassEmployee klasa : data.getGroups()) {
                        System.out.println(klasa.getGroupName());}
                }

                return null;
            });

            dialog.showAndWait();
        });
        sortGroupByNameButton.setOnAction(event -> {
            ObservableList<String> grupy = grupyPracownicze.getItems();

            grupy.sort(String::compareToIgnoreCase);

            grupyPracownicze.refresh();
        });

    }

}
