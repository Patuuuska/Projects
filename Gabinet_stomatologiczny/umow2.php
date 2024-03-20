<?php
session_start();

$tab=NULL;  
$godziny_all=NULL;
$godziny_wolne=NULL;
$godziny_zajete=NULL;
$inna_wizyta;
$today = date('Y-m-d');
//echo $today;

$d=substr($_GET['d'],-2);
$d =(int)$d;
$m=substr(substr($_GET['d'],0,-3),-2);
$m =(int)$m;
$y=substr($_GET['d'],-0,-6);
$y =(int)$y;
$ok=checkdate($m,$d,$y);

////pobieramy id przez get
if(isset($_GET['d']) && $today<$_GET['d'] && isset($_SESSION['lekarz_imie']) && $ok==1)
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
		$dat= $_GET['d'];
		$id=$_SESSION['lekarz_id'];
	
         $con->close();
		}
	}

	catch(Exception $e)
	{
		echo '<span style="color:red;">Blad serwera </span>';
		echo '<br/>'.$e;
	}
    
    
	$data = $_GET['d'];
	unset($_GET['value']);
}
else
{
header('Location:zaloguj_pacjent_layout.php');
exit();
}

function tablica(&$tablica,$rezultat) //zapelniamy tablice danymi
{
        $licz=0; 
			
		while($row = mysqli_fetch_assoc($rezultat)) //specjalizacje
		{
			$tablica[$licz]=$row;
			$licz++;
			  
		}  
}

function ptablica(&$tablica) //pokaz tablice
{
 for($i=0;$i<count($tablica);$i++)
    echo $tablica[$i]['Czas']."</br>";
echo '</br>';
}

function godziny_pracy(&$tablica,$start,$finish) //zapelniamy tablice danymi
{
  for($i=0;$i<$finish-$start;$i++)
  {
      if($start+$i<10)
        $k="0";
      else
        $k="";
      $k.=$i+$start;
      $k.=":00";
      $tablica[$i]=$k; // tworzymy godzine np 9:00
      //echo $k."</br>";
      
  }
}

function wypisz_godziny2($tablica) //zapelniamy tablice danymi
{
  $godziny_kal="";
  for($i=0;$i<count($tablica);$i++)
  {
      $godziny_kal.=$tablica[$i]['Czas'];
      if($i%2==1)
         $godziny_kal.="</br>";
      else
         $godziny_kal.=" ";
         
  }
  return $godziny_kal;
}

function porownaj($tab2,&$wynik) //zapelniamy tablice danymi
{
  $k=0;
  $i=8;
  $j=0;
  
  while($i<16)
  {
     // echo $i." ".$x." ".$j."</br>";
      if($tab2==NULL)
      {
        $wynik[$k]=$i.":00";
        $i++;
        $k++;
      }
      else if($j<count($tab2))
      {
        $x=substr($tab2[$j]['Czas'], 0, -6); 
        
            if($i<$x)
            {
                $godzina=$i.":00";
                $wynik[$k]=$godzina;
                
                $k++;
                $i++;
            }
            else
            {
                $j++;
                $i++;
            }
      }
      else
      {
          $godzina=$i.":00";
          $wynik[$k]=$godzina;

          $i++;
          $k++;
         
      }
      
  }
}

function inna($wizyta,$tab)
{
    $oks=1;
    for($i=0;$i<count($tab);$i++)
    {
        if($tab[$i]==$wizyta)
            $oks=0;
    }
    return $oks;
}
/// funkcje

godziny_pracy($godziny_all,8,16);

// baza danych
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
		$id=$_SESSION['lekarz_id'];
		//imie stoamtologa
		$rez0=$con->query("SELECT * FROM lekarze WHERE ID='$id'"); 
		if(!$rez0) throw new Exception($con->error);
		
		$wiersz=$rez0->fetch_assoc();
		$imie=$wiersz['Name'];
		

		$rez=$con->query("SELECT * FROM wizyty WHERE Lekarz_id='$id' AND Data='$data' order by Czas");  //harmonogram stomatologa
		if(!$rez) throw new Exception($con->error);
		
		$ile=$rez->num_rows;
		
		if($ile>=8)
		    header('Location:zaloguj_pacjent_layout.php');
		if($ile!=0)
		    tablica($tab,$rez);
		
         $con->close();
		}
	}

	catch(Exception $e)
	{
		echo '<span style="color:red;">Blad serwera </span>';
		echo '<br/>'.$e;
	}

porownaj($tab,$godziny_wolne);

$pom=0;

if(isset($_POST['godziny']))
{
    	//sprawdzamy czy pacjent nie ma innej wizyty o tej godzinie
    	
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
        $t=$_POST['godziny'].":00";
        $t0=substr($t,0,-6);
        if($t0<10)
            $t="0".$t;
        $id2=$_SESSION['id'];
        //echo $t."</br>";
       // echo $id2."</br>";
        //echo $data."</br>";
		$rez2=$con->query("SELECT * FROM wizyty WHERE Pacjent_id='$id2' AND Data='$data' AND Czas='$t' order by Czas");  
		if(!$rez2) throw new Exception($con->error);
		
		$ile2=$rez2->num_rows;
		//echo $ile2;
		
		if($ile2==1)
		{
		    tablica($inna_wizyta,$rez2);
		}
     
           $con->close();
		}
	}

	catch(Exception $e)
	{
		echo '<span style="color:red;">Blad serwera </span>';
		echo '<br/>'.$e;
	}
     
     ///////////////////////////////////////
        if($ile2==1)
        {
            //echo "</br>".$t." ".$inna_wizyta[0]['Czas']."</br>";
            if($t==$inna_wizyta[0]['Czas'])
            {
                $pom=1;
            }
        }
        if($pom==0)
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
                    
                	$czas=$_POST['godziny'];
                	$pacjent=$_SESSION['Name'];
                	
    				if($con->query("INSERT INTO wizyty VALUES(NULL, '$data', '$czas', '$id2', '$id')"))
    				{	
    				    //customer staje sie pacjentem
    				    if($con->query("INSERT INTO pacjenci VALUES(NULL, '$id2', '$id')"))
    				    {
    					//generujemy powiadomienie o dokonaniu wizyty
    					$wys=date("Y-m-d H:i:s");
    					$tresc="Umowiono na wizyte"."\r".
    					'Data: '.$data."\r".
    					"Czas: ".$czas."\r";
    					
    					$tresc1=$tresc."Lekarz: ".$imie;
                        $tresc2=$tresc."Pacjent: ".$pacjent;
    					
    					//echo $wys."</br>";
    					//echo $tresc."</br>";
    					if($con->query("INSERT INTO powiadomienia_pacjent VAlUES
    					(NULL, '$tresc1','$id2','$id','$wys','nieprzeczytane','NOWA WIZYTA')"))
    					{
    					    //powiadomienie dla lekarza
    					    if($con->query("INSERT INTO powiadomienia_lekarze VAlUES(NULL, '$tresc2','$id2','$id','$wys','nieprzeczytane','NOWA WIZYTA')")){}
    					    else
    					        throw new Exception($con->error);

    					}
    					else
    				    	throw new Exception($con->error);
    					
    					header('Location:main_pacjent.php');
    				    }
    				    else
    				    	throw new Exception($con->error);
    				}
    				else
    					throw new Exception($con->error);

			        $con->close();
        		}
	        }

        	catch(Exception $e)
        	{
        		echo '<span style="color:red;">Blad serwera </span>';
        		echo '<br/>'.$e;
        	}
        }
     
}


?>



<!DOCTYPE html>
<html lang="pl">
<head>
    <meta charset="utf-8">
    <title>Kalendarz</title>
	<link href="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-1BmE4kWBq78iYhFldvKuhfTAU6auU8tT94WrHftjDbrCEXSU1oBoqyl2QvZ6jIW3" crossorigin="anonymous">
         <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/js/bootstrap.bundle.min.js" integrity="sha384-ka7Sk0Gln4gmtz2MlQnikT1wXgYsOg+OMhuP+IlRH9sENBO0LRn5q+8nbTov4+1p" crossorigin="anonymous"></script>
		 </head> 
<body style="margin: 50px;">
    
     <a href="kalendarz2.php"> <button > Powrót </button> </a> </br> </br>
     
     
<form method="post">   
    <?php 
echo "Imie i nazwisko specjalisty:     ";
	echo $_SESSION['lekarz_imie']."</br>";

   echo "Wybrana data wizyty:        "; 
    echo $data."</br></br>";
    ?>
    
<td> 
<div class="row mb-3">
                                              <label class="col-sm-2 col-form-label">Dostępne godziny:</label>
                                                     <div class="col-sm-1">
													 <select class="form-control" name="godziny">                                                      </div>
                                          </div>
										  </div>


  <?php
  
        for($i=0;$i<count($godziny_wolne);$i++)
        { 
         
            ?>
             <option value ="<?php echo $godziny_wolne[$i];?>">
            <?php  echo $godziny_wolne[$i];
        }  
    ?>
    </option>  
	</select>
</td> 
  </br>
  <input type="submit" class="btn btn-primary" name="umow" value="Umów wizyte"> 
 </form>    


  
</body>
</html>

<?php
if($pom==1)
    echo '</br><span style="color:red;">Masz juz wizyte z innym lekarzem</span>';
?>

       
