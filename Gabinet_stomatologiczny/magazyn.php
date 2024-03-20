<?php
session_start();
if(!isset($_SESSION['zalogowany2']))
{
header('location:index.php');
}
?>
<!DOCTYPE html>
<html>
<head>
    <title>Magazyn</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-1BmE4kWBq78iYhFldvKuhfTAU6auU8tT94WrHftjDbrCEXSU1oBoqyl2QvZ6jIW3" crossorigin="anonymous">
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/js/bootstrap.bundle.min.js" integrity="sha384-ka7Sk0Gln4gmtz2MlQnikT1wXgYsOg+OMhuP+IlRH9sENBO0LRn5q+8nbTov4+1p" crossorigin="anonymous"></script>

</head>

<body style="margin: 50px;">
<a href="main_dc.php"> <button name="wroc">Wroc</button> </a> </br>
<h1> Lista produktow w magazynie</h1>
<a class="btn btn-primary" href="/php1/nowy_produkt.php" role="button">Nowy produkt</a>
<br>
<table class="table">
         <thead>
             <tr>
                 <th>Nazwa</th>
                 <th>Ilosc</th>
                 <th>Funkcje</th>
             </tr>
         </thead>
         <tbody>
             <?php
require_once"conected.php"; //zalaczenie pliku z kodem
$con =new mysqli($servername, $username, $password, $database); //łączenie z baza danych 
		if($con->connect_errno)
		{
		   die("Connection failed: ". $con->connect_error); //blad 
		}
            	$sql = "SELECT * FROM magazyn"; //pobierz *-wszystko z bazy danych MAGAZYN
                $rez = $con->query($sql);
		if(!$rez)
         {
        die("Invalid query: ") . $con->error; //bład 
          }

        while($row = $rez->fetch_assoc())   {
            echo"<tr>
                 <td>" . $row["nazwa"] . "</td>  
                 <td>" . $row["ilosc"] . "</td>
                 <td>
                     <a class='btn btn-primary btn-sm' href='edytuj.php?ID=$row[ID]'>Edytuj</a>
                     <a class='btn btn-primary btn-sm' href='/php1/usun.php?ID=$row[ID]'>Usun</a>
                 </td>
             </tr>";
        }

             ?>
         </tbody>

</table>


  </body>
  </html>

