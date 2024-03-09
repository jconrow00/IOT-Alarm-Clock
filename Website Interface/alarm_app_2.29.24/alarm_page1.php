<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Alarm Page</title>
    <link rel="stylesheet" href="css/style.css">
    <style>
        .alarm-container {
            text-align: center;
        }

        #current-time {
            font-size: 24px;
            margin-bottom: 20px;
        }

        .clocks-list, .alarms-list {
            list-style: none;
            padding: 0;
            display: inline-block;
            text-align: left;
            margin: 20px;
        }

        #disable-snooze-label {
            display: inline-block;
            margin-right: 10px;
        }

        #add-alarm-time {
            margin-top: 20px;
        }
    </style>
</head>
<body>
    <div class="alarm-container">
        <h1>Welcome to the Alarm Page</h1>
        
        <div id="current-time"></div>

        <h3>Available Clocks</h3>
        <ul class="clocks-list">
            <li>Clock 1</li>
            <li>Clock 2</li>
            <!-- Add more clocks as needed -->
        </ul>

        <h3>Associated Alarms</h3>
        <ul class="alarms-list">
            <li>Alarm 1 - 08:00 AM</li>
            <li>Alarm 2 - 12:30 PM</li>
            <!-- Add more alarms as needed -->
        </ul>

        <div>
            <label id="disable-snooze-label" for="disable-snooze">Disable Snooze:</label>
            <input type="checkbox" id="disable-snooze">
        </div>

        <div>
            <label for="alarm-time">Select Alarm Time:</label>
            <select id="alarm-time" type="time">
                <?php
                    // Generate dropdown options for alarm time intervals
                    $start = strtotime('00:00');
                    $end = strtotime('23:59');
                    $interval = 15 * 60; // 15 minutes interval

                    for ($i = $start; $i <= $end; $i += $interval) {
                        echo '<option value="' . date('H:i', $i) . '">' . date('h:i A', $i) . '</option>';
                    }
                ?>
            </select>
        </div>

        <button id="add-alarm-time">Add Alarm</button>
    </div>

    <script>
        // Update current time every second
        function updateCurrentTime() {
            const currentTimeElement = document.getElementById('current-time');
            setInterval(() => {
                const now = new Date();
                const hours = now.getHours().toString().padStart(2, '0');
                const minutes = now.getMinutes().toString().padStart(2, '0');
                const seconds = now.getSeconds().toString().padStart(2, '0');
                currentTimeElement.textContent = `Current Time: ${hours}:${minutes}:${seconds}`;
            }, 1000);
        }

        // Add event listener for "Add Alarm" button
        document.getElementById('add-alarm-time').addEventListener('click', function() {
            const selectedAlarmTime = document.getElementById('alarm-time').value;
            alert(`Alarm added for ${selectedAlarmTime}`);
        });

        // Call the updateCurrentTime function when the page loads
        window.onload = updateCurrentTime;
    </script>
</body>
</html>

