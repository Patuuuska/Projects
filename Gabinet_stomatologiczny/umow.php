<?php
session_start();

$tab;
$tab2;
$tab3;
$_SESSION['lekarze'][]="";
$flaga=0;
////funkcje
function tablica(&$tablica,$rezultat,$pom) //zapelniamy tablece danymi
{
  $licz=0; 
			
		while($row = mysqli_fetch_assoc($rezultat))
		{
			 
			$tablica[$licz]=$row;
			//if($pom==1)   
			$licz++;
			  
		}  
}

////funkcje

if(!isset($_SESSION['zalogowany']))
{
header('location:index.php');
}


$id=$_SESSION['id'];
if(isset($_POST['d1']))
{
    $spec=$_POST['lekarz_s'];
}

require_once "conected.php";
	
		$con= new mysqli($servername,$username,$password,$database);
		if($con->connect_errno)
		{
		   die("Connection failed: ". $con->connect_error); //blad 
		}

		else
		{
		$rez2=$con->query("SELECT * FROM lekarze ORDER BY Name");
		if(!$rez2) throw new Exception($con->error);

		$ile2=$rez2->num_rows;

        tablica($tab2,$rez2,$flaga);
        
			$con->close();
		}
	

	
	/////////
?>
<!DOCTYPE html>
<html>
<head>
	<title>Umow wizyte</title>
	<link href="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-1BmE4kWBq78iYhFldvKuhfTAU6auU8tT94WrHftjDbrCEXSU1oBoqyl2QvZ6jIW3" crossorigin="anonymous">
         <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/js/bootstrap.bundle.min.js" integrity="sha384-ka7Sk0Gln4gmtz2MlQnikT1wXgYsOg+OMhuP+IlRH9sENBO0LRn5q+8nbTov4+1p" crossorigin="anonymous"></script>

</head>
<a href="main_pacjent.php"> <button > Powrót </button> </br> </br> </a>
<body style="margin: 50px;">

<form action="kalendarz2.php" method="post">  
</br>
  <h3>WYBIERZ SPECJALISTE:</h3> 

<td> 
	<div class="col-sm-2">
  <select class="form-control" name="lekarz_n"> 
</div>
  <?php
    for($i=0;$i<$ile2;$i++)
    { ?>
     <option  value ="<?php echo $tab2[$i]['Name']?>">
     <?php  echo $tab2[$i]['Name'];
    
    }  
    ?>
    </option>  
     
	</select>
  </td> 
  </br>
<input type="submit"  class="btn btn-primary"  name="d2" value="DALEJ">
</form> </br>


</body>
</html>
