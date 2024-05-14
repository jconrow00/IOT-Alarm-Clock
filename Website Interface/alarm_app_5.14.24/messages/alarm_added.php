<!DOCTYPE html>
<html land="en">
<head>
	<meta charset="UTF-8">
	<meta name="viewport" content="width=device-width, initial-scale=1.0">
	<title>Alarm Has Been Added</title>
	<link rel="stylesheet" href="../css/style.css">
</head>
<body>

	<h1>Alarm Has Been Added</h1>

	<script>
		function sleep(ms){
			return new Promise(resolve => setTimeout(resolve, ms));
		}

		sleep(2500).then(() => {window.location.replace("../alarm_page.php"); });

	</script> 
</body>

</html>
