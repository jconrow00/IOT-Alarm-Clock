<?php
//////   includes/formhandler.inc.php   //////


//if ($_SEVER["REQUEST_METHOD"] == "POST") {
	$username = $_POST["signupUsername"];
	$password = $_POST["signupPassword"];
	$name = $_POST["signupName"];
	$email = $_POST["signupEmail"];
	$clk_count = 0;	
	
	try {
		// Setsup PDO DB access	
		require_once "dbh_accounts.inc.php"; 

		// Checks if the entered name already is registered
		$chkquery = "SELECT COUNT(name) FROM users WHERE name=:chkname;";
		$chkstmt= $pdo->prepare($chkquery);
		$chkstmt->bindParam(":chkname", $name);
		$chkstmt->execute();
		if ($chkstmt->fetchColumn()){
			header("Location: ../name_has_acc.php");
			$chkstmt = null;	
			die();		
		}else{
		$chkstmt = null;
		}	
		
		
		// Checks if the entered username already is registered
		$chkquery = "SELECT COUNT(username) FROM users WHERE name=:chkusername;";
		$chkstmt= $pdo->prepare($chkquery);
		$chkstmt->bindParam(":chkusername", $username);
		$chkstmt->execute();
		if ($chkstmt->fetchColumn()){
			header("Location: ../username_has_acc.php");
			$chkstmt = null;	
			die();		
		}else{
		$chkstmt = null;
		}	


		// Weak check for valid email
		$pos1 = strpos($email, ".");
		$pos2 = strpos($email, "@");
		if ($pos1 === false OR $pos2 === false) { 
			header("Location: ../invalid_email.php");
			$pos1 = null;
			$pos2 = null;
			die();
		}else{
			$pos1 = null;
			$pos2 = null;
		}
		
		
		// Add information into the users table
		$query = "INSERT INTO users (username, password, name, email, clk_count) 
			VALUES (:username, :password, :name, :email, :clk_count);";
	        $stmt = $pdo->prepare($query);
		$stmt->bindParam(":username", $username);
		$stmt->bindParam(":password", $password);
		$stmt->bindParam(":name", $name);
		$stmt->bindParam(":email", $email);
		$stmt->bindParam(":clk_count", $clk_count);
		$stmt->execute(); 
		$pdo = null; 
		$stmt = null;
		header("Location: ../account_added.php");
		die(); 

	} catch (PDOException $e) {
	    die("Query Failed: " . $e->getMessage());
	
	}
//}
//else {
//	header("Location: ../index.php");
//	die();
//}



