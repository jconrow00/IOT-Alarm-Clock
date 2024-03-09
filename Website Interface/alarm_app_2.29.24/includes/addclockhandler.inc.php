<?php
//////   includes/addclockhandler.inc.php   //////
session_start();

//if ($_SEVER["REQUEST_METHOD"] == "POST") {
	$id = $_POST["addClockID"];
	$username = $_SESSION['username'];	
	try {
		// Setup PDO DB
		require_once "dbh_accounts.inc.php";

		// Checks if the entered ID already is registered
		$chkquery = "SELECT COUNT(id) FROM clocks WHERE id=:id;";
		$chkstmt= $pdo->prepare($chkquery);
		$chkstmt->bindParam(":id", $id);
		$chkstmt->execute();
		if ($chkstmt->fetchColumn()){
			header("Location: ../id_registered.php");
			$chkstmt = null;	
			die();		
		}else{
			$chkstmt = null;
		}	
		
		// Checks clocks table for the sum number of users' clocks
		$query = "SELECT COUNT(indx) FROM clocks WHERE owner=:username;";
		$sumstmt = $pdo->prepare($query);
		$sumstmt->bindParam(":username", $username);
		$sumstmt->execute();
			// implying a clock is being added	
		$clk_count = $sumstmt->fetchColumn() + 1; 	
		$indx = $clk_count;
		$sumstmt = null;

		// New entry into clock table
		$query = "INSERT INTO clocks (owner, indx, id) 
			VALUES (:owner, :indx, :id);";
		$newstmt = $pdo->prepare($query);
		$newstmt->bindParam(":owner", $username);
		$newstmt->bindParam(":indx", $indx);
		$newstmt->bindParam(":id", $id);
		$newstmt->execute(); 
		$newstmt = null;
		
		// Rewrites users table to be up to date	
		$query = "UPDATE users SET clk_count=:clk_count WHERE username=:username;";
		$upstmt = $pdo->prepare($query);
		$upstmt->bindParam(":clk_count", $clk_count);
		$upstmt->bindParam(":username", $username);
		$upstmt->execute();
		$upstmt = null;

		// forward to confirmation message	
		$pdo = null; 
		header("Location: ../clock_added.php");
		die(); 


	} catch (PDOException $e) {
	    die("Query Failed: " . $e->getMessage());
	
	}
	
//}
//else {
//	header("Location: ../index.php");
//	die();
//}



