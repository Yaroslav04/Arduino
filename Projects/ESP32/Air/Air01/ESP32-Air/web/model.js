const model = [
    { type: 'title', value: 'Air Quality 1.0' },
    {
        type: 'sensor', value: '!', id: "temperature", class: "sensor", color: "0,0,255",
        description: "Температура🌡:",
        color_sheme_low: 0, color_sheme_middle: 20, color_sheme_up: 30,
        color_low_r: 0, color_low_g: 0, color_low_b: 0xff,
        color_middle_r: 0xff, color_middle_g: 0xff, color_middle_b: 0,
        color_up_r: 0xff, color_up_g: 0, color_up_b: 0
    },
    {
        type: 'sensor', value: "!", id: "humidity", class: "sensor", color: "0,0,255",
        description: "Влажность💧:",
        color_sheme_low: 0, color_sheme_middle: 50, color_sheme_up: 100,
        color_low_r: 0, color_low_g: 0xff, color_low_b: 0xff,
        color_middle_r: 0, color_middle_g: 0, color_middle_b: 0xff,
        color_up_r: 0xff, color_up_g: 0, color_up_b: 0xff
    },
    {
        type: 'sensor', value: "!", id: "co", class: "sensor", color: "0,0,255",
        description: "CO2☁:",
        color_sheme_low: 600, color_sheme_middle: 800, color_sheme_up: 1200,
        color_low_r: 0, color_low_g: 0xff, color_low_b: 0,
        color_middle_r: 0, color_middle_g: 0xff, color_middle_b: 0xff,
        color_up_r: 0xff, color_up_g: 0, color_up_b: 0
    },
    {
        type: 'sensor', value: "!", id: "aqi", class: "sensor", color: "0,0,255",
        description: "Воздух☣:",
        color_sheme_low: 0, color_sheme_middle: 15, color_sheme_up: 30,
        color_low_r: 0, color_low_g: 0xff, color_low_b: 0,
        color_middle_r: 0xff, color_middle_g: 0xff, color_middle_b: 0,
        color_up_r: 0xff, color_up_g: 0, color_up_b: 0
    },
    {
        type: 'graph', id: "graph_temperature", 
        labels: [30,25,20,15,10,5,0],
        label: 'Temperature',
        //data: [65, 59, 80, 81, 56, 55, 40],
        borderColor: 'rgb(255, 0, 0)',
    },
    {
        type: 'graph', id: "graph_humidity", 
        labels: [30,25,20,15,10,5,0],
        label: 'Humidity',
        borderColor: 'rgb(255, 0, 0)',
    },
    {
        type: 'graph', id: "graph_co", 
        labels: [30,25,20,15,10,5,0],
        label: 'CO',
        borderColor: 'rgb(255, 0, 0)',
    },
    {
        type: 'graph', id: "graph_aqi", 
        labels: [30,25,20,15,10,5,0],
        label: 'AQI',
        borderColor: 'rgb(255, 0, 0)',
    },
]