<?php
session_start();
if(!isset($_SESSION['zalogowany']))
{
header('location:index.php');
}
?>
<!DOCTYPE html>
<html>
<head>
    <title>Aktualne dane</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-1BmE4kWBq78iYhFldvKuhfTAU6auU8tT94WrHftjDbrCEXSU1oBoqyl2QvZ6jIW3" crossorigin="anonymous">

</head>

<body style="margin: 50px;">
<a href="main_pacjent.php"> <button name="wroc">Wroc</button> </a> </br>
<h1>Aktualne dane</h1>
<table class="table">
         <thead>
             <tr>
                 <th>Imie Nazwisko</th>
                 <th>Wiek</th>
                 <th>Mail</th>
                 <th>Pesel</th>
             </tr>
         </thead>
         <tbody>
             <?php

require_once"conected.php"; //zalaczenie pliku z kodem
$con= new mysqli($servername,$username,$password,$database); //łączenie z baza danych
        if($con->connect_errno)
        {
           die("Connection failed: ". $con->connect_error);
        }

            	
               
                    $id=$_SESSION['id'];
                    $sql = "SELECT * FROM customers WHERE id=$id";
        
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
                 <td>
                 <a class='btn btn-primary btn-sm' href='modyfikuj2.php'>Modyfikuj dane</a>
                 </td>
             </tr>";
        }

             ?>
         </tbody>

</table>




  </body>
  </html>

