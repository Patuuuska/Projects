<!DOCTYPE html>
<html lang="en">
<head>
    <title>Kartoteka</title>
    <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-1BmE4kWBq78iYhFldvKuhfTAU6auU8tT94WrHftjDbrCEXSU1oBoqyl2QvZ6jIW3" crossorigin="anonymous">

    
</head>

<body style="margin: 50px;">
<a href="main_dc.php"> <button name="wroc">Wroc</button> </a> </br>
<h2> Kartoteki pacjentow Gabinetu Stomatologicznego</h2>
<a class="btn btn-primary" href="nowy_pacjent.php" role="button">Nowy pacjent</a>
<br>
<table class="table">
         <thead>
             <tr>
                 <th>Imie Nazwisko</th>
             </tr>
         </thead>
         <tbody>
             <?php
$servername = "localhost";
$username = "root";
$password = "";
$database = "projekt";


        $con= new mysqli($servername,$username,$password,$database);
        if($con->connect_error)
        {
           die("Connection failed: ". $con->connect_error);
        }

            	$sql = "SELECT * FROM customers";
                $rez = $con->query($sql);
        if(!$rez)
         {
        die(("Invalid query: ") . $con->error);
          }

        while($row = $rez->fetch_assoc())   {
            echo"
            <tr>
                 <td>$row[Name]</td>
                 <td>
                 <a class='btn btn-primary btn-sm' href='/php1/kartoteka_pacjent.php?Id=$row[Id]'>Podglad</a>
                 </td>
             </tr>
             ";
        }

             ?>
         </tbody>

</table>


  </body>
  </html>

