<!DOCTYPE html>
<html land="en">
<head>
	<meta charset="UTF-8">
	<meta name="viewport" content="width=device-width, initial-scale=1.0">
	<title>Email Taken/Registered</title>
	<link rel="stylesheet" href="../css/style.css">
</head>
<body>

	<h1>Email Taken/Registered</h1>

	<script>
		function sleep(ms){
			return new Promise(resolve => setTimeout(resolve, ms));
		}

		sleep(2500).then(() => {window.location.replace("../signup_page.php"); });

	</script> 
</body>

</html>
