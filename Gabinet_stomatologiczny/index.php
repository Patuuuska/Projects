<?php
session_start();
if((isset($_SESSION['zalogowany'])) && ($_SESSION['zalogowany']==true))
{
header('Location:main_pacjent.php');
exit();
}
if((isset($_SESSION['zalogowany2'])) && ($_SESSION['zalogowany2']==true))
{
header('Location:main_dc.php');
exit;
}

$tab=NULL;

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
   

        $today = date("Y-m-d");                   // np 2001-03-10 (the MySQL DATETIME format)
    	if($con->query("DELETE FROM wizyty WHERE Data<'$today'"))
		{}
		else
		{
		   	throw new Exception($con->error);
	    }
			
            $con->close();
		}
	}

	catch(Exception $e)
	{
		echo '<span style="color:red;">Blad serwera </span>';
		echo '<br/>'.$e;
	}

?>

<style>
.wybor
{
  float:left;
  text-align:center;
}

.div1
{
  margin:auto;
  width:950px;
  height:400px;

}



</style>

<!DOCTYPE html>
<html>
<head>

	<title>Gabinet Stomatologiczny </title>
	<link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-1BmE4kWBq78iYhFldvKuhfTAU6auU8tT94WrHftjDbrCEXSU1oBoqyl2QvZ6jIW3" crossorigin="anonymous">
         <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/js/bootstrap.bundle.min.js" integrity="sha384-ka7Sk0Gln4gmtz2MlQnikT1wXgYsOg+OMhuP+IlRH9sENBO0LRn5q+8nbTov4+1p" crossorigin="anonymous"></script>
		
</head>

<body style="margin: 50px;">
<img src="porady_grafika/logo.jpg" class="rounded float-start" alt="..."></br>
<em><h1><div class="text-primary text-center">................Witamy w Systemie Gabinetu Stomatologicznego............................................
</div></h1></em>



<div class="div1">
	<div class="wybor">
	</br>
	<h3>JESTEM PACJENTEM</h3> </br>
  	<a href="zaloguj_pacjent_layout.php"> <img src="porady_grafika/klienten.png"
		onmouseover="this.src='porady_grafika/klienten1.jpg.png'"
		onmouseout="this.src='porady_grafika/klienten.png'" width="450" height="400" /> </a>
	</div>	

    	<div class="wybor">
		</br>
	<h3>JESTEM STOMATOLOGIEM</h3> </br>
	<a href="zaloguj_doctor_layout.php"> <img src="porady_grafika/dentistin.jpg"
		onmouseover="this.src='porady_grafika/dentistin1.jpg'"
		onmouseout="this.src='porady_grafika/dentistin.jpg'" width="400" height="400" /> </a>
		
	</div>
</div>
</br>
<div class="card-body">
	<form action="">
		<div class="input-group form-group">
		<div class="input-group-prepend">
			<span class="input-group-text">
<svg xmlns="http://www.w3.org/2000/svg" width="45" height="45" fill="currentColor" class="bi bi-telephone" viewBox="0 0 16 16">
  <path d="M3.654 1.328a.678.678 0 0 0-1.015-.063L1.605 2.3c-.483.484-.661 1.169-.45 1.77a17.568 17.568 0 0 0 4.168 6.608 17.569 17.569 0 0 0 6.608 4.168c.601.211 1.286.033 1.77-.45l1.034-1.034a.678.678 0 0 0-.063-1.015l-2.307-1.794a.678.678 0 0 0-.58-.122l-2.19.547a1.745 1.745 0 0 1-1.657-.459L5.482 8.062a1.745 1.745 0 0 1-.46-1.657l.548-2.19a.678.678 0 0 0-.122-.58L3.654 1.328zM1.884.511a1.745 1.745 0 0 1 2.612.163L6.29 2.98c.329.423.445.974.315 1.494l-.547 2.19a.678.678 0 0 0 .178.643l2.457 2.457a.678.678 0 0 0 .644.178l2.189-.547a1.745 1.745 0 0 1 1.494.315l2.306 1.794c.829.645.905 1.87.163 2.611l-1.034 1.034c-.74.74-1.846 1.065-2.877.702a18.634 18.634 0 0 1-7.01-4.42 18.634 18.634 0 0 1-4.42-7.009c-.362-1.03-.037-2.137.703-2.877L1.885.511z"/>
</svg>
</span>
</div>
<div class="p-3 bg-primary bg-opacity-10 border border-primary border-start-3 rounded-end">
     +48 123-123-123
</div>
</div>

<div class="input-group form-group">
		<div class="input-group-prepend">
			<span class="input-group-text">

			<svg xmlns="http://www.w3.org/2000/svg" width="45" height="45" fill="currentColor" class="bi bi-house" viewBox="0 0 16 16">
  <path d="M8.707 1.5a1 1 0 0 0-1.414 0L.646 8.146a.5.5 0 0 0 .708.708L2 8.207V13.5A1.5 1.5 0 0 0 3.5 15h9a1.5 1.5 0 0 0 1.5-1.5V8.207l.646.647a.5.5 0 0 0 .708-.708L13 5.793V2.5a.5.5 0 0 0-.5-.5h-1a.5.5 0 0 0-.5.5v1.293L8.707 1.5ZM13 7.207V13.5a.5.5 0 0 1-.5.5h-9a.5.5 0 0 1-.5-.5V7.207l5-5 5 5Z"/>
</svg>
</span>
</div>

<div class="p-3 bg-primary bg-opacity-10 border border-primary border-start-3 rounded-end ">
 Ul. Malborska 34, Kraków
</div>
</form>                                           
</body>
</html> 
