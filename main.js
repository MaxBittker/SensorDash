//module.exports.start =function () {

var button = document.getElementById('start'); // add id="my-button" into html
button.addEventListener('click', start);


function start() {

        document.getElementById("Readings").innerHTML = "Waiting for data...<br>";
        var eventSource = new EventSource("https://api.spark.io/v1/devices/" + deviceID + "/events/?access_token=" + accessToken);

        eventSource.addEventListener('open', function(e) {
            console.log("Opened!"); },false);

        eventSource.addEventListener('error', function(e) {
            console.log("Errored!"); },false);

        eventSource.addEventListener('Readings', function(e) {
            var parsedData = JSON.parse(e.data);
            var tempSpan = document.getElementById("Readings");
            var tsSpan   = document.getElementById("tstamp");
            tempSpan.innerHTML += " Reading: " + (parsedData.data-70) +"<br>"; //"Core: " + parsedData.coreid +
            tempSpan.style.fontSize = "28px";
            tsSpan.innerHTML = "Last timestamp " + parsedData.published_at;
            tsSpan.style.fontSize = "20px";
            tick(parsedData.data-70);
        }, false);
    }


var n = 40,
    random = d3.random.normal(0,0),
    data = d3.range(n).map(random);
var margin = {top: 20, right: 20, bottom: 20, left: 40},
    width = 960 - margin.left - margin.right,
    height = 500 - margin.top - margin.bottom;
var x = d3.scale.linear()
    .domain([0, n - 1])
    .range([0, width]);
var y = d3.scale.linear()
    .domain([0, 500])
    .range([height, 0]);
var line = d3.svg.line()
    .x(function(d, i) { return x(i); })
    .y(function(d, i) { return y(d); });
var svg = d3.select("#chart").append("svg")
    .attr("width", width + margin.left + margin.right)
    .attr("height", height + margin.top + margin.bottom)
  .append("g")
    .attr("transform", "translate(" + margin.left + "," + margin.top + ")");
svg.append("defs").append("clipPath")
    .attr("id", "clip")
  .append("rect")
    .attr("width", width)
    .attr("height", height);
svg.append("g")
    .attr("class", "x axis")
    .attr("transform", "translate(0," + y(0) + ")")
    .call(d3.svg.axis().scale(x).orient("bottom"));
svg.append("g")
    .attr("class", "y axis")
    .call(d3.svg.axis().scale(y).orient("left"));
var path = svg.append("g")
    .attr("clip-path", "url(#clip)")
  .append("path")
    .datum(data)
    .attr("class", "line")
    .attr("d", line);
function tick(value) {
  // push a new data point onto the back
  data.push(value);
  // redraw the line, and slide it to the left
  path
      .attr("d", line)
      .attr("transform", null)
    .transition()
      .duration(500)
      .ease("linear")
      .attr("transform", "translate(" + x(-1) + ",0)");
      // .each("end", tick);
  // pop the old data point off the front
  data.shift();
}