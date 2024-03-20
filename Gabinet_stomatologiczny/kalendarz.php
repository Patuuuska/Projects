<?php
session_start();
$id=$_SESSION['id'];

//laczenie z baza danych
$tab=NULL;  //jesli nie bedzie wizyt tablica domyslnie pusta
$tab2=NULL; //jesli nie bedzie wizyt tablica domyslnie pusta

require_once "conected.php";
		$con= new mysqli($servername,$username,$password,$database);
		if($con->connect_error)
        {
           die("Connection failed: ". $con->connect_error);
        }

		else
		{
		$rez=$con->query("SELECT * FROM wizyty WHERE Pacjent_id='$id' ORDER BY Data,Czas");  //najblizsze wizyty dla danego pacjenta
		if(!$rez) throw new Exception($con->error);
		
		$ile=$rez->num_rows;
		$licz=0; 
			
			while($row = mysqli_fetch_assoc($rez))
			{
			   $tab[$licz]=$row;
			   $licz++;
			}


			for($i=0; $i<$ile; $i++) //znajdujemy imie lekarza o danym id
		    {
    		    $iden=$tab[$i]['Lekarz_id'];
    		    $rez2=$con->query("SELECT * FROM lekarze WHERE ID='$iden'");
    		    if(!$rez2) throw new Exception($con->error);

    		    $row=mysqli_fetch_assoc($rez2);
    		    $tab2[$i]=$row;
	    	}
            $con->close();
		}

//formula kalendarza

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
// Today
$today = date('Y-m-d', time());

// For H3 title
$html_title = date('Y / m', $timestamp);

// Create prev & next month link     mktime(hour,minute,second,month,day,year)
$prev = date('Y-m', mktime(0, 0, 0, date('m', $timestamp)-1, 1, date('Y', $timestamp)));
$next = date('Y-m', mktime(0, 0, 0, date('m', $timestamp)+1, 1, date('Y', $timestamp)));

// Number of days in the month
$day_count = date('t', $timestamp);
 
// 0:Sun 1:Mon 2:Tue ...
$str = date('w', mktime(0, 0, 0, date('m', $timestamp), 0, date('Y', $timestamp)));



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
     

        $i=0;
        $pom=0;     
        $pom2=$ile;

    while($i<$pom2) //terminy aktualnych wizyt
    {
        if ($date == $tab[$i]['Data'] && $today<=$tab[$i]['Data']) //zlapanie dzisiejszej daty
        {
            $godzina=$tab[$i]['Czas'];
            $godzina=substr($godzina,0,-3);  //wycinamy sekundy
            $doktorek=$tab2[$i]['Name'];
            if($date!=$today) //jezeli dzis nie jest wizyta
            {
                if($i==0) //ostatni element tablicy
                {
                    $week .= '<td class="bg-success">' . $day."</br></br> ".$godzina." ".$doktorek;
                  
                    $pom=1;
                }
                else if($tab[$i]['Data']!=$tab[$i-1]['Data']) //reszta
                {
                    $week .= '<td class="bg-success">' . $day."</br></br> ".$godzina." ".$doktorek;
                }
                else
                {
                     $week .="</br>".$godzina." ".$doktorek;
                }
                $pom=1;
            }
            else //today=dzisiaj
            {
                $dzisiaj=$tab[$i]['Data'];
                if($i==0) //pierwszy element tablicy
                {
                     $week .= '<td class="bg-danger">' . $day."</br>dzis wizyta </br></br>".$godzina." ".$doktorek;
                }
                else if($tab[$i]['Data']!=$tab[$i-1]['Data']) //reszta
                {
                    $week .= '<td class="bg-danger">'. $day."</br>dzis wizyta </br></br>".$godzina." ".$doktorek;
                }
                else
                {
                     $week .="</br>".$godzina." ".$doktorek;
                }
                $pom=1;
                
            }
            
        } 
        
        $i++;
    }
    
    if ($today == $date && $pom==0) //zlapanie dzisiejszej daty
    { 
        
        $week .= '<td class="bg-warning">' . $day."</br> "."Dzis"; 
    } 
   
    else 
    {
        if($pom==0)
        $week .= '<td>' . $day;
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
     <a href="main_pacjent.php"> <button > Powrót </button> </a>
    <style>
        .container
        {
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
            width:100px;
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