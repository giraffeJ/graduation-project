var express = require('express');
var app = express();
var port = 8080;
var router = require('./router/main')(app);
var hostname = '127.0.0.1';

app.set('views', __dirname + '/views');
app.set('view engine', 'ejs');
app.engine('html', require('ejs').renderFile);

var server = app.listen(port, function(){
    console.log("Express server has started on port 3000")
})

app.get('/', function(req, res){
    res.send('Hello world');
})