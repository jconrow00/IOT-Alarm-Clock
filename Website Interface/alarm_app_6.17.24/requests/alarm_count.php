<?php
if(isset($_GET["id"])) {
   $clock_id = $_GET["id"]; 

   // Setsup PDO DB access	   
   require_once "../includes/dbh_accounts.inc.php"; 

   // Checks if the entered name already is registered
   $query = "SELECT COUNT(clock_id) FROM alarms WHERE clock_id=:clock_id;";
   $stmt= $pdo->prepare($query);
   $stmt->bindParam(":clock_id", $clock_id);
   $stmt->execute();
   echo "{$stmt->fetchColumn()}";
   $stmt = null;


} else {
   echo "clock_id not properly set for HTTP request";
}
