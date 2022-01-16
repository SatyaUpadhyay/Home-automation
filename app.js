
    const express    = require('express');
    const bodyParser = require('body-parser');
    const path       = require('path');
    const cors       = require('cors');

    var multer       = require('multer');
    var upload       = multer();
    // Init App
    const app  = express();
    
    const http = require('http').Server(app);
    const io   = require('socket.io')(http);
    require("./DbConnection");
    //app.use( bodyParser.json() );
    //Route Define
    var byke = require('./routes/routes')(app, io); 

    //app.use(bodyParser.json({limit: '500000mb'}));
    //app.use(bodyParser.urlencoded({limit: '500000mb', extended: true, parameterLimit: 10000000000}));
    app.use(upload.array()); 
    // Set Static Folder
    app.use(express.static(path.join(__dirname, 'public')));
    app.use((req, res, next)=>{
        res.header('Access-Control-Allow-Origin','*');
        res.header('Access-Control-Allow-Headers','Origin, X-Requested-with, Accept, Authorization, authorization');
        res.header('Access-Control-Allow-Methods','OPTIONS,GET, POST, PUT, DELETE');
        next();
    });
    app.use(cors({
        exposedHeaders: ['Authorization', 'authorization'],
    }));
    app.use('/api', byke); 
    io.on('connection', function(socket) {
        console.log('A user connected');
        //Whenever someone disconnects this piece of code executed
        socket.on('disconnect', function () {
            console.log('A user disconnected');
        });
    }); 
    http.listen(process.env.APP_PORT,(err)=>{ 
        if(err) throw err;
        console.log('Listing To port http://localhost:'+process.env.APP_PORT);
    })
