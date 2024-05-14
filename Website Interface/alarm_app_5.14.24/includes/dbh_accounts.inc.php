<?php
//////   includes/dbh.inc.php   //////


$dsn = "mysql:host=localhost;dbname=accounts"; 
$dbusername = "root";
$dbpassword = "123"; 

try {
     $pdo = new PDO($dsn, $dbusername, $dbpassword);  
     $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
} catch (PDOException $e) { 
     die("Connection Failed: " . $e->getMessage());
}

