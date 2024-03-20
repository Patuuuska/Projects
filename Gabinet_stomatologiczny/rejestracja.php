<?php
session_start();

if(isset($_POST['mail']))
{
//zakladamy ze dane sa poprawne
$ok=true;

//sprawdzamy poprawnosc imienia
$Name=$_POST['imie'];
$Sur=$_POST['nazwisko'];
$Age=$_POST['wiek'];
$Mail=$_POST['mail'];
$Pas1=$_POST['pass1'];
$Pas2=$_POST['pass2'];
$Pesel=$_POST['pesel'];

$success="";
//sprawdzamy dlugosc imienia
	if((strlen($Name)<2) || (strlen($Name)>20))
	{
		$ok=false;
		$_SESSION['E_Name']="Imie powinno posiadać od 3 do 20 znaków!";
	}
///sprawdzamy czy imie alfanumeryczne
	if(ctype_alnum($Name)==false)
	{
		$ok=false;
		$_SESSION['E_Name']="Imie powinno sie skladac tylko z liter i cyfr!";
	}


///sprawdzamy czy imie alfanumeryczne
	if(ctype_alnum($Sur)==false)
	{
		$ok=false;
		$_SESSION['E_Sur']="Nazwisko powinno sie skladac tylko z liter i cyfr!";
	}

//sprawdzamy dlugosc nazwiska
	if((strlen($Sur)<2) || (strlen($Sur)>20))
	{
		$ok=false;
		$_SESSION['E_Sur']="Nazwisko powinno posiadać od 3 do 20 znaków!";
	}

//sprawdzamy mail
	$mailb=filter_var($Mail,FILTER_SANITIZE_EMAIL);	
	if((filter_var($mailb,FILTER_VALIDATE_EMAIL)==false) || ($mailb!=$Mail))
	{
	$ok=false;
	$_SESSION['E_mail']="E-mail jest niepoprawny!";
	}
//sprawdzamy wiek
	if(is_numeric($Age)==false || $Age<=0 || $Age>=130)
	{
		$ok=false;
		$_SESSION['E_Age']="Podaj poprawny wiek!";
	}
	$Age=(int) $Age; //jezeli podamy wiek jako float zamieniamy na int

// sprawdzamy tylko czy podano ciagcyfr i ile cyfr	
	$Pesel=(int) $Pesel;
	if(is_numeric($Pesel)==false || strlen($Pesel)!=11)
	{
		$ok=false;
		$_SESSION['E_pesel']="Podaj poprawny Pesel!";
	}

//spraawdzamy hasla
	if((strlen($Pas1)<8) || (strlen($Pas2)>20)) //na ten monet nie sprawdamy znakow innych niz alfanumeryczne
	{
		$ok=false;
		$_SESSION['E_Pas']="Haslo powinno posiadać od 8 do 20 znaków!";
	}
	if($Pas1!=$Pas2)
	{
		$ok=false;
		$_SESSION['E_Pas']="Hasła nie są identyczne";
	}
	//echo $Pas1.'<br>';
	$haslo_hash=password_hash($Pas1,PASSWORD_DEFAULT);
	//echo $haslo_hash;// exit();

//checkbox
	if(!isset($_POST['Reg']))
	{
	$ok=false;
	$_SESSION['E_Reg']="Potwierdz regulamin";
	}
//zapamietanie danych formularza
$_SESSION['rem_name']=$Name;
$_SESSION['rem_sur']=$Sur;
$_SESSION['rem_age']=$Age;
$_SESSION['rem_mail']=$Mail;
$_SESSION['rem_pesel']=$Pesel;
$_SESSION['rem_pass1']=$Pas1;
$_SESSION['rem_pass2']=$Pas2;
if(isset($_POST['Reg']))
	$_SESSION['rem_reg']=true;


//laczymy sie z baza

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
		//czy mail istnieje juz w bazie
		$rez=$con->query("SELECT Id FROM customers WHERE Mail='$Mail'");

			if(!$rez) throw new Exception($con->error);

			$ile=$rez->num_rows;
			if($ile>0)
			{
			 $ok=false;
			 $_SESSION['E_mail']="Mail jest juz zajęty";
			}
		//jezeli spelnione wszystkie warunki
			if($ok==true)
			{
				if($con->query("INSERT INTO customers VALUES(NULL,'$Name $Sur','$Age','$haslo_hash','$Mail',NULL,'$Pesel')"))
				{
					
					$_SESSION['nowy_mail']=$Mail;
					echo "Rejestracja zakończyla się pomyślnie, dziękujemy.<br/><br/>";
					echo "Zaloguj się, aby aktywować konto";
					?>
					<a href="zaloguj_pacjent_layout.php"> <button type="button">Zaloguj na nowe konto</button> </a> </br>
					<?php
					exit();
				
				}
				else
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

}	

?>

<style>
.error
{
color:red;
margin-top:10px;
margin-left:10px;
}
</style> 

<!DOCTYPE html>
<html>
<head>
	<title>Rejestracja</title>

<link href="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-1BmE4kWBq78iYhFldvKuhfTAU6auU8tT94WrHftjDbrCEXSU1oBoqyl2QvZ6jIW3" crossorigin="anonymous">
<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/js/bootstrap.bundle.min.js" integrity="sha384-ka7Sk0Gln4gmtz2MlQnikT1wXgYsOg+OMhuP+IlRH9sENBO0LRn5q+8nbTov4+1p" crossorigin="anonymous"></script>

</head>

<body style="margin: 50px;">


<a href="index.php"> <button name="wroc">Wroc</button> </a> </br>

</br>

<h2>Witamy z systemie rejestracji </h2>
<form method="post">
<div class="row mb-2">
                                              <label class=" col-form-label">Imie:</label>
                                                     <div class="col-sm-2">
                                                         <input type="text" class="form-control" value="<?php
	if(isset($_SESSION['rem_name'])) //zapamietaie danych z poprzedniej proby wypelnienia formularza
	{
	echo $_SESSION['rem_name'];
	unset($_SESSION['rem_name']);
	}
	?>"
 	name="imie"/> 
	 </div>
                                          </div>
	<?php
	if(isset($_SESSION['E_Name']))
	{	
		echo '<div class="error">'.$_SESSION['E_Name'].'</div> <br>';
		unset($_SESSION['E_Name']);
	}
	?>

<div class="row mb-3">
                                              <label class=" col-form-label">Nazwisko:</label>
                                                     <div class="col-sm-2">
                                                         <input type="text" class="form-control" value="<?php
	if(isset($_SESSION['rem_sur'])) //zapamietaie danych z poprzedniej proby wypelnienia formularza
	{
	echo $_SESSION['rem_sur'];
	unset($_SESSION['rem_sur']);
	}
	?>"	
	name="nazwisko"/> 
	</div>
    </div>
	<?php
	if(isset($_SESSION['E_Sur']))
	{	
		echo '<div class="error">'.$_SESSION['E_Sur'].'</div> <br>';
		unset($_SESSION['E_Sur']);
	}
	?>	

											<div class="row mb-3">
                                              <label class=" col-form-label">E-mail:</label>
                                                     <div class="col-sm-2">
                                                         <input type="text" class="form-control" value="<?php
	if(isset($_SESSION['rem_mail'])) //zapamietaie danych z poprzedniej proby wypelnienia formularza
	{
	echo $_SESSION['rem_mail'];
	unset($_SESSION['rem_mail']);
	}
	?>"

	 name="mail"/> 
	 </div>
    </div>
	<?php
	if(isset($_SESSION['E_mail']))
	{	
		echo '<div class="error">'.$_SESSION['E_mail'].'</div> <br>';
		unset($_SESSION['E_mail']);
	}
	?>

<div class="row mb-3">
                                              <label class=" col-form-label">Wiek:</label>
                                                     <div class="col-sm-2">
                                                         <input type="text" class="form-control" value="<?php
        if(isset($_SESSION['rem_age']) && $Age!=0) //zapamietaie danych z poprzedniej proby wypelnienia formularza
	{
	echo $_SESSION['rem_age'];
	unset($_SESSION['rem_age']);
	}
	?>"
	name="wiek" /> 
 </div>
    </div>
	<?php
	if(isset($_SESSION['E_Age']))
	{	
		echo '<div class="error">'.$_SESSION['E_Age'].'</div> <br>';
		unset($_SESSION['E_Age']);
	}
	?>
	<div class="row mb-3">
                                              <label class=" col-form-label">Pesel:</label>
                                                     <div class="col-sm-2">
                                                         <input type="text" class="form-control" value="<?php
	if(isset($_SESSION['rem_pesel']) && $Pesel!=0) //zapamietaie danych z poprzedniej proby wypelnienia formularza
	{
	echo $_SESSION['rem_pesel'];
	unset($_SESSION['rem_pesel']);
	}
	?>"
	name="pesel"/> 
 </div>
    </div>
	<?php
	if(isset($_SESSION['E_pesel']))
	{	
		echo '<div class="error">'.$_SESSION['E_pesel'].'</div> <br>';
		unset($_SESSION['E_pesel']);
	}
	?>

<div class="row mb-3">
                                              <label class=" col-form-label">Hasło:</label>
                                                     <div class="col-sm-2">
                                                         <input type="password" class="form-control" name="pass1"/>  </div>
    </div>
	<?php
	if(isset($_SESSION['E_Pas']))
	{	
		echo '<div class="error">'.$_SESSION['E_Pas'].'</div> <br>';
		unset($_SESSION['E_Pas']);
	}
	?>

<div class="row mb-3">
                                              <label class=" col-form-label">Powtórz hasło:</label>
                                                     <div class="col-sm-2">
                                                         <input type="password" class="form-control" name="pass2"/>  </div>
    </div>
      
	<label>
		<input type="checkbox" class="btn btn-primary" name="Reg"/> Akceptuje <a href="regulamin.html" target="_blank">regulamin</a>
	<?php
	if(isset($_SESSION['rem_Reg']))
	{	
		echo '<div class="error">'.$_SESSION['E_Reg'].'</div> <br>';
		unset($_SESSION['E_Reg']);
	}
	?>
	</label>
	<?php
	if(isset($_SESSION['E_Reg']))
	{	
		echo '<div class="error">'.$_SESSION['E_Reg'].'</div> <br>';
		unset($_SESSION['E_Reg']);
	}
	?>
		<br/><br/>
	<input type="submit"class="btn btn-primary" value= "Zarejestruj jako pacjent"/>
  	<br/><br/>
</form>



</body>
</html> 
