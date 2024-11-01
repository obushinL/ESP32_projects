const char HTML[] = R"=====(
<!DOCTYPE HTML>
<html lang="ru">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>ESP Web Server</title>
<link rel="icon" href="data:,">
<style>
  html {
    font-family: Arial, Helvetica, sans-serif;
    text-align: center;
  }
  h1 {
    font-size: 1.8rem;
    color: white;
  }
  h2 {
    font-size: 1.5rem;
    font-weight: bold;
    color: #143642;
  }
  .topnav {
    overflow: hidden;
    background-color: #143642;
  }
  body {
    margin: 0;
  }
  .content {
    padding: 30px;
    max-width: 1000px;
    margin: 0 auto;
  }
  .card {
    background-color: #F8F7F9;
    box-shadow: 2px 2px 12px 1px rgba(140, 140, 140, .5);
    padding-top: 10px;
    padding-bottom: 20px;
  }
  canvas {
    border: 1px solid black;
    margin-top: 20px;
  }
</style>
</head>
<body>
<div class="topnav">
    <h1>ESP-S3 Web Server</h1>
</div>
<div class="content">
    <div>
    <h2>График данных</h2>
    </div>
    <div class="card">
    <canvas id="myChart" width="700" height="400"></canvas>
    </div>
</div>

<script>
const canvas = document.getElementById('myChart');
  const ctx = canvas.getContext('2d');

  let xyValues = []; // Изначально пустой массив

  // Функция для рисования графика
  function drawChart() {
    ctx.clearRect(0, 0, canvas.width, canvas.height);

    const xMin = 0;
    const xMax = 270;
    const yMin = 0;
    const yMax = 100;

    // Рисуем оси
    ctx.beginPath();
    ctx.moveTo(50, canvas.height - 30); 
    ctx.lineTo(canvas.width - 30, canvas.height - 30); // Ось X
    ctx.lineTo(canvas.width - 30, canvas.height - 20); // Стрелка оси X
    ctx.moveTo(50, canvas.height - 30); 
    ctx.lineTo(50, 10); // Ось Y
    ctx.stroke();

    // Подписи осей
    ctx.font = "16px Arial";
    ctx.fillText("t, с", canvas.width - 25, canvas.height - 30);
    ctx.fillText("t, °C", 10, 15);

    // Рисуем деления на осях
    const xStep = (canvas.width - 80) / (xMax / 30);
    const yStep = (canvas.height - 60) / (yMax / 10);

    for (let i = xMin; i <= xMax; i += 30) {
      const x = (i - xMin) / (xMax - xMin) * (canvas.width - 80) + 50;
      ctx.moveTo(x, canvas.height - 30);
      ctx.lineTo(x, canvas.height - 25);
      ctx.fillText(i, x - 10, canvas.height - 10);
    }

    for (let i = yMin; i <= yMax; i += 10) {
      const y = canvas.height - ((i - yMin) / (yMax - yMin) * (canvas.height - 60) + 30);
      ctx.moveTo(50, y);
      ctx.lineTo(45, y);
      ctx.fillText(i, 10, y + 5);
    }

    // Рисуем линии и точки
    ctx.beginPath();
    xyValues.forEach((point, index) => {
      const x = (point.x - xMin) / (xMax - xMin) * (canvas.width - 80) + 50;
      const y = canvas.height - ((point.y - yMin) / (yMax - yMin) * (canvas.height - 60) + 30);

      // Рисуем линию к предыдущей точке
      if (index > 0) {
        const prevPoint = xyValues[index - 1];
        const prevX = (prevPoint.x - xMin) / (xMax - xMin) * (canvas.width - 80) + 50;
        const prevY = canvas.height - ((prevPoint.y - yMin) / (yMax - yMin) * (canvas.height - 60) + 30);
        ctx.moveTo(prevX, prevY);
        ctx.lineTo(x, y); 
      }

      // Рисуем точку
      ctx.arc(x, y, 4, 0, Math.PI * 2); 
      ctx.fillStyle = "rgb(0,0,0)";
      ctx.fill();
    });
            
    // Устанавливаем стиль для линий
    ctx.strokeStyle = "rgb(0,0,255)";
    ctx.stroke();
  }

  // Функция для получения данных из JSON и обновления графика
  function updateChart() {
    fetch('http://192.168.1.1/data_temp_values') // Замените 'ip' на ваш IP-адрес
      .then(response => response.json())
      .then(data => {
        xyValues = []; // Очищаем массив перед заполнением новыми данными
        for (let i = 1; i <= Object.keys(data).length; i++) {
          xyValues.push({x: (i-1)*30, y: parseFloat(data['Value' + i])});
        }
        drawChart(); // Перерисовываем график с новыми данными
      })
      .catch(error => console.error('Ошибка:', error));
  }

  // Первоначальный вызов для отрисовки графика
  updateChart();

  // Обновляем график каждые 30 секунд
  setInterval(updateChart, 30000);
</script>
</body>
</html>
)=====";