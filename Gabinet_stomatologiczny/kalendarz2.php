<?php
session_start();

$tab=NULL;  
$lekarze=NULL;
$godziny_all=NULL;
$godziny_wolne=NULL;
$godziny_zajete=NULL;

/// funkcje

function tablica(&$tablica,$rezultat) //zapelniamy tablice danymi
{
  $licz=0; 
			
		while($row = mysqli_fetch_assoc($rezultat)) 
		{
			 
			$tablica[$licz]=$row;
			$licz++;
			  
		}  
}

function ptablica(&$tablica) //zapelniamy tablice danymi
{
 for($i=0;$i<count($tablica);$i++)
    echo $tablica[$i]['Czas']."</br>";
echo '</br>';
}

function imie($tablica,$id) //
{
  $licz=0; 
		while($tablica[$licz]['ID']!=$id && $licz<count($tablica)) 
		{
			$licz++;
		}  
	return $tablica[$licz]['Name'];
}

function godziny_pracy(&$tablica,$start,$finish) //zapelniamy tablice danymi
{
  for($i=0;$i<$finish-$start;$i++)
  {
      
      $k=$i+$start;
      $k.=":00";
      $tablica[$i]=$k; // tworzymy godzine np 9:00
      $k="";
  }
}

function wypisz_godziny($tablica) //zapelniamy tablice danymi
{
  $godziny_kal="";
  for($i=0;$i<count($tablica);$i++)
  {
      $godziny_kal.=$tablica[$i];
      if($i%2==1)
         $godziny_kal.="</br>";
      else
         $godziny_kal.=" ";
         
  }
  return $godziny_kal;
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

function porownaj($tab2) //zapelniamy tablice danymi
{
  $k=0;
  $godzina="";
  $i=8;
  $j=0;
  while($i<16)
  {
      if($j<count($tab2))
      {
        $x=substr($tab2[$j]['Czas'], 0, -6); 
        
            if($i<$x)
            {
                $godzina.=$i.":00";
                
                if($k%2==0)
                    $godzina.=" ";
                else
                    $godzina.="</br>";
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
          $godzina.=$i.":00";
          
          if($k%2==0)
              $godzina.=" ";
          else
              $godzina.="</br>";
          $i++;
          $k++;
         
      }
      
  }
  return $godzina;
}

function todata($data,$rest) 
{
  $month = substr($rest, -2); 
  $year = substr($rest, 0, -5); 
  if($data<10)
    $dej="0".$data; 
  else
    $dej=$data;
  
  return $year."-".$month."-".$dej; 
}

////////////////////////funkcje


// baza danych
require_once "conected.php";
	
		$con= new mysqli($servername,$username,$password,$database);
		if($con->connect_errno!=0)
		{
			throw new Exception(mysqli_connect_errno());
		}

	
		if(isset($_POST['d2'])) //jezeli wybrano imie lekarza
		    $_SESSION['d2']=$_POST['lekarz_n'];
		    
		
        
            if(isset($_POST['lek']))
            {
               
                $id=$_POST['lek'];
               
                $_SESSION['lek_rem']=imie($lekarze,$_POST['lek']);
                $_SESSION['lek_rem2']=$id;
                
            }
            //jezeli mamy ustawionego lekarza i damy nastepnegy miesiac zmienia nam sie lekarz na pierwszego
            else if(isset($_SESSION['lek_rem2'])) 
            {
                $id=$_SESSION['lek_rem2'];
                $_SESSION['lek_rem']=imie($lekarze,$id);
            }

		    if(isset($_POST['lekarz_n']))
		    {
		        $_SESSION['lekarz_imie']=$_POST['lekarz_n'];
		    }
		    
		    $imie=$_SESSION['lekarz_imie'];
            
		    
		    $rezn=$con->query("SELECT * FROM lekarze WHERE Name='$imie'"); //szukamy id dla lekarza o danym imieniu i nazwisku
    		if(!$rezn) throw new Exception($con->error);  
    		
            $iles=$rezn->num_rows;
            tablica($lekarze,$rezn);
            $id=$lekarze[0]['ID'];
		    

///////////////////////////////////////////////////////////////// harmonogram

       
	    
		$rez=$con->query("SELECT * FROM wizyty WHERE Lekarz_id='$id' order by Data,Czas");  //harmonogram 
		if(!$rez) throw new Exception($con->error);
		
		$ile=$rez->num_rows;
		$licz=0; 
			
			while($row = mysqli_fetch_assoc($rez))
			{
			   $tab[$licz]=$row;
			   $licz++;
			}
	
		
            $con->close();
		
	



godziny_pracy($godziny_all,8,16);
wypisz_godziny($godziny_all);


//////////////////////////////////////////////////////////////////////////// formula kalendarza

//funkcja

// Set your timezone
date_default_timezone_set('Europe/Warsaw');

// Get prev & next month
if (isset($_GET['ym']))
{
    $ym = $_GET['ym'];
} else {
    // This month
    $ym = date('Y-m');
}

// Check format
$timestamp = strtotime($ym . '-01');
if ($timestamp === false)
{
    $ym = date('Y-m');
    $timestamp = strtotime($ym . '-01');
}
//echo $timestamp."</br>";
// Today
$today = date('Y-m-d', time());
//echo $today."</br>";
//echo $tab[0];
// For H3 title
$html_title = date('Y / m', $timestamp);

// Create prev & next month link     mktime(hour,minute,second,month,day,year)
$prev = date('Y-m', mktime(0, 0, 0, date('m', $timestamp)-1, 1, date('Y', $timestamp)));
$next = date('Y-m', mktime(0, 0, 0, date('m', $timestamp)+1, 1, date('Y', $timestamp)));
// You can also use strtotime!
// $prev = date('Y-m', strtotime('-1 month', $timestamp));
// $next = date('Y-m', strtotime('+1 month', $timestamp));

// Number of days in the month
$day_count = date('t', $timestamp);
 
// 0:Sun 1:Mon 2:Tue ...
$str = date('w', mktime(0, 0, 0, date('m', $timestamp), 0, date('Y', $timestamp)));
//$str = date('w', $timestamp);


// Create Calendar!!
$weeks = array();
$week = '';

// Add empty cell
$week .= str_repeat('<td></td>', $str);

for ( $day = 1; $day <= $day_count; $day++, $str++)
{
    $dzisiaj="";
     
    if($day<10)
        $date = $ym . '-' ."0".$day;
    else
        $date = $ym . '-' . $day;

     
    $pom=0;
    $pom2=$ile;
 
//////////przegladamy po kolei dni kalendarza i patrzymy ile jest przypisanych wizyt do danego dnia dla danego lekarza

     require_once "conected.php";
     mysqli_report(MYSQLI_REPORT_STRICT);
     try
        {
        	$con= new mysqli($servername,$username,$password,$database);
        	if($con->connect_errno!=0)
    			throw new Exception(mysqli_connect_errno());
    		else
    		{   
    		    $godziny_zajete=NULL;
            	$rezul=$con->query("SELECT * FROM wizyty WHERE Lekarz_id='$id' AND Data='$date' ORDER BY Czas ");  //harmonogram lekarza
        		if(!$rezul) throw new Exception($con->error);
        		
            	$ilosc=$rezul->num_rows;
                if($ilosc>0)
                    tablica($godziny_zajete,$rezul);
                
            	$con->close();
            	}
        	}
        	catch(Exception $e)
        	{
        		echo '<span style="color:red;">Blad serwera </span>';
        		echo '<br/>'.$e;
        	}
 
if($today< $date)
{
//// rozne rodzaje terminow: wolne, czesciowo wolne lub zajete   
   
    if($ilosc==0 && $str % 7!= 6)
    {
       $day_pom=todata($day,$html_title);
       $week .= '<td class=" bg-success">'.'<a class="text-dark" href="umow2.php?d='.$day_pom.'">'.$day.'</a>'."<br>".wypisz_godziny($godziny_all); 
       $pom=1;
    }
    else if($ilosc>0 && $ilosc<8)
    {
     $day_pom=todata($day,$html_title);
     $week .='<td class="bg-info">'.'<a class="text-dark" href="umow2.php?d='.$day_pom.'">'.$day.'</a>'."</br>".porownaj($godziny_zajete);
     $pom=1;
    }
}   

 
    if ($today == $date && $pom==0) //zlapanie dzisiejszej daty
    {
        
        $week .='<td class="bg-warning">'. $day."</br> "."Dzis"; 
        
    } 
   
    else 
    {
        if($pom==0)
        {
            $week .='<td>' . $day;
        }
    }
    
    $week .= '</td>';
     
    // End of the week OR End of the month
    if ($str % 7 == 6 || $day == $day_count) 
    {

        if ($day == $day_count) {
            // Add empty cell
            $week .= str_repeat('<td></td>', 6 - ($str % 7));
        }

        $weeks[] = '<tr>' . $week . '</tr>';

        // Prepare for new week
        $week = '';
    }

}
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="utf-8">
    <title>Kalendarz</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-1BmE4kWBq78iYhFldvKuhfTAU6auU8tT94WrHftjDbrCEXSU1oBoqyl2QvZ6jIW3" crossorigin="anonymous">
    <div style="margin: 50px;">
     
<a href="umow.php"> <button name="wroc">Powrót</button> </a> 
     
<form method="post">     
 
  <?php
  
  if(isset($_SESSION['Spec']))
  {
        $_SESSION['lekarz_imie']=$lekarze[0]['Name'];
      
        if(isset($_SESSION['lek_rem']))
        {
        $_SESSION['lekarz_imie']=$_SESSION['lek_rem'];
        ?> <option value ="<?php  $_SESSION['lek_rem2']?>"> <?php  $_SESSION['lek_rem'];
        unset($_SESSION['lek_rem']);
        }
        
        for($i=0;$i<$iles;$i++)
        { 
            if(isset($_SESSION['lek_rem2']) && $lekarze[$i]['ID']!=$_SESSION['lek_rem2'])
            {
            ?>
             <option value ="<?php  $lekarze[$i]['ID'];?>">
             <?php   $lekarze[$i]['Name'];
            }
            else if(!isset($_POST['lek']) && !isset($_SESSION['lek_rem2']))
            {
            ?>
             <option value ="<?php  $lekarze[$i]['ID'];?>">
             <?php  $lekarze[$i]['Name'];
            }
            
        }  
  }
  else if(isset($_SESSION['d2']))
  {
        ?> <option value ="<?php  $id?>"> <?php $lekarze[0]['Name'];
        $_SESSION['lekarz_imie']=$lekarze[0]['Name'];
        $_SESSION['lekarz_id']=$lekarze[0]['ID'];

  }
    ?>
    </option>  
	</select>
 
  <?php
  if(isset($_SESSION['Spec']) && count($lekarze)>1)
  
  ?>
 
  
 </form>    
   
</head>
<body>
    <div class="container">
        <h3><a href="?ym=<?php echo $prev; ?>">&lt;</a> <?php echo $html_title; ?> <a href="?ym=<?php echo $next; ?>">&gt;</a></h3>
        <table class="table table-bordered">
            <tr>
                
                <th>Poniedziałek</th>
                <th>Wtorek</th>
                <th>Środa</th>
                <th>Czwartek</th>
                <th>Piątek</th>
                <th>Sobota</th>
                <th>Niedziela</th>
            </tr>
            <?php
                foreach ($weeks as $week) 
                {
                    echo $week;
                }
            ?>
        </table>
    </div>
</body>
</html>

 <style>
        .container
        {
            font-family: 'Noto Sans', sans-serif;
            margin-top: 20px;
            
        }
        h3
        {
            margin-bottom: 30px;
        }
        th
        {
            height: 30px;
            text-align: center;
        }
        td
        {
            height: 100px;
            width:150px;
        }
       
        th:nth-of-type(7), td:nth-of-type(7) 
        {
            color: red;
        }
        th:nth-of-type(6), td:nth-of-type(6) 
        {
            color: blue;
        }
    </style>