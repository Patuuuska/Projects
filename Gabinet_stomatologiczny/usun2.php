<?php
    if  (isset($_GET["id"]))   {

    $id = $_GET["id"];

$servername = "localhost";
$database = "projekt";
$username = "root";
$password = "";


        $con= new mysqli($servername,$username,$password,$database);

        $sql = "DELETE FROM wizyty WHERE id=$id";
        $con->query($sql);

    }

    header("location: aktualne_wizyty.php");
    exit;
?>
