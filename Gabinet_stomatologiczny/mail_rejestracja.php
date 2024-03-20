<?php

///mail jeszcze nie dziala
$to =$_SESSION['nowy_mail'];
$subject = "Witamy w gabinecie stomatologicznym";

$message = "Poprawnie zalozono konto";

if (mail($to,$subject,$message)){
    echo "Wiadomosc wyslana";
}

    else{
        echo "Niepowodzenie";
}
?>   				    	
