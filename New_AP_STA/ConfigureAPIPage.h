const char APIconfig_page[] PROGMEM = R"====(
<!DOCTYPE HTML>
<html>
<head> <meta name="viewport" content="width=device-width, initial-scale=1.0">
<script>
function validateForm(){
var apiV = document.forms["Settings"]["api"]; 
if(apiV.value == ""){window.alert("Enter valid data");return false;}                                  
return true;
}
</script>
</head>
<body bgcolor = "lightgrey">
<center>
<h1>API Configuration Menu</h1><br>
<form align="center" name="Settings" action="/SaveConfig" onsubmit="return validateForm()" method="POST">
    <br><label for="api">Enter API: </label><br>
    <br><input type="url" id="api" name="api"><br>
    <br><br><input type="submit" value="Save API Configurations">
</form><br><br>
<form action="/close">
    <input type="submit" value="Close">
</form><br><br>

</html>
)====";
