const char machineNameconfig_page[] PROGMEM = R"====(
<!DOCTYPE HTML>
<html>
<head> <meta name="viewport" content="width=device-width, initial-scale=1.0">
<script>
function validateForm(){
var machineNameV = document.forms["Settings"]["machineNameD"]; 
if(machineName.value == ""){window.alert("Enter valid data");return false;}                                  
return true;
}
</script>
</head>
<body bgcolor = "lightgrey">
<center>
<h1>Machine Name Configuration Menu</h1><br>
<form align="center" name="Settings" action="/SaveConfig" onsubmit="return validateForm()" method="POST">
    <br><label for="machineName">Enter Machine Name: </label><br>
    <br><input type="text" id="machineName" name="machineName"><br>
    <br><br><input type="submit" value="Save Machine Name Configurations">
</form><br><br>
<form action="/close">
    <input type="submit" value="Close">
</form><br><br>

</html>
)====";
