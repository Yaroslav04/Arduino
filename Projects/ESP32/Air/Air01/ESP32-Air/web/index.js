function title(block) {
    return `<h1 class="text">${block.value}</h1>`
}

function text(block) {
    return `<p class="text">${block.value}</p>`
}

function button(block) {
    return row(`
    <input type="button" id="${block.id}" class="${block.class}">
    <h2 class="button_title">${block.value}</h2>
    `)
}

function sensor(block) {
    return row(`
    <p class="${block.class}">${block.description}</p>
    <p id="${block.id}" style=" color: rgb(${block.color});" class="${block.class}">${block.value}</p>
    `)
}

function tap(block) {
    return row(`
    <input type="button" id="${block.id}" class="${block.class}">
    <h2 class="button_title">${block.value}</h2>
    `)
}

function graph(block) {
    return row(`
    <canvas id="${block.id}""></canvas>
    `)
}

function row(content) {
    return `<div class="block">${content}</div>`
}

const templates = {
    title,
    text,
    button,
    sensor,
    tap,
    graph
}

//SENSOR

function StartTimerSensorsValue() {
    setInterval(GetSensorsValue, 11000)
}

function GetSensorsValue() {
    var request = new XMLHttpRequest()
    request.open('GET', '/getSensorsValue', true)
    request.onload = function () {
        if (request.readyState == 4 && request.status == 200) {
            var values = request.responseText
            SearchSensors(values)
        }
    }
    request.send()
}

function SearchSensors(values) {
    model.forEach(block => {
        if (block.type === 'sensor') {
            var arrayJson = JSON.parse(values)
            arrayJson.forEach(elementJson => {
                if (elementJson.name === block.id) {
                    SensorUpload(elementJson.name, elementJson.value)
                }
            }
            )
        }
    })
}

function SensorUpload(id, value) {

    var block = model.find(obj => {
        return obj.id === id
    })
    var element = document.getElementById(id)

    console.log(value)

    if (value.length > 1) {
        console.log( 'res' + value)
        block.color = getColorForPercentage(
            value[0], block.color_sheme_low, block.color_sheme_middle, block.color_sheme_up,
            block.color_low_r, block.color_low_g, block.color_low_b,
            block.color_middle_r, block.color_middle_g, block.color_middle_b,
            block.color_up_r, block.color_up_g, block.color_up_b)
            console.log(block.color)
        element.style.color = `rgb(${block.color})`
        element.innerHTML = value.join(' | ')
    }
    else {
        block.color = getColorForPercentage(
            value, block.color_sheme_low, block.color_sheme_middle, block.color_sheme_up,
            block.color_low_r, block.color_low_g, block.color_low_b,
            block.color_middle_r, block.color_middle_g, block.color_middle_b,
            block.color_up_r, block.color_up_g, block.color_up_b)
            console.log(block.color)
        element.style.color = `rgb(${block.color})`
        element.innerHTML = value
    }
}

//GRAPHS

function StartTimerGraphsValue() {
    setInterval(GetGraphsValue, 360000)
}

function GetGraphsValue() {
    var request = new XMLHttpRequest()
    request.open('GET', '/getGraphsValue', true)
    request.onload = function () {
        if (request.readyState == 4 && request.status == 200) {
            var values = request.responseText
            SearchGraphs(values)
        }
    }
    request.send()
}

function SearchGraphs(values) {
    model.forEach(block => {
        if (block.type === 'graph') {
            var arrayJson = JSON.parse(values)
            arrayJson.forEach(elementJson => {
                if (elementJson.name === block.id) {
                    GraphUpload(elementJson.name, elementJson.value)
                }
            }
            )
        }
    })
}

function GraphUpload(id, value) {

    var block = model.find(obj => {
        return obj.id === id
    })

        var array = value
        let data = {
            labels: block.labels,
            datasets: [{
                label: block.label,
                data: array,
                fill: false,
                borderColor: block.borderColor,
                tension: 0.1
            }]
        };

        let ctx = document.getElementById(block.id).getContext('2d')

        const myChart = new Chart(ctx, {
            type: 'line',
            data: data,
        })

        setTimeout(() =>
            myChart.destroy()
            , 355000)

}

//BUTTONS

function StartTimerButtonsValue() {
    setInterval(GetButtonsValue, 7000)
}

function GetButtonsValue() {
    var request = new XMLHttpRequest()
    request.open('GET', '/getRelayValue', true)
    request.onload = function () {
        if (request.readyState == 4 && request.status == 200) {
            var values = request.responseText
            SearchButtons(values)
        }
    }
    request.send()
}

function SearchButtons(values) {
    model.forEach(block => {
        if (block.type === 'button') {
            values.split(';').forEach(value => {
                var array = value.split(',')
                if (array[0] === block.id) {
                    ButtonUpload(array[0], array[1])
                }
            }
            )
        }
    })
}

function ButtonUpload(id, value) {

    var block = model.find(obj => {
        return obj.id === id
    })
    var element = document.getElementById(id)
    var state = Number.parseInt(value)
    if (state == 0) {
        block.state = state
        element.classList.remove('relay_on')
        element.classList.add('relay_off')
    }
    else if (state == 1) {
        block.state = state
        element.classList.remove('relay_off')
        element.classList.add('relay_on')
    }
}

function ButtonClick(block) {
    var button = document.getElementById(block.id)
    var request = new XMLHttpRequest()
    request.open('GET', '/relay' + button.id.match(/\d+/g) + 'Switch', true);
    request.onload = function () {
        if (request.readyState == 4 && request.status == 200) {
            var response = request.responseText;
            var state = Number.parseInt(response);
            if (state == 0) {
                block.state = state
                button.classList.remove('relay_on')
                button.classList.add('relay_off')
            }
            else if (state == 1) {
                block.state = state
                button.classList.remove('relay_off')
                button.classList.add('relay_on')
            }
        }
    }
    request.send();
    button.classList.remove('relay_on')
    button.classList.add('relay_off')
}

//TAPS

function TapClick(block) {
    var tap = document.getElementById(block.id)
    var request = new XMLHttpRequest()
    request.open('GET', "/" + tap.id, true)
    request.onload = function () {
        if (request.readyState == 4 && request.status == 200) {
            var response = request.responseText
            alert(tap.id + " " + response)
        }
    }
    request.send()
}

//MAIN

let myCharts = null
var isSensors = false
var isGraphs = false
var isButtons = false

model.forEach(e => {

    if (e.type === 'sensor') {
        isSensors = true
    }
    if (e.type === 'button') {
        isButtons = true
    }
    if (e.type === 'graph') {
        isGraphs = true
    }
})

if (isSensors) {
    document.addEventListener('DOMContentLoaded', StartTimerSensorsValue);
    document.addEventListener('DOMContentLoaded', GetSensorsValue);
}

if (isButtons) {
    document.addEventListener('DOMContentLoaded', StartTimerButtonsValue);
    document.addEventListener('DOMContentLoaded', GetButtonsValue);
}

if (isGraphs) {
    document.addEventListener('DOMContentLoaded', StartTimerGraphsValue);
    document.addEventListener('DOMContentLoaded', GetGraphsValue);
}

const $site = document.querySelector('#site')

model.forEach(block => {
    const toHTML = templates[block.type]
    $site.insertAdjacentHTML('beforeend', toHTML(block))
    if (block.type === 'button') {
        var button = document.getElementById(block.id)
        button.addEventListener('click', eventHandlerButtonClick)
        function eventHandlerButtonClick() {
            ButtonClick(block)
        }
    }
    else if (block.type === 'tap') {
        var tap = document.getElementById(block.id)
        tap.addEventListener('click', eventHandlerTapClick)
        function eventHandlerTapClick() {
            TapClick(block)
        }
    }
})





