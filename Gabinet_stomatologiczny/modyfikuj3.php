<?php
$servername = "localhost";
$database = "projekt";
$username = "root";
$password = "";

		$con= new mysqli($servername,$username,$password,$database);


$id ="";
$Data = "";
$Czas = "";

$errorMessage = "";
$successMessage = "";
if ( $_SERVER['REQUEST_METHOD'] == 'GET'){

    if (!isset($_GET["id"])) {
        header("location: aktualne_wizyty.php");
        exit;
    }
    $id = $_GET["id"];
    $sql = "SELECT * FROM wizyty WHERE id=$id ORDER BY Data, Czas";
           $rez = $con->query($sql);
           $row = $rez->fetch_assoc();
    
           if (!$row) {
        header("location: aktualne_wizyty.php");
        exit;
    
    }
    $id = $row["id"];
    $Data = $row["Data"];
    $Czas=$row["Czas"];
    $Czas=substr($Czas,0,-3);
     }
        else {
         $id = $_POST["id"];
        $Data = $_POST["Data"];
        $Czas = $_POST["Czas"];
  do{
      if ( empty($Data) || empty($Czas))  {
        $errorMessage = "Uzupelnij wszystkie pola";
        break;
    }
       $sql = "UPDATE wizyty " .
       "SET Data = '$Data', Czas = '$Czas' " .
          "WHERE id = $id";

          $rez = $con->query($sql);
              if (!$rez) {
                  $errorMessage = "Invalid query: " . $con->error;
                  break;
              }

              $successMessage = "Zmodyfikowano dane poprawnie";

                   header("location: aktualne_wizyty.php");
exit;
} while (false);
    }
?>
?>
<!DOCTYPE html>
<html>
<head>
    <title>Modyfikacja wizyty</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-1BmE4kWBq78iYhFldvKuhfTAU6auU8tT94WrHftjDbrCEXSU1oBoqyl2QvZ6jIW3" crossorigin="anonymous">
         <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/js/bootstrap.bundle.min.js" integrity="sha384-ka7Sk0Gln4gmtz2MlQnikT1wXgYsOg+OMhuP+IlRH9sENBO0LRn5q+8nbTov4+1p" crossorigin="anonymous"></script>
</head>

<body>
                    <div class="container my-5" >
                    <h2>Modyfikuj wizyte</h2>
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
                        <input type="hidden" name="id" value="<?php echo $id; ?>">
                        <div class="row mb-3">
                                              <label class="col-sm-3 col-form-label">Data:</label>
                                                     <div class="col-sm-6">
                                                         <input type="text" class="form-control" name="Data" value="<?php echo $Data; ?>">
                                                     </div>
                                          </div>
                                          <div class="row mb-3">
                                              <label class="col-sm-3 col-form-label">Czas:</label>
                                                     <div class="col-sm-6">
                                                         <input type="text" class="form-control" name="Czas" value="<?php echo $Czas; ?>">
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
                                                         <a class="btn btn-outline-primary" href="aktualne_wizyty.php" role="button">Cancel</a>
                                                     </div>
                                          </div>
                    </form>

   </div>


</body>
</html>


