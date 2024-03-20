<?php
$servername = "localhost";
$database = "projekt";
$username = "root";
$password = "";


		$con= new mysqli($servername,$username,$password,$database);

$ID ="";
$nazwa = "";
$ilosc = "";


$errorMessage = "";
$successMessage = "";
if ( $_SERVER['REQUEST_METHOD'] == 'GET'){

if (!isset($_GET["ID"])) {
    header("location: magazyn.php");
    exit;
}
$ID = $_GET["ID"];
$sql = "SELECT * FROM magazyn WHERE ID=$ID";
       $rez = $con->query($sql);
       $row = $rez->fetch_assoc();

       if (!$row) {
    header("location: magazyn.php");
    exit;

}
      $nazwa = $row["nazwa"];
      $ilosc = $row["ilosc"];
 }
    else {
     $ID = $_POST["ID"];
      $nazwa = $_POST["nazwa"];
      $ilosc = $_POST["ilosc"];

      
      

      do{ 
          if (( empty($ID)|| empty($nazwa) || empty($ilosc)) || (is_numeric($ilosc)==false || $ilosc < 0 ||  $ilosc >1000))  {
            $errorMessage = "Podaj wszystkie poprawne dane";
            break;
          
        }
        
          
        
           $sql = "UPDATE magazyn " .
           "SET nazwa = '$nazwa', ilosc = '$ilosc' " .
              "WHERE ID = $ID";

              $rez = $con->query($sql);
                  if (!$rez) {
                      $errorMessage = "Invalid query: " . $con->error;
                      break;
                  }

                  $successMessage = "Zmodyfikowano przedmiot poprawnie";

                       header("location: magazyn.php");
    exit;
    } while (false);
      }
?>
<!DOCTYPE html>
<html>
<head>
    <title>Magazyn</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-1BmE4kWBq78iYhFldvKuhfTAU6auU8tT94WrHftjDbrCEXSU1oBoqyl2QvZ6jIW3" crossorigin="anonymous">
         <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/js/bootstrap.bundle.min.js" integrity="sha384-ka7Sk0Gln4gmtz2MlQnikT1wXgYsOg+OMhuP+IlRH9sENBO0LRn5q+8nbTov4+1p" crossorigin="anonymous"></script>
</head>

<body>
   <div class="container my-5" >
                    <h2>Edytuj produkt</h2>
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
                        <input type="hidden" name="ID" value="<?php echo $ID; ?>">
                                          <div class="row mb-3">
                                              <label class="col-sm-3 col-form-label">Nazwa:</label>
                                                     <div class="col-sm-6">
                                                         <input type="text" class="form-control" name="nazwa" value="<?php echo $nazwa; ?>">
                                                     </div>
                                          </div>
                                          <div class="row mb-3">
                                              <label class="col-sm-3 col-form-label">Ilosc:</label>
                                                     <div class="col-sm-6">
                                                         <input type="text" class="form-control" name="ilosc" value="<?php echo $ilosc; ?>">
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
                                                         <a class="btn btn-outline-primary" href="magazyn.php" role="button">Cancel</a>
                                                     </div>
                                          </div>
                    </form>

   </div>
   

</body>
</html>


