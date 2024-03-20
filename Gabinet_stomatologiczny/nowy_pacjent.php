<?php
session_start();

?>
<?php
$servername = "localhost";
$username = "root";
$password = "";
$database = "projekt";


		$con= new mysqli($servername,$username,$password,$database);

$Name = "";
$Age = "";
$Mail = "";
$Pesel = "";

$errorMessage = "";
$successMessage = "";

if ( $_SERVER['REQUEST_METHOD'] == 'POST') { //sprawdzamy czy dane zostaly wyslane metoda post
    $Name = $_POST["Name"];
    $Age = $_POST["Age"];
    $Mail = $_POST["Mail"];
    $Pesel = $_POST["Pesel"]; //inicjujemy zmienne danymi z formualazra

    do {
        if ( empty($Name) || empty($Age) || empty($Mail) || empty($Pesel) )   {
            $errorMessage = "Uzupelnij wszystkie pola";
            break;
        }
                  $sql = "INSERT INTO customers (Name, Age, Mail, Pesel) " .
                  "VALUES ( '$Name', '$Age', '$Mail', '$Pesel')";
                  $rez = $con->query($sql);
                  if (!$rez) {
                      $errorMessage = "Invalid query: " . $con->error;
                      break; //wychodzimy z petli
                  }

                  $Name = "";
                  $Age = "";
                  $Mail = "";
                  $Pesel = "";


        $successMessage = "Poprawnie dodano";
      header("location: kartoteka.php");
      exit;

    }   while (false); //petla wykonuje sie tylko raz
}

?>
<!DOCTYPE html>
<html>
<head>
	<title>Kartoteka</title>
    <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-1BmE4kWBq78iYhFldvKuhfTAU6auU8tT94WrHftjDbrCEXSU1oBoqyl2QvZ6jIW3" crossorigin="anonymous">
         <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/js/bootstrap.bundle.min.js" integrity="sha384-ka7Sk0Gln4gmtz2MlQnikT1wXgYsOg+OMhuP+IlRH9sENBO0LRn5q+8nbTov4+1p" crossorigin="anonymous"></script>
</head>

<body>
   <div class="container my-5" >
                    <h2>Nowy pacjent</h2>
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
                                                         <a class="btn btn-outline-primary" href="kartoteka.php" role="button">Anuluj</a>
                                                     </div>
                                          </div>
                    </form>

   </div>

</body>
</html>


