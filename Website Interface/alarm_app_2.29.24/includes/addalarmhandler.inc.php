<?php
//////   includes/addalarmhandler.inc.php   //////
session_start();

//if ($_SEVER["REQUEST_METHOD"] == "POST") {
	$alarm_time = $_POST["alarmTime"];
    $clock_id = $_POST["clockSelect"];
	$username = $_SESSION['username'];	
    $snooze_en;
	if ($_POST["resetToggle"] === 'on') {
		$snooze_en = 1;
	} else {
		$snooze_en = 0;
	}
	try {
		// Setup PDO DB
		require_once "dbh_accounts.inc.php";

		// Checks if the entered Alarm already is registered
		$chkquery = "SELECT COUNT(clock_id) FROM alarms WHERE clock_id=:clock_id AND alarm_time=:alarm_time";
		$chkstmt= $pdo->prepare($chkquery);
		$chkstmt->bindParam(":clock_id", $clock_id);
		$chkstmt->bindParam(":alarm_time", $alarm_time);
		$chkstmt->execute();
		if ($chkstmt->fetchColumn()){
			header("Location: ../alarm_already_used.php");
			$chkstmt = null;	
			die();		
		}else{
			$chkstmt = null;
		}	

		// New entry into alarm table
		$query = "INSERT INTO alarms (alarm_time, clock_id, snooze_en) 
			VALUES (:alarm_time, :clock_id, :snooze_en);";
		$newstmt = $pdo->prepare($query);
		$newstmt->bindParam(":alarm_time", $alarm_time);
		$newstmt->bindParam(":clock_id", $clock_id);
		$newstmt->bindParam(":snooze_en", $snooze_en);
		$newstmt->execute(); 
		$newstmt = null;

		
		// forward to confirmation message	
		$pdo = null; 
		header("Location: ../alarm_added.php");
		die(); 


	} catch (PDOException $e) {
	    die("Query Failed: " . $e->getMessage());
	
	}
	
//}
//else {
//	header("Location: ../index.php");
//	die();
//}



