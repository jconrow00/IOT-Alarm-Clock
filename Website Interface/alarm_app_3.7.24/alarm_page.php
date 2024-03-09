<!DOCTYPE html>

<?php 
     require_once "includes/process_login.inc.php";

?>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Alarm Interface</title>
    <link rel="stylesheet" href="css/style.css">
    <style>
        .container {
            text-align: center;
        }

        .tabs {
            display: flex;
            justify-content: center;
            margin-bottom: 20px;
        }

        .tabs button {
            padding: 10px;
            cursor: pointer;
            border: none;
            background-color: #4CAF50;
            color: white;
            margin: 0 10px;
        }

        .tabs button:hover {
            background-color: #45a049;
        }

        .tab-content {
            display: none;
        }
	.clocks-list, .alarms-list {
	    list-style: none;
	    padding: 0;
	    display: inline-block; 
	    text-align: left; 
	    margin-top: 0px; 
	    margin-bottom: 0px; 
	}

    </style>
</head>
<body>

    <div class="container">
        <h1>Alarm Configuration</h1>
	<h2><?php echo "Welcome \"{$username}\"!"; ?></h2>
		
		<form class="right">
	        <h3> Current Time:</h3>
	        <div id="currentTime" ></div> 	

			<h3>Associated Clocks:</h3>
			<ul class="clocks-list">
		    	<?php 
					$i = 0;
					$idx = 1;
					foreach($clk_arr as $c){
						echo "<li>Clock {$idx} - (ID{$c})</li>"; 
						echo "<ol class=\"no-numbers\">";
						echo "<li style=color:#333>TIME - EN:</li>";
						// lists the clock's alarms indented
						for($j = 0; $j < count($alarm_arr[$i][0]); $j++){
							echo "<li>{$alarm_arr[$i][0][$j]} - {$alarm_arr[$i][1][$j]} </li>";
						}	
						echo "</ol>";
						$i++;
						$idx++;
					}
		     	?>
			</ul>

	    </form>
		
		<form class="fake">
	    </form>
		
		<form action="includes/process_goback.inc.php" method="post">
			<button type="go_back">Logout</button>
		</form>

		<form action="includes/addclockhandler.inc.php" method="post">
			<label for="ddClockID">Add Clock ID:</label>
			<input type="number" name="addClockID" placeholder="XXXXXXXX" maxlength=8 required>
			<button type="add_clock">Add Clock</button>
	    </form>

		<form action="includes/addalarmhandler.inc.php" method="post" id="alarmForm">
			<h3 style=padding-left:5px>Add Alarm:</h3>
				<label for="clockSelect">Select a Clock:</label>
				<select id="clockSelect" name="clockSelect" required>
					<?php
						$i = 1;
						foreach($clk_arr as $a){
							echo "<option value=\"{$a}\">Clock {$i} - (ID{$a})</option>";
							$i++;
						}	
					?>
				</select>

				<label for="alarmTime">Set Alarm Time:</label>
				<input type="time" id="alarmTime" name="alarmTime">
				
				<label for="resetToggle" class="container">Reset Toggle
				<input type="checkbox" id="resetToggle" name="resetToggle">
				<span class="checkmark"></span>
				</label>

				<button id="add-alarm-time">Set Alarm</button>
		</form>

		</div>
    </div>

    <script>
	document.getElementById('currentTime').value = getCurrentTime();
	function updateCurrentTime() { 
	    const currentTimeElement = document.getElementById('currentTime');
    	    setInterval(() => {
		const now = new Date();
    	const hours = now.getHours().toString().padStart(2, '0');
		const minutes = now.getMinutes().toString().padStart(2, '0');		
		const seconds = now.getSeconds().toString().padStart(2, '0');		
		currentTimeElement.textContent = `${hours}:${minutes}:${seconds} PST`;
	    }, 1000);
	}

        function getCurrentTime	() {
            var now = new Date();
            var hours = now.getHours();
            var minutes = now.getMinutes();
            var timeString = hours + ':' + (minutes < 10 ? '0' : '') + minutes;
            return timeString;
        }


	// // Add event listener for "Set Alarm" button
	// document.getElementById('add-alarm-time').addEventListener('click', function() {
	// 	const selectedAlarmTime = document.getElementById('alarmTime').value;
	// 	if (selectedAlarmTime){	
	// 		alert(`Alarm added for ${selectedAlarmTime}`);
	// 	} else {
	// 		alert(`No alarm selected`)
	// 	}
	// });

        function setAlarm() {
            alert('Alarm set successfully!');
        }

        function openTab(tabName) {
            var i;
            var tabContent = document.getElementsByClassName('tab-content');
            for (i = 0; i < tabContent.length; i++) {
                tabContent[i].style.display = 'none';
            }

            document.getElementById(tabName).style.display = 'block';
        }

	// Call the updateCurrentTime function when the page loads
	window.onload = updateCurrentTime;
    </script>

</body>
</html>

