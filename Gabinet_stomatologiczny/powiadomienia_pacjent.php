<?php
session_start();
$ok=0;
if(isset($_GET['i']))
{
	$ID = $_GET['i'];
	unset($_GET['i']);
	$ok=1;
}

$tab=NULL;
$tab0=NULL;
function tablica(&$tablica,$rezultat) //zapelniamy tablice danymi
{
  $licz=0; 
			
		while($row = mysqli_fetch_assoc($rezultat)) 
		{
			$tablica[$licz]=$row;
			$licz++;
			  
		}  
}

function wypisz_pow(&$tablica,$rozmiar) 
{
  for($i=0;$i<$rozmiar;$i++)
  {
      $iden=$tablica[$i]['ID'];
      if($tablica[$i]['status']=='nieprzeczytane')
      {
          ?>
          <a href="powiadomienia_pacjent.php?i=<?php echo $iden; ?>"> <button id="block">
          <?php echo $tablica[$i]['typ']."</br></br>Wyslano: ". $tablica[$i]['data_wyslania'];?>
          </button> </a>
          <?php
      }
      else
      {
           ?>
          <a href="powiadomienia_pacjent.php?i=<?php echo $iden; ?>"> <button id="block2">
          <?php echo $tablica[$i]['typ']."</br></br>Wyslano: ". $tablica[$i]['data_wyslania'];?>
          </button> </a>
          <?php
          
      }
      
  }
}

function find_ID(&$tablica,$rozmiar,$id)
{
  for($i=0;$i<$rozmiar;$i++)
  {
      if($tablica[$i]['ID']==$id)
      {
       return $i;
      }
  }
}



if(!isset($_SESSION['zalogowany']))
{
header('location:index.php');
}
// oznaczanie jako przeczytanie

if($ok==1)
{
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
	
		//przeczytane,nieprzeczytane
	   
		$rez2=$con->query("UPDATE powiadomienia_pacjent SET status='przeczytane' WHERE ID='$ID'");
		if(!$rez2) throw new Exception($con->error);
		
		$con->close();

		}
	}

	catch(Exception $e)
	{
		echo '<span style="color:red;">Blad serwera </span>';
		echo '<br/>'.$e;
	}
}

/// powiadomienia
require_once "conected.php";
	
		$con= new mysqli($servername,$username,$password,$database);
    if($con->connect_error)
    {
       die("Connection failed: ". $con->connect_error);
    }
		  
		//wszystkie wiadomosci
	    $id=$_SESSION['id'];
		$rez=$con->query("SELECT * FROM powiadomienia_pacjent WHERE pacjent_id='$id' ORDER BY data_wyslania DESC");
		if(!$rez) throw new Exception($con->error);
		
		$ile=$rez->num_rows;
        tablica($tab,$rez);

		$con->close();

		
?>	


<style>

A {text-decoration: none;
}


#block, #block2
{
    display: block;
    border: none;
    color:  black;
    padding: 14px 18px;
    font-size: 12px;
    cursor: pointer;
    text-align: center;
}

#block2
{
    width: 20%; 
    background-color: #aeb6bf;
}


#block
{
  background-color: grey;
  width: 20%; 
  float:right;
}

#block:hover,#block2:hover
{
  background-color: #ddd;
  color: black;
}
#pusty
{
  width: 80%; 
  float:right;
  height: 100%;
  background-color: #eaecee;
}
#text
{
  color:  black;
  padding: 14px 18px;
}
</style>


<!DOCTYPE html>
<html>
<head>
	<title>System ubslugi pacjenta</title>
  <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0-alpha1/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-GLhlTQ8iRABdZLl6O3oVMWSktQOp6b7In1Zl3/Jr59b6EGGoI1aFkw7cmDA6j6gD" crossorigin="anonymous">
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/js/bootstrap.bundle.min.js" integrity="sha384-ka7Sk0Gln4gmtz2MlQnikT1wXgYsOg+OMhuP+IlRH9sENBO0LRn5q+8nbTov4+1p" crossorigin="anonymous"></script>

</head>
<body style="margin: 50px;">
<a href="main_pacjent.php"> <button  type="button">Powrot </button> </a> </br></br>


<?php
/// tresc wiadomosci (przypadek na pierwsze wejscie)
if($ok==0)
{?>
    <div id="pusty">
        <div id="text">
        </div>
    </div>
<?php
}
else
{
  $index=find_ID($tab,$ile,$ID);    
?>
    <div id="pusty">
        <div id="text">
        <?php echo nl2br($tab[$index]['tresc']); ?>
        </div>
    </div>
<?php 
}

wypisz_pow($tab,$ile);
?>


</body>
</html> 

