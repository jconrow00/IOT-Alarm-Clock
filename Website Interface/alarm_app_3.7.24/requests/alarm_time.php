<?php
if(isset($_GET["id"]) && isset($_GET["alarm"])) {
   $clock_id = $_GET["id"]; 
   $alarm_indx = $_GET["alarm"] - 1;
   // echo "{$alarm_indx}"; //temp

   // Setsup PDO DB access	   
   require_once "../includes/dbh_accounts.inc.php"; 

   // Checks if the entered name already is registered
   $query = "SELECT * FROM alarms WHERE clock_id=:clock_id ORDER BY alarm_time;";
   $stmt = $pdo->prepare($query);
   $stmt->bindParam(":clock_id", $clock_id);
   $stmt->execute();
   $time = $stmt->fetchAll(PDO::FETCH_COLUMN, 0);
   echo "{$time[$alarm_indx]}";
   $stmt = null;
   
} else {
   echo "clock_id not properly set for HTTP request";
}
