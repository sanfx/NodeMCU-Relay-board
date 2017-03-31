namespace webpage
{

char html[] = "<html>\n\t\
  <head>\n\t\t\
    <title>Wifi Switch with Temperature & Humidity Panel</title>\n\t\t\
    <style>\n\t\
      body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; \Color: #000088; }\n\t\t\
      li { margin: 10px 0;}\n\t\
      .button {\n\t\
    -webkit-transition-duration: 0.4s;\n\t\
    transition-duration: 0.4s;\n\t\
    background-color: #4CAF50;\n\t\
    border: none;\n\t\
    padding: 32px 16px;\n\t\
    color: black;\n\t\
    text-align: center;\n\t\
    text-decoration: none;\n\t\
    \display: \inline-block;\n\t\
    font-\size: 24px;\n\t\
    margin: 4px 2px;\n\t\
    \cursor: pointer;\n\
}\n\
.button3 {width: 100%; border-radius: 12px; background-color: white; border: 2px solid #4CAF50;}\n\
.button3:hover {box-shadow: 0 12px 16px 0 rgba(0,0,0,0.24), 0 17px 50px 0 rgba(0,0,0,0.19);}\n\
    </style>\n\t\
    <script type=\'text/javascript\'>\n\t\
        function turnOnRelay(param, relayNum) {\n\t\t\
  var ifrm = document.createElement(\'iframe\');\n\t\
    ifrm.setAttribute(\'src\', \'/control?relay=\' + relayNum);\n\t\
    ifrm.setAttribute(\'id\', \'iframe\');\n\t\
    ifrm.style.visibility = \'false\';\n\t\
    ifrm.style.display = \'none\';\n\t\
    document.body.appendChild(ifrm);\n\t\
    fetchData();\n\t\
      }\n\
    function startUp(){\n\t\
    fetchData();\n\t\
    }\n\
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
        text = sensorData.relay1 ? \'off\' : \'on\';\n\t\
      document.getElementById(\'btn1\').innerHTML = \'Turn \' + text + \' Light\';\n\t\
      txt = sensorData.relay2 ? \'off'\ : \'on'\;\n\t\
      document.getElementById(\'btn2\').innerHTML = \'Turn \' + txt + \' Fan\';\n\t\
           }\n\
      }\n\
  };\n\
  xmlhttp.send(null);\n\
  }\n\
    </script>\n\
    \n\t\n</head>\n\
    <body onload=\'startUp()\'>\n\
    \t<h1>Wifi Switch with Temperature & Humidity Panel</h1>\n\
    <\div id=\'temp\'>Temperature: </\div>\n\
    <\div id=\'hum\'>Humidity:  <br></\div>\n\t";

}

