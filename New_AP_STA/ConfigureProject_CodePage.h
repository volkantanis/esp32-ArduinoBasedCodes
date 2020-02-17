const char Project_Codeconfig_page[] PROGMEM = R"====(
<!DOCTYPE HTML>
<html>
<head> <meta name="viewport" content="width=device-width, initial-scale=1.0">
<script>
function validateForm(){
var deviceIdV = document.forms["Settings"]["deviceID"]; 
if(deviceIdV.value == ""){window.alert("Enter valid data");return false;}                                  
return true;
}
</script>
</head>
<body bgcolor = "lightgrey">
<center>
<h1>Device ID Configuration Menu</h1><br>
<form align="center" name="Settings" action="/SaveConfig" onsubmit="return validateForm()" method="POST">
    <br><label for="Project_Code">Enter Project Code: </label><br>
    <br><input type="text" id="Project_Code" name="Project_Code"><br>
    <br><br><input type="submit" value="Save Project Code Configurations">
</form><br><br>
<form action="/close">
    <input type="submit" value="Close">
</form><br><br>

</html>

)====";
