namespace webpage
{

char html[] = "<html>\n\t\
  <head>\n\t\t\
    <title>NodeMCU DHT11 Sensor \and Relay Board</title>\n\t\t\
    <style>\n\t\
      body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\n\t\t\
      li { margin: 10px 0;}\n\
    </style>\n\t\
    <script type=\'text/javascript\'>\n\
    url = \'http://192.168.1.88/json\';\n\t\t\
  setInterval(function() {\n\t\t\
  fetchData();\n\
  }, 60000);\n\
  function fetchData(){\n\t\
  var xmlhttp = new XMLHttpRequest();\n\t\
  xmlhttp.open(\'GET\', url, true);\n\t\
  xmlhttp.onreadystatechange = function() {\n\t\
      if (xmlhttp.readyState == 4) {\n\t\
          if(xmlhttp.status == 200) {\n\
              var obj = JSON.parse(xmlhttp.responseText);\n\
              sensorData = obj[\'nodemcu\'][0];\n\
        document.getElementById(\'temp\').innerHTML = \'Temperature: \'+sensorData.temperatureInC +\'&deg;C\';\n\
        document.getElementById(\'hum\').innerHTML = \'Humidity: \'+sensorData.humidity +\'%\';\n\
           }\n\
      }\n\
  };\n\
  xmlhttp.send(null);\n\
  }\n\
    </script>\n\
    \n\t\n</head>\n\
    <body onload=\'fetchData()\'>\n\
    \t<h1>Hello from NodeMCU!</h1>\n\
    <\div id=\'temp\'>Temperature: </\div>\n\
    <\div id=\'hum\'>Humidity:  <br></\div><ol>\n\t";

}

