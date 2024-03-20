

<!DOCTYPE html>
<html>
<head>
    <title>Kartoteka pacjenta</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-1BmE4kWBq78iYhFldvKuhfTAU6auU8tT94WrHftjDbrCEXSU1oBoqyl2QvZ6jIW3" crossorigin="anonymous">

</head>

<body style="margin: 50px;">
<a href="kartoteka.php"> <button name="wroc">Wroc</button> </a> </br>
<h1>Kartoteka pacjenta</h1>
<br>
<table class="table">
         <thead>
             <tr>
                 <th>Imie Nazwisko</th>
                 <th>Wiek</th>
                 <th>Mail</th>
                 <th>Pesel</th>
                 <th>Ostatnia wizyta</th>
             </tr>
         </thead>
         <tbody>
             <?php
$servername = "localhost";
$database = "projekt";
$username = "root";
$password = "";


        $con= new mysqli($servername,$username,$password,$database);
        if($con->connect_errno)
        {
           die("Connection failed: ". $con->connect_error);
        }

            	
                if ( $_SERVER['REQUEST_METHOD'] == 'GET'){

                    if (!isset($_GET["Id"])) {
                        header("location: kartoteka.php");
                        exit;
                    }
                    $Id = $_GET["Id"];
                    $sql = "SELECT * FROM customers WHERE Id=$Id";
        
                $rez = $con->query($sql);
        if(!$rez)
         {
        die("Invalid query: ") . $con->error;
          }

        while($row = $rez->fetch_assoc())   {
            echo"<tr>
                 <td>" . $row["Name"] . "</td>
                 <td>" . $row["Age"] . "</td>
                 <td>" . $row["Mail"] . "</td>
                 <td>" . $row["Pesel"] . "</td>
                 <td>" . $row["Opis"] ."</td>
                 <td>
                     <a class='btn btn-primary btn-sm' href='modyfikuj.php?Id=$row[Id]'>Modyfikuj dane</a>
                 </td>
             </tr>";
        }}

             ?>
         </tbody>

</table>


  </body>
  </html>
