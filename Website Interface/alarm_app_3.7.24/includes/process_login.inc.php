<?php
//////   includes/process_login.inc.php   //////
session_start();
// Check if the form is submitted
$clk_arr;
$alarm_arr;
$alarm_en;
if ($_SERVER["REQUEST_METHOD"] == "POST") {

    // Validate username and password 
    $username = $_POST["username"];
    $password = $_POST["password"];
    $_SESSION['username'] = $username;
    try {
	    require_once "dbh_accounts.inc.php";
	    $query = "SELECT * FROM users WHERE username=:username AND password=:password;"; 
	    $stmt = $pdo->prepare($query);
	    $stmt->bindParam(":username", $username);
	    $stmt->bindParam(":password", $password);
	    $stmt->execute();
	    if ($stmt->rowCount() === 0){
			$stmt = null;
			$query = "";
			header("Location: wrong_credentials.php");
			die();
	    } 
	    else{
			$stmt = null;
			$query = "";
	    } 
    } catch (PDOException $e){
		die("Query Failed: " . $e->getMessage());
    }

    // Now extract the users clocks to display
    $owner = $username;
    try {
	    $query = "SELECT * FROM clocks WHERE owner=:owner"; 
	    $stmt = $pdo->prepare($query);
	    $stmt->bindParam(":owner", $owner);
	    $stmt->execute();
	    $clk_arr = $stmt->fetchAll(PDO::FETCH_COLUMN, 2);
    } catch (PDOException $e){
		die("Query Failed: " . $e->getMessage());
    } 
	

	// Now extract the user's alarms for display 
    try {
			//loops through each clock id to extract clock's alarms and toggles
		$i = 0;
	    foreach($clk_arr as $id){
			// add array for times
			$query = "SELECT * FROM alarms WHERE clock_id=:clock_id ORDER BY alarm_time"; 
			$alarmstmt = $pdo->prepare($query);
			$alarmstmt->bindParam(":clock_id", $id);
			$alarmstmt->execute();
				// puts the alarm time and enable into the
				// associated array spot of each clock. 
				// thus, a 3D array
				// first column, is the asscoiated clock
				// second column, is the value (0=alarm_time, 1=enable_value)
				// third column is the alarm number itself.
			$alarm_arr[$i][0] = $alarmstmt->fetchAll(PDO::FETCH_COLUMN,0);
			// add array for toggles
			$query = "SELECT * FROM alarms WHERE clock_id=:clock_id ORDER BY alarm_time"; 
			$enstmt = $pdo->prepare($query);
			$enstmt->bindParam(":clock_id", $id);
			$enstmt->execute();
				// puts the alarm time and enable into the
				// associated array spot of each clock. 
				// thus, a 3D array
				// first column, is the asscoiated clock
				// second column, is the value (0=alarm_time, 1=enable_value)
				// third column is the alarm number itself.
			$alarm_arr[$i][1] = $enstmt->fetchAll(PDO::FETCH_COLUMN, 2);
			$i++;
		}
    } catch (PDOException $e){
		die("Query Failed: " . $e->getMessage());
    } 


} 

else {
    header("Location: index.php");   
    die();
}






/*
function alert($msg) {
	echo "<script type='text/javascript'>alert('$msg');</script>";
}
		    */

