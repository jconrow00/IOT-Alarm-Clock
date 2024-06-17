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
		$chkname = $pdo->prepare($chkquery);
		$chkname->bindParam(":chkname", $name);
		$chkname->execute();
		if ($chkname->fetchColumn()){
			header("Location: ../messages/name_has_acc.php");
			$chkname = null;	
			die();		
		}else{
			$chkname = null;
		}		

		// Checks if the entered username already is registered
		$chkuserquery = "SELECT COUNT(username) FROM users WHERE username=:username;";
		$chkuser = $pdo->prepare($chkuserquery);
		$chkuser->bindParam(":username", $username);
		$chkuser->execute();
		if ($chkuser->fetchColumn()){
			header("Location: ../messages/username_has_acc.php");
			$chkuser = null;	
			die();		
		}else{
			$chkuser = null;
		}	

		// Checks if the entered email already is registered
		$chkemailquery = "SELECT COUNT(email) FROM users WHERE email=:email;";
		$chkemail = $pdo->prepare($chkemailquery);
		$chkemail->bindParam(":email", $email);
		$chkemail->execute();
		if ($chkemail->fetchColumn()){
			header("Location: ../messages/email_has_acc.php");
			$chkemail = null;	
			die();		
		}else{
			$chkemail = null;
		}	


		// Weak check for valid email
		$pos1 = strpos($email, ".");
		$pos2 = strpos($email, "@");
		if ($pos1 === false OR $pos2 === false) { 
			header("Location: ../messages/invalid_email.php");
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
		header("Location: ../messages/account_added.php");
		die(); 

	} catch (PDOException $e) {
	    die("Query Failed: " . $e->getMessage());
	
	}
//}
//else {
//	header("Location: ../index.php");
//	die();
//}



