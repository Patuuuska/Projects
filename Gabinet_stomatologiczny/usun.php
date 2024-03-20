<?php
    if  (isset($_GET["ID"]))   {

    $ID = $_GET["ID"];

$servername = "localhost";
$database = "projekt";
$username = "root";
$password = "";


        $con= new mysqli($servername,$username,$password,$database);

        $sql = "DELETE FROM magazyn WHERE ID=$ID";
        $con->query($sql);

    }


    header("location: magazyn.php");
    exit;
?>