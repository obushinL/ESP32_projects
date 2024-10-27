const char HTML[] = R"=====(
<!DOCTYPE html>

<html>
<style>

body{
      background: linear-gradient(to right,white,60%,rgb(149, 253, 253));
    }

header{
    text-align: center;
    font-family: Georgia, 'Times New Roman', Times, serif;
}

main{
    text-align: center;
}

.switch {
  display: inline-block;
  height: 70px;
  position: relative;
  width: 200px;
}

.switch input {
  display:none;
}

.slider {
  background-color: #000000;
  bottom: 0;
  cursor: pointer;
  left: 0;
  position: absolute;
  right: 0;
  top: 0;
  transition: .4s;
}

.slider:before {
  background-color: #fff;
  bottom: 10px;
  content: "";
  height: 50px;
  left: 10px;
  position: absolute;
  transition: .2s;
  width: 50px;
}

input:checked + .slider {
  background-color: orange;
}

input:checked + .slider:before {
  transform: translateX(130px);
}

.slider.round {
  border-radius: 50px;
}

.slider.round:before {
  border-radius: 50%;
}

}
html {font-family: Arial; display: inline-block; text-align: center;}
  p { font-size: 1.2rem;}
  body {  margin: 0;}
  .topnav { overflow: hidden; background-color: #50B8B4; color: white; font-size: 1rem; }
  .content { padding: 20px; }
  .card { background-color: white; box-shadow: 2px 2px 12px 1px rgba(0, 0, 0, 0.5); width:400px;top:30%; left:40%; position:absolute}
  .cards { max-width: 800px; margin: 0 auto; display: grid; grid-gap: 2rem; grid-template-columns: repeat(auto-fit, minmax(200px, 1fr)); }
  .reading { font-size: 1.4rem; }
</style>    

<head>
  <meta http-equiv="X-UA-Compatible" content="IE=edge">

  <title>
  </title>

  <meta name="description" content="">
  <meta name="viewport" content="width=device-width, initial-scale=1">
</head>
    
<script>

  function check_checkbox(){
    var mode = Number(document.getElementById("checkbox").checked);
    console.log("mode "+mode);
    
    var request = new XMLHttpRequest();
		request.open('GET', '/mode?mode='+mode, false);
		request.send();
  }


</script>
    
<body>

  <header>
    <div>
        <h1>WEB - interface for your luminodiode</h1>
    </div>
</header>

<main>
  <h2>Let the Lamp Light</h2>
  <div class="container">
      <label class="switch" for="checkbox">
        <input type="checkbox" id="checkbox" onchange="check_checkbox()">
        <div class="slider round"></div>
      </label>

</main>

<footer>
</footer>
          
</body>

</html>
)=====";