<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Signup</title>
    <link rel="stylesheet" href="css/style.css">
</head>
<body>
    <div class="login-container">
	    <form action="includes/formhandler.inc.php" method="post" >
		<h2>Signup</h2>

		<input type="text" name="signupUsername" placeholder="Username" required>
		<input type="password" name="signupPassword" placeholder="Password" required>
		<input type="text" name="signupName" placeholder="Name" required>
		<input type="text" name="signupEmail" placeholder="E-Mail" required>

		<button type="submit" id="signupButton">Signup</button>
	    </form>
	    <form action="includes/process_goback.inc.php" method="post">
		<button type="go_back">Go Back to Login</button>	
	    </form>
    </div>
    <script>

    </script>

</body>

 </html>
