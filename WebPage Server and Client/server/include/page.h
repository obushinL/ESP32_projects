const char HTML[] = R"=====(
<!DOCTYPE html>
<html lang="en-US">
<style>
    body {
        background-color: #333131;
    }

    .page_header {
        position: relative;
        top: 0pt;
        padding-right: 10pt;
        padding-left: 10pt;
        margin-left: 30%;
        height: 50pt;
        width: 270pt;
        background-color: aliceblue;
        border-radius: 15pt;
        box-shadow: 3pt 3pt black;
        text-align: center;
        line-height: 50pt;
        margin-top: 20pt;
    }

    .page_header h1 {
        font-size: 25pt;
        font-family: 'Consolas';
    }

    .temp_panel {
        position: relative;
        top: 0pt;
        margin-top: 50pt;
        margin-left: 50pt;
        width: 200pt;
        height: 70pt;
    }

    .name_temp_value {
        position: absolute;
        top: 15pt;
        left: 0pt;
        width: 150pt;
        height: 30pt;
        align-content: center;
        font-weight: bolder;
        line-height: 35pt;
        border-style: dashed;
        border-radius: 6pt;
        border-color: rgb(0, 0, 0);
        box-shadow: 2pt 4pt black;
        background-color: whitesmoke;
    }

    .name_temp_value {
        font-size: 12pt;
        font-family: 'Consolas';
        text-align: center;
        margin-top: 0pt;
        line-height: 30pt;

    }

    #temp_value {
        position: absolute;
        top: -12pt;
        left: 135pt;
        height: 80pt;
        width: 80pt;
        border-radius: 25pt;
        align-content: center;
        background-color: aliceblue;
        border-style: dashed;
        box-shadow: 2pt 4pt black;
        font-weight: bolder;
        font-size: 22pt;
        line-height: 75pt;
        font-family: 'Consolas';
    }

    #temp_value_2 {
        position: absolute;
        top: -12pt;
        left: 135pt;
        height: 80pt;
        width: 80pt;
        border-radius: 25pt;
        align-content: center;
        background-color: aliceblue;
        border-style: dashed;
        box-shadow: 2pt 4pt black;
        font-weight: bolder;
        font-size: 22pt;
        line-height: 75pt;
        font-family: 'Consolas';
    }

    #out_soc_temp_val_1 {
        position: absolute;
        right: 24pt;
        top: -10pt;
        font-size: 1rem;
    }

    #out_soc_temp_val_2 {
        position: absolute;
        right: 24pt;
        top: -10pt;
        font-size: 1rem;
    }

    #out_soc_temp_mesure {
        position: absolute;
        right: 10pt;
        top: -20pt;
        font-size: 25pt;
    }
</style>

<head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <title>Easy dashboard</title>
    <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=2.0, user-scalable=yes">

</head>

<body>
    <header>
        <div class="page_header">
            <h1 id="title_header">ESP32S3 dashboard</h1>
        </div>
    </header>
    <main>
        <div class="temp_panel">
            <div class="name_temp_value">
                <a>SoC 1 temp (°C)</a>
            </div>
            <div id="temp_value">
                <h3 id="out_soc_temp_val_1">0</h3>
            </div>
        </div>

        <div class="temp_panel">
            <div class="name_temp_value">
                <a>SoC 2 temp (°C)</a>
            </div>
            <div id="temp_value_2">
                <h3 id="out_soc_temp_val_2">0</h3>
            </div>

        </div>
    </main>


    <script>
        
        // Запуск обработчика запросов по таймеру
        function work() {
            let request1 = new XMLHttpRequest();
            request.open("GET", "/out_soc_temp_val_1", true);
            request.responseType = "text";
            request.onreadystatechange = function () {
                // проверяем состояние запроса и числовой код состояния HTTP ответа
                if (request.readyState === 4 && request.status === 200) {
                    // Cтроковое значение, содержащее ответ на запрос в виде текста
                    const newValTemp = request.responseText;
                    console.log(String(newValTemp));
                    // Принятие нового значения
                    document.getElementById("out_soc_temp_val_1").innerText = newValTemp;
                }
            };
            request.send();

            let request2 = new XMLHttpRequest();
            request.open("GET", "/data_temp_2", true);
            request.responseType = "text";
            request.onreadystatechange = function () {
                // проверяем состояние запроса и числовой код состояния HTTP ответа
                if (request.readyState === 4 && request.status === 200) {
                    // Cтроковое значение, содержащее ответ на запрос в виде текста
                    const newValTemp = request.responseText;
                    console.log(String(newValTemp));
                    // Принятие нового значения
                    document.getElementById("out_soc_temp_val_2").innerText = newValTemp;
                }
            };
            request.send();
        }

            async function fetchRGBData(){
        try{
            const res1 = await fetch('http://192.168.1.1/data_rgb_1');
            const d1 = await res1.json();

            if (d1.id === 'device_1') {
                console.log('Device 1 rgb: ')
                console.log(`rgb: ${JSON.stringify(d1.Value)}`); 
            }

            const res2 = await fetch('http://192.168.1.1/data_rgb_2');
            const d2 = await res2.json();

            if (d2.id === 'device_2') {
                console.log('Device 2 rgb: ')
                console.log(`rgb: ${JSON.stringify(d2.Value)}`); 
            }
        } 
        catch (error) {
        console.error('Error fetching data:', error);
    }
}

        async function fetchTempData() {
    try {
        const response1 = await fetch('http://192.168.1.1/data_temp_1');
        const data1 = await response1.json();

        if (data1.id === 'device_1') {
                const temperatureElement = document.getElementById('out_soc_temp_val_1');
                temperatureElement.textContent = data1.Value; 
        } 

        const response2 = await fetch('http://192.168.1.1/data_temp_2');
        const data2 = await response2.json();

        if (data2.id === 'device_2') {
                const temperatureElement = document.getElementById('out_soc_temp_val_2');
                temperatureElement.textContent = data2.Value; 
        } 
    } 

    catch (error) {
        console.error('Error fetching data:', error);
    }
}

// Вызов функции для получения данных
setInterval(fetchTempData, 3000);

    </script>

</body>

</html>
)=====";