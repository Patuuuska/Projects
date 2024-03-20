<?php
	session_start();
	if((isset($_SESSION['zalogowany2'])) && ($_SESSION['zalogowany2']==true))
	header('Location:main_dc.php');
?>

<!DOCTYPE html>
<html>
<head>
	<title>Logowanie</title>
	<link href="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-1BmE4kWBq78iYhFldvKuhfTAU6auU8tT94WrHftjDbrCEXSU1oBoqyl2QvZ6jIW3" crossorigin="anonymous">

</head>

<body style="margin: 50px;">


<a href="index.php"> <button name="Wroc">Wroc</button> </a> 
</br> </br>
<h2>Jestem stomatologiem </h2>
<form action="zaloguj_doctor.php" method="post">
<div class="row mb-3">
                                              <label class=" col-form-label">Login:</label>
                                                     <div class="col-sm-2">
                                                         <input type="text" class="form-control" name="login_doctor">
                                                     </div>
                                          </div>
										  <div class="row mb-3">
                                              <label class="col-form-label">Hasło:</label>
                                                     <div class="col-sm-2">
                                                         <input type="password" class="form-control" name="haslo_doctor">
                                                     </div>
                                          </div>
</br>

        <input type="submit"class="btn btn-primary" value= "Zaloguj sie jako stomatolog"/>
		
  	<br/><br/>
</form>


<?php
if(isset($_SESSION['blad']))
	echo $_SESSION['blad'];
?>





</body>
</html> 
