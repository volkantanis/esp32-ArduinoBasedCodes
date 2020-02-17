const char InputConfig_page[] PROGMEM = R"====(
<!DOCTYPE HTML>
<html>
<head> <meta name="viewport" content="width=device-width, initial-scale=1.0">
<script>
function validateForm(){
var i1 = document.forms["Settings"]["Input1"]; 
var i2 = document.forms["Settings"]["Input2"]; 
var i3 = document.forms["Settings"]["Input3"]; 
var i4 = document.forms["Settings"]["Input4"]; 
var i5 = document.forms["Settings"]["Input5"]; 
var i6 = document.forms["Settings"]["Input6"]; 
var i7 = document.forms["Settings"]["Input7"]; 
var i8 = document.forms["Settings"]["Input8"]; 
if(i1.value == "" || i2.value == ""|| i3.value == ""|| i4.value == ""|| i5.value == ""|| i6.value == ""|| i7.value == ""|| i8.value == "")
{window.alert("Enter all valid data");return false;}                                  
return true;
}
</script>
</head>
<body bgcolor = "lightgrey">
<center>
<h1>Input Configuration Menu</h1><br>
<form align="center" name="Settings" action="/SaveConfig" onsubmit="return validateForm()" method="POST">
    <br><label for="Input1">Enter Input1: </label><br>
    <br><input type="text" id="Input1" name="Input1"><br>
    <br><label for="Input2">Enter Input2: </label><br>
    <br><input type="text" id="Input2" name="Input2"><br>
    <br><label for="Input3">Enter Input3: </label><br>
    <br><input type="text" id="Input3" name="Input3"><br>
    <br><label for="Input4">Enter Input4: </label><br>
    <br><input type="text" id="Input4" name="Input4"><br>
    <br><label for="Input5">Enter Input5: </label><br>
    <br><input type="text" id="Input5" name="Input5"><br>
    <br><label for="Input6">Enter Input6: </label><br>
    <br><input type="text" id="Input6" name="Input6"><br>
    <br><label for="Input7">Enter Input7: </label><br>
    <br><input type="text" id="Input7" name="Input7"><br>
    <br><label for="Input8">Enter Input8: </label><br>
    <br><input type="text" id="Input8" name="Input8"><br>
    <br><br><input type="submit" value="Save Input Configurations">
</form><br><br>
<form action="/close">
    <input type="submit" value="Close">
</form><br><br>

</html>
)====";
