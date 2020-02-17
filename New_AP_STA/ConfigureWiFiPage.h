const char Wificonfig_page[] PROGMEM = R"====(
<!DOCTYPE HTML>
<html>
<head> <meta name="viewport" content="width=device-width, initial-scale=1.0">
<script>
function validateForm(){
var ssidV = document.forms["Settings"]["ssid"]; 
var passV = document.forms["Settings"]["password"]; 
if(ssidV.value == "" || passV.value == ""){window.alert("Enter valid data");return false;}                                  
return true;
}
</script>
</head>
<body bgcolor = "lightgrey">
<center>
<h1>Wi-Fi Configuration Menu</h1><br>
<form align="center" name="Settings" action="/SaveConfig"  onsubmit="return validateForm()" method="POST">
    <br><label for="ssid">Enter SSID: </label><br>
    <br><input type="text"  id="ssid" name="ssid"><br>
    <br><label for="pass">Enter Password: </label><br>
    <br><input type="password" id="pass" name="password" minlength="8"><br>
    <br><br><input type="submit" value="Save WiFi Configurations">
</form><br><br>
<form action="/close" >
    <input type="submit" value="Close">
</form><br><br>

</html>
)====";
