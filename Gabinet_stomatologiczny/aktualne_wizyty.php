<?php
session_start();
$id=$_SESSION['id'];
?>
<!DOCTYPE html>
<html>
<head>
    <title>Aktualne wizyty</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-1BmE4kWBq78iYhFldvKuhfTAU6auU8tT94WrHftjDbrCEXSU1oBoqyl2QvZ6jIW3" crossorigin="anonymous">

</head>

<body style="margin: 50px;">
<a href="main_pacjent.php"> <button name="wroc">Wroc</button> </a> </br>
<h1> Lista aktualnych wizyt</h1>
<br>
<table class="table">
         <thead>
             <tr>
                 <th>Data </th>
                 <th>Godzina</th>
                 <th>Stomatolog</th>
                 <th>Funkcje</th>
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
             		$sql="SELECT * FROM wizyty WHERE Pacjent_id='$id' ORDER BY Data, Czas";  //najblizsze wizyty dla danego pacjenta
                     $rez = $con->query($sql);
                     if(!$rez) throw new Exception($con->error);
		
                     $ile=$rez->num_rows;
                     $licz=0; 

                     while($row = $rez->fetch_assoc())  {
                        if ($row["Lekarz_id"] == "1") $name="Anna Kowalska";
                        else if  ($row["Lekarz_id"] == "2") $name = "Dorota Mak";
                        else $name = "Robert Polak";
                     
                        

                        $godzina=$row["Czas"];
                        $godzina=substr($godzina,0,-3);

                        echo"<tr>
                             <td>" . $row["Data"] . "</td>
                             <td>" . $godzina . "</td>
                             <td>" . $name ."</td>
                             <td>
                                 <a class='btn btn-primary btn-sm' href='modyfikuj3.php?id=$row[id]'>Modyfikuj</a>
                                 <a class='btn btn-primary btn-sm' href='usun2.php?id=$row[id]'>Usun</a>
                             </td>
                         </tr>";
                    
                     }
                   
             
                     
             ?>
         </tbody>

</table>

  </body>
  </html>

