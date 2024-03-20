<?php
require_once"conected.php"; //zalaczenie pliku z kodem
$con= new mysqli($servername,$username,$password,$database); //łączenie z baza danych

$Id ="";
$Name = "";
$Age = "";
$Mail = "";
$Pesel = "";
$Opis = "";

$errorMessage = "";
$successMessage = "";

if ( $_SERVER['REQUEST_METHOD'] == 'GET'){  //w GET parametry przekazuje się za pomocą adresu URL
    //zmienne trafiają do odpowiednich tablic asocjacyjnych - $_get

if (!isset($_GET["Id"])) {
    header("location: kartoteka_pacjent.php"); 
    exit;
}
$Id = $_GET["Id"];
$sql = "SELECT * FROM customers WHERE Id=$Id"; //pobierz wszystko z bazy danych CUSTOMERS gdzie id jest równe ustawionemu id
       $rez = $con->query($sql);
       $row = $rez->fetch_assoc();

       if (!$row) {
    header("location: kartoteka_pacjent.php");
    exit;

}
$Id = $row["Id"];
$Name = $row["Name"];
$Age = $row["Age"];
$Mail = $row["Mail"];
$Pesel = $row["Pesel"];
$Opis = $row["Opis"];
 }
 //Metoda „POST” do przekazywania parametrów wykorzystuje nagłówek zapytania
    else {
     $Id = $_POST["Id"];
    $Name = $_POST["Name"];
    $Age = $_POST["Age"];
    $Mail = $_POST["Mail"];
    $Pesel = $_POST["Pesel"];
    $Opis = $_POST["Opis"];
      do{
          if ( empty($Id)|| empty($Name) || empty($Age)|| empty($Mail) || empty($Pesel) || empty($Opis))  {
            $errorMessage = "Uzupelnij wszystkie pola";
            break;
        }
           $sql = "UPDATE customers " .
           "SET Name = '$Name', Age = '$Age', Mail = '$Mail', Pesel ='$Pesel', Opis = '$Opis'  " .
              "WHERE Id = $Id";
//zaktualizowanie danych w bazie danych CUSTOMERS 
              $rez = $con->query($sql);
                  if (!$rez) {
                      $errorMessage = "Invalid query: " . $con->error;
                      break;
                  }

                  $successMessage = "Zmodyfikowano dane poprawnie";

                       header("location: kartoteka_pacjent.php");
    exit;
    } while (false);
}  
?>
<!DOCTYPE html>
<html>
<head>
    <title>Modyfikacja danych</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-1BmE4kWBq78iYhFldvKuhfTAU6auU8tT94WrHftjDbrCEXSU1oBoqyl2QvZ6jIW3" crossorigin="anonymous">
         <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/js/bootstrap.bundle.min.js" integrity="sha384-ka7Sk0Gln4gmtz2MlQnikT1wXgYsOg+OMhuP+IlRH9sENBO0LRn5q+8nbTov4+1p" crossorigin="anonymous"></script>
</head>

<body>
   <div class="container my-5" >
                    <h2>Modyfikuj dane</h2>
                    <?php
                    if ( !empty($errorMessage)){
                        echo"
                        <div class='alert alert-warning alert-dismissible fade show' role='alert'>
                        <strong>$errorMessage</strong>
                        <button type='button' class='btn-close' data-bs-dismiss='alert' aria-label='Close'></button>
                        </div>
                        ";
                    }
                    ?>
                    <form method="post">
                        <input type="hidden" name="Id" value="<?php echo $Id; ?>">
                        <div class="row mb-3">
                                              <label class="col-sm-3 col-form-label">Imie Nazwisko:</label>
                                                     <div class="col-sm-6">
                                                         <input type="text" class="form-control" name="Name" value="<?php echo $Name; ?>">
                                                     </div>
                                          </div>
                                          <div class="row mb-3">
                                              <label class="col-sm-3 col-form-label">Wiek:</label>
                                                     <div class="col-sm-6">
                                                         <input type="text" class="form-control" name="Age" value="<?php echo $Age; ?>">
                                                     </div>
                                          </div>
                                          <div class="row mb-3">
                                              <label class="col-sm-3 col-form-label">Mail:</label>
                                                     <div class="col-sm-6">
                                                         <input type="text" class="form-control" name="Mail" value="<?php echo $Mail; ?>">
                                                     </div>
                                          </div>
                                          <div class="row mb-3">
                                              <label class="col-sm-3 col-form-label">Pesel:</label>
                                                     <div class="col-sm-6">
                                                         <input type="text" class="form-control" name="Pesel" value="<?php echo $Pesel; ?>">
                                                     </div>
                                          </div>
                                          <div class="row mb-3">
                                              <label class="col-sm-3 col-form-label">Ostatnia Wizyta:</label>
                                                     <div class="col-sm-6">
                                                         <input type="text" class="form-control" name="Opis" value="<?php echo $Opis; ?>">
                                                     </div>
                                          </div>
                                          
                                          

                                           <?php
                                                if ( !empty($successMessage)){
                        echo"
                        <div class='row mb-3'>
                         <div class='offset-sm-3 col-sm-6'>
                        <div class='alert alert-success alert-dismissible fade show' role='alert'>
                        <strong>$successMessage</strong>
                        <button type='button' class='btn-close' data-bs-dismiss='alert' aria-label='Close'></button>
                        </div>
                        </div>
                        </div>
                        ";
                    }

                                           ?>

                                          <div class="row mb-3">
                                              <div class="offset-sm-3 col-sm-3 d-grid">
                                                  <button type="zatwierdz" class="btn btn-primary">Zatwierdz</button>
                                                   </div>
                                                  <div class="col-sm-3 d-grid">
                                                         <a class="btn btn-outline-primary" href="kartoteka_pacjent.php" role="button">Anuluj</a>
                                                     </div>
                                          </div>
                    </form>

   </div>

</body>
</html>
