<?php
session_start();
if(!isset($_SESSION['zalogowany']))
{
header('location:index.php');
}
/////////sprawdzamy czy sa nieprzeczytane wiadomosci

require_once "conected.php";
	mysqli_report(MYSQLI_REPORT_STRICT);
	try
	{
		$con= new mysqli($servername,$username,$password,$database);
		if($con->connect_errno!=0)
		{
			throw new Exception(mysqli_connect_errno());
		}

		else
		{
     

	    $id=$_SESSION['id'];
		$rez=$con->query("SELECT *from powiadomienia_pacjent where pacjent_id='$id'AND status='nieprzeczytane' ");
		if(!$rez) throw new Exception($con->error);
		
		$ile=$rez->num_rows;
		
        }
			$con->close();

	}
		
	catch(Exception $e)
	{
		echo '<span style="color:red;">Blad serwera </span>';
		echo '<br/>'.$e;
	}
	$name = $_SESSION['Name'];
/////////
?>

<!DOCTYPE html>
<html>
<head>
	<title>System ubslugi pacjenta</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0-alpha1/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-GLhlTQ8iRABdZLl6O3oVMWSktQOp6b7In1Zl3/Jr59b6EGGoI1aFkw7cmDA6j6gD" crossorigin="anonymous">
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/js/bootstrap.bundle.min.js" integrity="sha384-ka7Sk0Gln4gmtz2MlQnikT1wXgYsOg+OMhuP+IlRH9sENBO0LRn5q+8nbTov4+1p" crossorigin="anonymous"></script>

</head>

<body>
<?php
unset($_SESSION['lekarze']);  //zmienna z umow
?>

<nav class="navbar bg-body-tertiary">
  <div class="container-fluid">
    <a class="navbar-brand">
    
      <img src="porady_grafika/logo.jpg" alt="Logo" width="240" height="110" class="d-inline-block align-text-top" href="main_pacjent.php">
     <h4><em>
      <?php
      echo"<h4> System Obsługi Gabinetu Stomatologicznego ";
        echo "</br><h2>Witaj ".$_SESSION['Name']." - Pacjent";
        ?> 
        </h4>
    </a>
  </div>
</nav>

<a href="powiadomienia_pacjent.php"> <button  id="block"><h4>Powiadomienia
<?php
if($ile>0)
    echo "(".$ile.") </h4>";
?>
</button> </a>  
<a href="kalendarz.php"> <button id="block2"><h4>Kalendarz</h4></button> </a>
<a href="aktualne_wizyty.php"> <button id="block2"><h4>Aktualne wizyty</h4></button> </a>
<a href="dane_pacjent.php"> <button id="block2"><h4>Aktualne dane</h4></button> </a>
<a href="umow.php"> <button id="block2"><h4>Umow wizyte</h4></button> </a>
<a href="logout.php"> <button id="block3"><h4>Wyloguj</h4></button> </a> </br>

</br>
</br>
<div id="carouselExampleDark" class="carousel carousel-dark slide">
  <div class="carousel-indicators">
    <button type="button" data-bs-target="#carouselExampleDark" data-bs-slide-to="0" class="active" aria-current="true" aria-label="Slide 1"></button>
    <button type="button" data-bs-target="#carouselExampleDark" data-bs-slide-to="1" aria-label="Slide 2"></button>
    <button type="button" data-bs-target="#carouselExampleDark" data-bs-slide-to="2" aria-label="Slide 3"></button>
  </div>
  <div class="carousel-inner">
  <div class="carousel-item active">
      <img src="porady_grafika/ortodoncja.jpg" class="d-block w-100" alt="...">
      <div class="carousel-caption d-none d-md-block">
        <h2>Ortodoncja</h2>
        <p><h4>Naszym Pacjentom oferujemy kompleksową opiekę stomatologiczną w zakresie ortodoncji oraz leczenia zachowawczego.</h4></p>
      </div>
    </div>
    <div class="carousel-item">
      <img src="porady_grafika/chlop1.jpg" class="d-block w-100" alt="...">
      <div class="carousel-caption d-none d-md-block">
        <h2>Stomatologia Estetyczna</h2>
        <p><h4>Naturalny, zdrowy i estetyczny wygląd zębów to misja naszej kliniki, którą realizujemy wobec wszystkich naszych Pacjentów.</h4></p>
      </div>
    </div>
    <div class="carousel-item">
      <img src="porady_grafika/idd.jpg" class="d-block w-100" alt="...">
      <div class="carousel-caption d-none d-md-block">
        <h2>Stomatologia dziecięca</h2>
        <p><h4>Nawiązujemy z dziećmi więź, tworzymy przyjazną atmosferę, leczymy pomagając unikać bólu.</h4></p>
      </div>
    </div>
  </div>
  <button class="carousel-control-prev" type="button" data-bs-target="#carouselExampleDark" data-bs-slide="prev">
    <span class="carousel-control-prev-icon" aria-hidden="true"></span>
    <span class="visually-hidden">Previous</span>
  </button>
  <button class="carousel-control-next" type="button" data-bs-target="#carouselExampleDark" data-bs-slide="next">
    <span class="carousel-control-next-icon" aria-hidden="true"></span>
    <span class="visually-hidden">Next</span>
  </button>
</div>


 
</body>
</html> 

<style>

A {
     text-decoration: none;}

    

#block, #block2, #block3
{
    display: block;
    border: none;
    color: white;
    padding: 16px 34px;
    font-size: 18px;
    cursor: pointer;
    text-align: center;
    float:left;
}

#block, #block2
{
    width: 18%; 
}

#block3
{
    width: 10%; 
}

#block
{
    <?php
    if($ile!=0)
        {?> 
        background-color: blue;
        <?php }
    else
        {?>
        background-color: grey;
        <?php }
    ?>
}

#block2, #block3
{
  background-color: grey;
}

#block:hover,#block2:hover,#block3:hover
{
  background-color: #ddd;
  color: black;
}



</style>